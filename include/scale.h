#ifndef DESIGN2_PROTOTYPE_SCALE_H
#define DESIGN2_PROTOTYPE_SCALE_H

#include "display.h"
#include "DistanceSensor.h"
#include "hardware_config.h"
#include "Actuator.h"
#include "pid_control.h"
#include "current_sensor.h"
#include "CircularBuffer.h"

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
          PidController &pidController, double scaleCalibSlope, double scaleCalibIntercept);
    void executeMainLoop();
    void executeNormalMode();
    void calibrate();
    void execute_count_mode();
    void tare();

private:
    void _regulateScale();
    double _calculateMassOnScale();
    bool _isStableAroundSetpoint(double setpoint, double tolerancePercentage);
    bool _isPositionStable(double setpoint, double tolerancePourcentage, unsigned long timeRequiredInStabilityZoneMs);

    Display& _display;
    DistanceSensor& _distanceSensor;
    CurrentSensor& _actuatorCurrentSensor;
    Actuator& _actuator;
    PidController& _pidController;
    ScaleModes _mode;
    double _scaleCalibrationSlope; // Ratio between the force applied by actuator (N) and the mass on the scale (g)
    double _scaleCalibrationIntercept;
    double _scaleCalibrationConstant; // Ratio between the force applied by actuator (N) and the mass on the scale (g)

    unsigned long _timestampFirstInsideStabilityZone = 0;
    static const unsigned long DEFAULT_TIME_BEFORE_STABILITY_MS = 1;

};


#endif //DESIGN2_PROTOTYPE_SCALE_H
