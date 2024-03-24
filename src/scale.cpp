#include "scale.h"

const unsigned int TIME_REQUIRED_FOR_STABILITY_MS = 1500;
const unsigned int TOLERANCE_PERCENTAGE_FOR_STABILITY = 5;
const unsigned int REGULATION_REFRESH_INTERVAL_MS = 10;
const unsigned long MIN_TIME_BETWEEN_UNIT_SWAP_MS = 1000;
const unsigned long MIN_TIME_BETWEEN_AVERAGING_SWAP_MS = MIN_TIME_BETWEEN_UNIT_SWAP_MS;

String scaleModeToString(ScaleModes mode) {
    switch(mode) {
        case ScaleModes::NORMAL:
            return "Pesee";
        case ScaleModes::TARE:
            return "Zero";
        case ScaleModes::CALIBRATION:
            return "Etalon.";
        case ScaleModes::COUNT:
            return "Comptage";
        default:
            return "UNKNOWN";
    }
}

Scale::Scale(UserInterface &display,
             DistanceSensor &distanceSensor,
             CurrentSensor &currentSensor,
             Actuator &actuator,
             PidController &positionRegulator,
             PidController &currentRegulator,
             double scaleCalibSlope,
             double scaleCalibIntercept) :
        _userInterface(display),
        _distanceSensor(distanceSensor),
        _actuatorCurrentSensor(currentSensor),
        _actuator(actuator),
        _positionRegulator(positionRegulator),
        _currentRegulator(currentRegulator),
        _scaleCalibrationSlope(scaleCalibSlope),
        _scaleCalibrationIntercept(scaleCalibIntercept){

    _averageTimePresetsMs = {10, 50, 100, 250, 500, 750, 1000, 1500, 2000};
    currentSensor.setSampleSize(_averageTimePresetsMs.front());
    distanceSensor.setSampleSize(_averageTimePresetsMs.front());

    _mode = ScaleModes::NORMAL;
    _unit = Units::GRAMS;
    _userInterface.displayMode("Demarrage");
    _executeTareMode();
}

[[noreturn]] void Scale::executeMainLoop() {
    while (true){
        _setModeFromButtonsState();
        _setUnitsFromButtonState();
        _userInterface.displayMode(scaleModeToString(_mode));
        _executeActiveMode();
    }

}

void Scale::_executeActiveMode(){
    switch(_mode) {
        case ScaleModes::NORMAL:
            _executeNormalMode();
            break;
        case ScaleModes::TARE :
            _executeTareMode();
            _mode = ScaleModes::NORMAL;
            break;
        case ScaleModes::CALIBRATION :
            _executeCalibrationMode();
            break;
        case ScaleModes::COUNT :
            _executeCountMode();
            break;
    }
}
void Scale::_executeNormalMode() {
    _regulateScale();
    _userInterface.displayStability(_isPositionStable());
    _userInterface.displayMass(getMassInGrams(), _unit);

    if (_userInterface.readButtons() == Buttons::select
        and millis() > _lastSampleSizeChangeTime + MIN_TIME_BETWEEN_AVERAGING_SWAP_MS) {
        _useNextAveragingPreset();
        _lastSampleSizeChangeTime = millis();
        _userInterface.clearMenuInstructionsZone();
    }
    _userInterface.displayAveragingTime(_averageTimePresetsMs[_currentAverageTimePresetIndex]);
}

void Scale::_regulateScale() {
    if (_isRefreshDue(_lastRegulatedTime)) {
        _positionRegulator.input = _distanceSensor.getAverageDistanceMm();

        _currentRegulator.setpoint = _positionRegulator.computeOutput();
        _currentRegulator.input = _actuatorCurrentSensor.getAverageCurrent(); //todo filter this or nah..?

        _actuator.setVoltage(_currentRegulator.computeOutput());
    }
}

void Scale::_executeCalibrationMode() {
    _userInterface.clearMassZone();
    //_userInterface.displayMass(0, _unit);//todo remove?
    const double calibrationMass1 = 0;
    const double calibrationMass2 = 50;
    bool calibrationDone = false;

    while (not calibrationDone) {
        while (_userInterface.readButtons() == Buttons::down) {
            _regulateScale();
            _userInterface.displayStability(_isPositionStable());
        }
        _userInterface.displayMenuInstructions("Ajouter 50g");
        _waitForButtonPressAndStabilization(Buttons::select);
        double massVsForceX2 = _actuator.getAppliedForceNFromCurrentA(_actuatorCurrentSensor.getAverageCurrent());

        while(_userInterface.readButtons() == Buttons::select){}

        _userInterface.displayMenuInstructions("Vider plateau");
        _waitForButtonPressAndStabilization(Buttons::select);
        double massVsForceX1 = _actuator.getAppliedForceNFromCurrentA(_actuatorCurrentSensor.getAverageCurrent());

        _scaleCalibrationSlope = (calibrationMass2 - calibrationMass1) / (massVsForceX2 - massVsForceX1);
        _scaleCalibrationIntercept = calibrationMass1 - _scaleCalibrationSlope * massVsForceX1;
        _userInterface.clearMenuInstructionsZone();
        calibrationDone = true;
    }
    _executeTareMode();
    _mode = ScaleModes::NORMAL;
    Serial.println("Calibration slope:");
    Serial.println(_scaleCalibrationSlope);
    Serial.println("Calibration intercept:");
    Serial.println(_scaleCalibrationIntercept);
}

