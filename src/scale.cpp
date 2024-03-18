#include "scale.h"

const unsigned int TIME_REQUIRED_FOR_STABILITY_MS = 1000;
const unsigned int TOLERANCE_PERCENTAGE_FOR_STABILITY = 5;
const unsigned int REGULATION_REFRESH_INTERVAL_MS = 10;

String scaleModeToString(ScaleModes mode) {
    switch(mode) {
        case ScaleModes::NORMAL:
            return "NORMAL";
        case ScaleModes::TARE:
            return "TARE";
        case ScaleModes::CALIBRATION:
            return "CALIB";
        case ScaleModes::COUNT:
            return "COUNT";
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
        _display(display),
        _distanceSensor(distanceSensor),
        _actuatorCurrentSensor(currentSensor),
        _actuator(actuator),
        _positionRegulator(positionRegulator),
        _currentRegulator(currentRegulator),
        _scaleCalibrationSlope(scaleCalibSlope),
        _scaleCalibrationIntercept(scaleCalibIntercept){

    _mode = ScaleModes::NORMAL;
    _display.displayMode("Demarrage");
    _executeTareMode();
}

[[noreturn]] void Scale::executeMainLoop() {
    while (true){
        _setModeFromButtonsState();
        _display.displayMode(scaleModeToString(_mode));
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
    _display.displayStability(_isPositionStable());
    _display.displayMass(getMassInGrams());
}

void Scale::_regulateScale() { //todo add a max frequency with Millis()
    if (_isRefreshDue(_lastRegulatedTime)) {
        _positionRegulator.input = _distanceSensor.getFilteredDistanceMm();

        _currentRegulator.setpoint = _positionRegulator.computeOutput();
        _currentRegulator.input = _actuatorCurrentSensor.getCurrent(); //todo filter this or nah..?

        _actuator.setVoltage(_currentRegulator.computeOutput());
    }
}

void Scale::_executeCalibrationMode() {
    _display.clearMassZone();
    _display.displayMass(0);
    const double calibrationMass1 = 0;
    const double calibrationMass2 = 50;
    bool calibrationDone = false;

    while (not calibrationDone) {
        while (_display.readButtons() == Buttons::left) {
            _regulateScale();
            _display.displayStability(_isPositionStable());
        }
        _display.displayMenuInstructions("Ajouter 50g");
        _waitForButtonPressAndStabilization(Buttons::select);
        double massVsForceX2 = _actuator.getAppliedForceNFromCurrentA(_actuatorCurrentSensor.getCurrent());

        while(_display.readButtons() == Buttons::select){}

        _display.displayMenuInstructions("Vider plateau");
        _waitForButtonPressAndStabilization(Buttons::select);
        double massVsForceX1 = _actuator.getAppliedForceNFromCurrentA(_actuatorCurrentSensor.getCurrent());

        _scaleCalibrationSlope = (calibrationMass2 - calibrationMass1) / (massVsForceX2 - massVsForceX1);
        _scaleCalibrationIntercept = calibrationMass1 - _scaleCalibrationSlope * massVsForceX1;
        _display.clearMenuInstructionsZone();
        calibrationDone = true;
    }
    _executeTareMode();
    _mode = ScaleModes::NORMAL;
}

void Scale::_executeCountMode() {

}

void Scale::_executeTareMode() {
    _display.clearMassZone();
    _regulateScale();
    while (!_isPositionStable()) {
        _regulateScale();
        _display.displayStability(_isPositionStable());
    }
    double stableMass = _getAbsoluteMass();
    _tareMassOffset = stableMass;
}

double Scale::getMassInGrams() {
    return _getAbsoluteMass() - _tareMassOffset;
}
double Scale::_getAbsoluteMass() {
    double actuatorCurrent = _actuatorCurrentSensor.getCurrent(); //todo try with filteredCurrent if necessary
    double forceNAppliedByActuator = _actuator.getAppliedForceNFromCurrentA(actuatorCurrent);
    double massGrams = forceNAppliedByActuator * _scaleCalibrationSlope + _scaleCalibrationIntercept;

    return massGrams;
}

bool Scale::_isPositionStable() {
    double currentValue = _distanceSensor.getDistanceMm();
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
    Buttons button = _display.readButtons();
    switch(button) {
        case Buttons::select:
            _mode = ScaleModes::TARE;
            break;
        case Buttons::left:
            _mode = ScaleModes::CALIBRATION;
        default:
            break;
    }

}

void Scale::_waitForButtonPressAndStabilization(Buttons button){
    bool isScaleStable = false;
    while(_display.readButtons() != button or not isScaleStable) {
        _regulateScale();
        _display.displayStability(_isPositionStable());
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