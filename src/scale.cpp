#include "scale.h"

const unsigned int TIME_REQUIRED_FOR_STABILITY_MS = 1000;
const unsigned int TOLERANCE_PERCENTAGE_FOR_STABILITY = 5;

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

Scale::Scale(UserInterface &display, DistanceSensor &distanceSensor, CurrentSensor &currentSensor, Actuator &actuator,
             PidController &pidController, double scaleCalibSlope, double scaleCalibIntercept) :
        _display(display), _distanceSensor(distanceSensor), _actuatorCurrentSensor(currentSensor), _actuator(actuator),
        _pidController(pidController), _scaleCalibrationSlope(scaleCalibSlope), _scaleCalibrationIntercept(scaleCalibIntercept){
    _mode = ScaleModes::NORMAL;
    _executeTareMode();
}

[[noreturn]] void Scale::executeMainLoop() {
    while (true){
        _regulateScale();
        _display.displayStability(_isPositionStable());
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
    _display.displayMass(getMassInGrams());
}

void Scale::_regulateScale() { //todo add a max frequency with Millis()
    _pidController.input = _distanceSensor.getFilteredDistanceMm();
    double voltageSentToDac = _pidController.computeOutput();
    _actuator.setVoltage(voltageSentToDac);
}

void Scale::_executeCalibrationMode() { //todo clean
    _display.displayMass(0);
    bool calibrationDone = false;
    while (not calibrationDone){
        Serial.println("calib 1");
        while(_display.readButtons() == Buttons::left){
            Serial.println("calib 2");
            _regulateScale();
            _display.displayStability(_isPositionStable());
        };

        bool isScaleStable = false;
        while(_display.readButtons() != Buttons::select or not isScaleStable){ // avec un 0g
            Serial.println("calib 3");
            _regulateScale();
            _display.displayStability(_isPositionStable());
            isScaleStable = _isPositionStable();
        }
        double massVsForceX1 = _actuator.getAppliedForceNFromCurrentA(_actuatorCurrentSensor.getCurrent());

        while(_display.readButtons() == Buttons::select){
            Serial.println("calib 4");
        };

        isScaleStable = false;
        while(_display.readButtons() != Buttons::select or not isScaleStable){ // avec un 50g
            Serial.println("calib 5");
            _regulateScale();
            _display.displayStability(_isPositionStable());
            isScaleStable = _isPositionStable();
        }
        while(_display.readButtons() == Buttons::select){
            Serial.println("calib 6");
        };

        double massVsForceX2 = _actuator.getAppliedForceNFromCurrentA(_actuatorCurrentSensor.getCurrent());

        _scaleCalibrationSlope = (50-0)/(massVsForceX2-massVsForceX1);//todo clean
        _scaleCalibrationIntercept = 0 - _scaleCalibrationSlope * massVsForceX1;
        calibrationDone = true;
    }
    Serial.println("calib 7");
    _mode = ScaleModes::NORMAL;

}

void Scale::_executeCountMode() {

}

void Scale::_executeTareMode() {
    //todo ajouter l'indicateur de stabilisation dans le tare (généraliser ça si possible)
    while (!_isPositionStable()) {//todo ajouter constantes
        _regulateScale();
        _display.displayMass(getMassInGrams());
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
    double lowerBound = _pidController.setpoint * (1.0 - TOLERANCE_PERCENTAGE_FOR_STABILITY / 100.0);
    double upperBound = _pidController.setpoint * (1.0 + TOLERANCE_PERCENTAGE_FOR_STABILITY / 100.0);

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