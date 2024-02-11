#ifndef DESIGN2_PROTOTYPE_SCALE_H
#define DESIGN2_PROTOTYPE_SCALE_H

#include "display.h"
#include "DistanceSensor.h"
#include "hardware_config.h"
#include "Actuator.h"


enum class ScaleModes {
    NORMAL,
    TARE,
    CALIBRATION,
    COUNT
};

class Scale {
public:
    Scale(Display& display, DistanceSensor& distanceSensor, Actuator& actuator);
    void executeMainLoop();
    void executeNormalMode();
    void calibrate();
    void execute_count_mode();
    void tare();

private:


    Display& _display;
    DistanceSensor& _distanceSensor;
    Actuator& _actuator;
    ScaleModes _mode;
};


#endif //DESIGN2_PROTOTYPE_SCALE_H
