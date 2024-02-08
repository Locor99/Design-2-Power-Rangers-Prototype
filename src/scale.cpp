//
// Created by louis on 2024-02-08.
//

#include "scale.h"

Scale::Scale(Display& display, DistanceSensor& distanceSensor, Actuator& actuator):
    _display(display), _distanceSensor(distanceSensor), _actuator(actuator){
    _mode = ScaleModes::NORMAL;
}

void Scale::executeMainLoop() {
    switch(_mode) {
        //display.announce_mode..? lcd screen tells the mode for 1-2 seconds
        case ScaleModes::NORMAL:
            _executeNormalMode();
            break;
        case ScaleModes::TARE :
            _tare();
            break;
        case ScaleModes::CALIBRATION :
            _calibrate();
            break;
    }

    // get the mode

}

void Scale::_executeNormalMode() {

}
