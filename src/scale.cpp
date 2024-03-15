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
            return "CALIBRATION";
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
        _display.displayStability(_isPositionStable(_pidController.setpoint,
                                                    TOLERANCE_PERCENTAGE_FOR_STABILITY,
                                                    TIME_REQUIRED_FOR_STABILITY_MS));
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

void Scale::_regulateScale() {
    _pidController.input = _distanceSensor.getFilteredDistanceMm();
    double voltageSentToDac = _pidController.computeOutput();
    _actuator.setVoltage(voltageSentToDac);
}

void Scale::_executeCalibrationMode() {

}

void Scale::_executeCountMode() {

}

void Scale::_executeTareMode() {
    Serial.println("Tare en cours");
    //todo ajouter l'indicateur de stabilisation dans le tare (généraliser ça si possible)
    while (!_isPositionStable(_pidController.setpoint)) {//todo ajouter constantes
        _regulateScale();
        _display.displayMass(getMassInGrams());
    }
    double stableMass = _getAbsoluteMass();
    _tareMassOffset = stableMass;
    Serial.println("Tare complété");
    _mode = ScaleModes::NORMAL;

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

bool Scale::_isPositionStable(double setpointMm,
                              double tolerancePourcentage,
                              unsigned long timeRequiredInStabilityZoneMs) {
    double currentValue = _distanceSensor.getDistanceMm();
    double lowerBound = setpointMm * (1.0 - tolerancePourcentage / 100.0);
    double upperBound = setpointMm * (1.0 + tolerancePourcentage / 100.0);

    if (currentValue >= lowerBound && currentValue <= upperBound) {
        if (_timestampFirstInsideStabilityZone == 0) {
            _timestampFirstInsideStabilityZone = millis();
        }
        if (millis() - _timestampFirstInsideStabilityZone >= timeRequiredInStabilityZoneMs) {
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
        default:
            break;
    }

}