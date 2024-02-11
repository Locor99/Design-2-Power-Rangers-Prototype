#include "scale.h"

Scale::Scale(Display& display, DistanceSensor& distanceSensor, Actuator& actuator):
    _display(display), _distanceSensor(distanceSensor), _actuator(actuator){
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

}