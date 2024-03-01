#ifndef DESIGN2_PROTOTYPE_SCALE_H
#define DESIGN2_PROTOTYPE_SCALE_H

#include "display.h"
#include "DistanceSensor.h"
#include "hardware_config.h"
#include "Actuator.h"
#include "pid_control.h"
#include "current_sensor.h"

static const double GRAVITY_ACCELERATION = 9.81;
static const double DEFAULT_SCALE_CALIB = GRAVITY_ACCELERATION*1000;

enum class ScaleModes {
    NORMAL,
    TARE,
    CALIBRATION,
    COUNT
};

class Scale {
public:
    Scale(Display &display, DistanceSensor &distanceSensor, CurrentSensor &currentSensor, Actuator &actuator,
          PidController &pidController, double scaleCalibRatio=DEFAULT_SCALE_CALIB);
    void executeMainLoop();
    void executeNormalMode();
    void calibrate();
    void execute_count_mode();
    void tare();

private:
    void _regulateScale();
    double _calculateMassOnScale();

    Display& _display;
    DistanceSensor& _distanceSensor;
    CurrentSensor& _actuatorCurrentSensor;
    Actuator& _actuator;
    PidController& _pidController;
    ScaleModes _mode;
    double _scaleCalibrationConstant; // Ratio between the force applied by actuator (N) and the mass on the scale (g)
};


#endif //DESIGN2_PROTOTYPE_SCALE_H
