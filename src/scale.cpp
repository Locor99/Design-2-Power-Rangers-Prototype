#include "scale.h"
Scale::Scale(Display &display, DistanceSensor &distanceSensor, CurrentSensor &currentSensor, Actuator &actuator,
             PidController &pidController, double scaleCalibRatio) :
        _display(display), _distanceSensor(distanceSensor), _actuatorCurrentSensor(currentSensor), _actuator(actuator),
        _pidController(pidController), _scaleCalibrationConstant(scaleCalibRatio){
    _mode = ScaleModes::NORMAL;
    _stabilityBuffer = CircularBuffer<double, 10>();
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
    }

}

void Scale::executeNormalMode() {
    _regulateScale();
    double mass = _calculateMassOnScale();
    _display.displayMass(mass);
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

}

double Scale::_calculateMassOnScale() {
    double actuatorCurrent = _actuatorCurrentSensor.getCurrent();
    double forceNAppliedByActuator = _actuator.getAppliedForceNFromCurrentA(actuatorCurrent);
    return forceNAppliedByActuator * _scaleCalibrationConstant;
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


