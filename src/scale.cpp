#include "scale.h"

Scale::Scale(Display &display, DistanceSensor &distanceSensor, CurrentSensor &currentSensor, Actuator &actuator,
             PidController &pidController) :
        _display(display), _distanceSensor(distanceSensor), _actuatorCurrentSensor(currentSensor), _actuator(actuator), _pidController(pidController){
    _mode = ScaleModes::NORMAL;
    _pidController.setSetpoint(ScaleConfig::DISTANCE_SENSOR_TO_BLADE_MM);
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
    _display.displayMass(_actuatorCurrentSensor.getCurrent());//todo calculate mass and inject here
}

void Scale::_regulateScale() {
    _pidController.setInput(_distanceSensor.getDistanceMm());
    _actuator.setVoltage(_pidController.computeOutput());
}
