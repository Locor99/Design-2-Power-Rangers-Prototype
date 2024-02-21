#include "scale.h"

Scale::Scale(Display &display, DistanceSensor &distanceSensor, CurrentSensor &currentSensor, Actuator &actuator,
             PidController &pidController) :
        _display(display), _distanceSensor(distanceSensor), _actuatorCurrentSensor(currentSensor), _actuator(actuator), _pidController(pidController){
    _mode = ScaleModes::NORMAL;
    _pidController.setSetpoint(1.87);//todo faire qqch de propre pour ça
}

void Scale::executeMainLoop() {
    switch(_mode) {
        //display.announce_mode..? lcd screen tells the mode for 1-2 seconds
        case ScaleModes::NORMAL:
            Serial.println("Normal mode");
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

    // get the mode

}

void Scale::executeNormalMode() {
    _regulateScale();
    _display.displayMass(_actuatorCurrentSensor.getCurrent());//todo calculate mass and inject here
}

void Scale::_regulateScale() {
    double distanceSensorVoltage = _distanceSensor.getPhysicalFilteredValue();
    Serial.print("distance sensor voltage:");
    Serial.println(distanceSensorVoltage);//todo clean
    _pidController.setInput(distanceSensorVoltage);

    double outputVoltage = _pidController.computeOutput();//todo clean
    Serial.print("output voltage given to actuator:");
    Serial.println(outputVoltage);
    _actuator.setVoltage(outputVoltage);
    delay(100);
}

void Scale::calibrate() {

}

void Scale::execute_count_mode() {

}

void Scale::tare() {

}
