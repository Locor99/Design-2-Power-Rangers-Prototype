#include "scale.h"

Scale::Scale(Display& display, DistanceSensor& distanceSensor,
             Actuator& actuator,PidController pidController):
    _display(display), _distanceSensor(distanceSensor), _actuator(actuator), _pidController(pidController){
    _mode = ScaleModes::NORMAL;
}

void Scale::executeMainLoop() {
    switch(_mode) {
        //display.announce_mode..? lcd screen tells the mode for 1-2 seconds
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

    // get the mode

}

void Scale::executeNormalMode() {
    _regulateScale();
    analogRead(ArduinoConfig::CURRENT_SENSOR_PIN);
    _display.displayMass();
}

void Scale::_regulateScale() {
    _pidController.setInput(_distanceSensor.readDistanceMm());
    double outputInPercentage = _pidController.computeOutput();
    _actuator.setOutputInPercentage(outputInPercentage);
}
