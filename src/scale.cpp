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
    tare();
}

void Scale::executeMainLoop() {
    while (true){
        switch(_mode) {
            case ScaleModes::NORMAL:
                executeNormalMode();
                break;
            case ScaleModes::TARE :
                tare();
                break;
            case ScaleModes::CALIBRATION :
                calibrate();
                break;
            case ScaleModes::COUNT :
                execute_count_mode();
                break;
        }
        _setModeFromButtonsState();
        _display.displayMode(scaleModeToString(_mode));

        _display.markAsStable(_isPositionStable(_pidController.setpoint,
                                                TOLERANCE_PERCENTAGE_FOR_STABILITY,
                                                TIME_REQUIRED_FOR_STABILITY_MS));

    }

}

void Scale::executeNormalMode() {
    _regulateScale();
    _display.displayMass(getMassInGrams());
}

void Scale::_regulateScale() {
    _pidController.input = _distanceSensor.getFilteredDistanceMm();
    double voltageSentToDac = _pidController.computeOutput();
    _actuator.setVoltage(voltageSentToDac);
}

void Scale::calibrate() {

}

void Scale::execute_count_mode() {

}

void Scale::tare() {
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

bool Scale::_isPositionStable(double setpoint,
                              double tolerancePourcentage,
                              unsigned long timeRequiredInStabilityZoneMs = DEFAULT_TIME_BEFORE_STABILITY_MS) {
    double currentValue = _calculateMassOnScale();
    double lowerBound = setpoint * (1.0 - tolerancePourcentage / 100.0);
    double upperBound = setpoint * (1.0 + tolerancePourcentage / 100.0);

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


