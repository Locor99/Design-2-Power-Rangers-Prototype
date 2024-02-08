#ifndef DESIGN2_PROTOTYPE_SCALE_H
#define DESIGN2_PROTOTYPE_SCALE_H

#include "display.h"
#include "DistanceSensor.h"
#include "hardware_config.h"
#include "Actuator.h"


enum class ScaleModes {
    NORMAL,
    TARE,
    CALIBRATION
};

class Scale {
public:
    Scale(Display& display, DistanceSensor& distanceSensor, Actuator& actuator);
    void executeMainLoop();

private:
    void _executeNormalMode();
    void _calibrate();
    void _tare();

    Display& _display;
    DistanceSensor& _distanceSensor;
    Actuator& _actuator;
    ScaleModes _mode;
};


#endif //DESIGN2_PROTOTYPE_SCALE_H
