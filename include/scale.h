#ifndef DESIGN2_PROTOTYPE_SCALE_H
#define DESIGN2_PROTOTYPE_SCALE_H

#include "display.h"
#include "DistanceSensor.h"
#include "hardware_config.h"
#include "Actuator.h"
#include "pid_control.h"
#include "current_sensor.h"
#include "CircularBuffer.h"

static const double GRAVITY_ACCELERATION = 9.81;
static const double DEFAULT_SCALE_CALIB = GRAVITY_ACCELERATION*1000;

enum class ScaleModes {
    NORMAL,
    TARE,
    CALIBRATION,
    COUNT
};

class Scale {
    constexpr static size_t STABILITY_BUFFER_SIZE = 10;
public:
    Scale(Display &display, DistanceSensor &distanceSensor, CurrentSensor &currentSensor, Actuator &actuator,
          PidController &pidController, double scaleCalibRatio=DEFAULT_SCALE_CALIB);
    double getMassInGrams();
    void executeMainLoop();
    void executeNormalMode();
    void calibrate();
    void execute_count_mode();
    void tare();

private:
    void _regulateScale();
    bool _isPositionStable(double setpointMm,
                           double tolerancePourcentage=DEFAULT_STABILITY_POURCENTAGE,
                           unsigned long timeRequiredInStabilityZoneMs=DEFAULT_TIME_BEFORE_STABILITY_MS);
    double _getAbsoluteMass();

    Display& _display;
    DistanceSensor& _distanceSensor;
    CurrentSensor& _actuatorCurrentSensor;
    Actuator& _actuator;
    PidController& _pidController;
    ScaleModes _mode;
    double _scaleCalibrationConstant; // Ratio between the force applied by actuator (N) and the mass on the scale (g)
    double _tareMassOffset = 0.0;
    unsigned long _timestampFirstInsideStabilityZone = 0;
    static const unsigned long DEFAULT_TIME_BEFORE_STABILITY_MS = 1;
    constexpr static double DEFAULT_STABILITY_POURCENTAGE = 5.0;

};


#endif //DESIGN2_PROTOTYPE_SCALE_H
