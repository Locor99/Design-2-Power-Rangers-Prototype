#include "scale.h"

Scale::Scale(Display &display, DistanceSensor &distanceSensor, CurrentSensor &currentSensor, Actuator &actuator,
             PidController &pidController) :
        _display(display), _distanceSensor(distanceSensor), _actuatorCurrentSensor(currentSensor), _actuator(actuator), _pidController(pidController){
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
    }

}

void Scale::executeNormalMode() {
    _regulateScale();
    _display.displayMass(_actuatorCurrentSensor.getCurrent());//todo calculate mass and inject here
}

void Scale::_regulateScale() {
    _pidController.input = _distanceSensor.getPhysicalFilteredValue();
    Serial.println("input in controller:");
    Serial.println(_pidController.input);
    double refreshedOutput = _pidController.computeOutput();
    _actuator.setVoltage(refreshedOutput);
}

void Scale::calibrate() {

}

void Scale::execute_count_mode() {

}

void Scale::tare() {

}
