#ifndef DESIGN2_PROTOTYPE_SCALE_H
#define DESIGN2_PROTOTYPE_SCALE_H

#include "display.h"
#include "DistanceSensor.h"
#include "hardware_config.h"
#include "Actuator.h"
#include "pid_control.h"
#include "current_sensor.h"


enum class ScaleModes {
    NORMAL,
    TARE,
    CALIBRATION,
    COUNT
};

class Scale {
public:
    Scale(Display &display, DistanceSensor &distanceSensor, CurrentSensor &currentSensor, Actuator &actuator,
          PidController &pidController);
    void executeMainLoop();
    void executeNormalMode();
    void calibrate();
    void execute_count_mode();
    void tare();

private:
    void _regulateScale();

    Display& _display;
    DistanceSensor& _distanceSensor;
    CurrentSensor& _actuatorCurrentSensor;
    Actuator& _actuator;
    PidController& _pidController;
    ScaleModes _mode;
};


#endif //DESIGN2_PROTOTYPE_SCALE_H