void Scale::_executeCountMode() {
    int numberOfParts = 0;

    _executeTareMode();

    while (_userInterface.readButtons() == Buttons::up) {
        _regulateScale();
        _userInterface.displayStability(_isPositionStable());
        _userInterface.displayMass(getMassInGrams(), _unit);
    }
    _userInterface.displayMenuInstructions("Placer modele");
    while(_userInterface.readButtons() != Buttons::select){
        _regulateScale();
        _userInterface.displayMass(getMassInGrams(), _unit);
        _userInterface.displayStability(_isPositionStable());

        if(_userInterface.readButtons() == Buttons::left){
            _executeTareMode();
        }
    }
    double modelUnitMass = getMassInGrams();

    while(_userInterface.readButtons() == Buttons::select){}
    _userInterface.clearMenuInstructionsZone();

    while(_userInterface.readButtons() != Buttons::select){
        _regulateScale();

        double mass = getMassInGrams();
        numberOfParts = lround(mass/modelUnitMass);
        if (numberOfParts<0){
            numberOfParts=0;
        }
        _userInterface.displayMenuInstructions(String(numberOfParts));
        _userInterface.displayMass(mass, _unit);
    }
    _userInterface.clearMenuInstructionsZone();
    _mode = ScaleModes::NORMAL;
}

void Scale::_executeTareMode() {
    _userInterface.clearMassZone();
    _regulateScale();
    while (!_isPositionStable()) {
        _regulateScale();
        _userInterface.displayStability(_isPositionStable());
    }
    double stableMass = _getAbsoluteMass();
    _tareMassOffset = stableMass;
}

double Scale::getMassInGrams() {
    return _getAbsoluteMass() - _tareMassOffset;
}
double Scale::_getAbsoluteMass() {
    double actuatorCurrent = _actuatorCurrentSensor.getAverageCurrent(); //todo try with filteredCurrent if necessary
    double forceNAppliedByActuator = _actuator.getAppliedForceNFromCurrentA(actuatorCurrent);
    double massGrams = forceNAppliedByActuator * _scaleCalibrationSlope + _scaleCalibrationIntercept;

    return massGrams;
}

bool Scale::_isPositionStable() {
    double currentValue = _distanceSensor.getAverageDistanceMm();
    double lowerBound = _positionRegulator.setpoint * (1.0 - TOLERANCE_PERCENTAGE_FOR_STABILITY / 100.0);
    double upperBound = _positionRegulator.setpoint * (1.0 + TOLERANCE_PERCENTAGE_FOR_STABILITY / 100.0);

    if (currentValue >= lowerBound && currentValue <= upperBound) {
        if (_timestampFirstInsideStabilityZone == 0) {
            _timestampFirstInsideStabilityZone = millis();
        }
        if (millis() - _timestampFirstInsideStabilityZone >= TIME_REQUIRED_FOR_STABILITY_MS) {
            return true;
        }
    } else {
        _timestampFirstInsideStabilityZone = 0;
    }
    return false;
}

void Scale::_setModeFromButtonsState(){
    Buttons button = _userInterface.readButtons();
    switch(button) {
        case Buttons::left:
            _mode = ScaleModes::TARE;
            break;
        case Buttons::down:
            _mode = ScaleModes::CALIBRATION;
            break;
        case Buttons::up:
            _mode = ScaleModes::COUNT;
            break;
        default:
            break;
    }

}

void Scale::_waitForButtonPressAndStabilization(Buttons button){
    bool isScaleStable = false;
    while(_userInterface.readButtons() != button or not isScaleStable) {
        _regulateScale();
        _userInterface.displayStability(_isPositionStable());
        isScaleStable = _isPositionStable();
    }
}

bool Scale::_isRefreshDue(unsigned long &lastRefreshTime) {
    unsigned long currentTime = millis();
    if (currentTime - lastRefreshTime >= REGULATION_REFRESH_INTERVAL_MS) {
        lastRefreshTime = currentTime;
        return true;
    }
    return false;

}

void Scale:: _setUnitsFromButtonState(){
    if(_userInterface.readButtons() == Buttons::right
        and millis() > _lastTimeUnitWasChanged + MIN_TIME_BETWEEN_UNIT_SWAP_MS){
        if (_unit == Units::GRAMS){
            _unit = Units::OUNCES;
        } else{
            _unit = Units::GRAMS;
        }
        _lastTimeUnitWasChanged = millis();
    }
}

void Scale::_useNextAveragingPreset() {
    _currentAverageTimePresetIndex = (_currentAverageTimePresetIndex + 1) % _averageTimePresetsMs.size();
    unsigned long newTimePresetMs = _averageTimePresetsMs[_currentAverageTimePresetIndex];
    _distanceSensor.setSampleSize(newTimePresetMs);
    _actuatorCurrentSensor.setSampleSize(newTimePresetMs);
}