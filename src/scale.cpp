#include "scale.h"
Scale::Scale(Display &display, DistanceSensor &distanceSensor, CurrentSensor &currentSensor, Actuator &actuator,
             PidController &pidController, double scaleCalibRatio) :
        _display(display), _distanceSensor(distanceSensor), _actuatorCurrentSensor(currentSensor), _actuator(actuator),
        _pidController(pidController), _scaleCalibrationConstant(scaleCalibRatio){
    _mode = ScaleModes::NORMAL;
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
        delay(10);
        // todo get the mode

        if (_isPositionStable(_pidController.setpoint)){
            Serial.println("Position stable");//todo ajouter indicateur réel
        }
        else{
            Serial.println("Position non stable");
        }
    }

}

void Scale::executeNormalMode() {
    _regulateScale();
    _display.displayMass(getMassInGrams());
}

void Scale::_regulateScale() {
    _pidController.input = _distanceSensor.getFilteredDistanceMm();
    Serial.println("Distance(mm): ");//todo remove
    Serial.println(_pidController.input);//todo remove

    double voltageSentToDac = _pidController.computeOutput();
    Serial.println("Voltage au dac: ");//todo remove
    Serial.println(voltageSentToDac);//todo remove
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
    double actuatorCurrent = _actuatorCurrentSensor.getCurrent();
    double forceNAppliedByActuator = _actuator.getAppliedForceNFromCurrentA(actuatorCurrent);
    return forceNAppliedByActuator * _scaleCalibrationConstant;
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


