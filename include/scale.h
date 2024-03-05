#ifndef DESIGN2_PROTOTYPE_SCALE_H
#define DESIGN2_PROTOTYPE_SCALE_H

#include "user_interface.h"
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

String scaleModeToString(ScaleModes mode);

class Scale {
    constexpr static size_t STABILITY_BUFFER_SIZE = 10;
public:
    Scale(UserInterface &display, DistanceSensor &distanceSensor, CurrentSensor &currentSensor, Actuator &actuator,
          PidController &pidController, double scaleCalibSlope, double scaleCalibIntercept);
    double getMassInGrams();

    [[noreturn]] void executeMainLoop();

private:
    void _executeActiveMode();
    void _executeNormalMode();
    void _executeCalibrationMode();
    void _executeCountMode();
    void _executeTareMode();
    void _regulateScale();
    bool _isPositionStable();
    double _getAbsoluteMass();

    UserInterface& _display;
    DistanceSensor& _distanceSensor;
    CurrentSensor& _actuatorCurrentSensor;
    Actuator& _actuator;
    PidController& _pidController;
    ScaleModes _mode;
    double _scaleCalibrationSlope; // Ratio between the mass on the scale (g) and the force applied by actuator (N)
    double _scaleCalibrationIntercept;
    double _tareMassOffset = 0.0;
    unsigned long _timestampFirstInsideStabilityZone = 0;
    static const unsigned long DEFAULT_TIME_BEFORE_STABILITY_MS = 1;
    constexpr static double DEFAULT_STABILITY_POURCENTAGE = 5.0;
    unsigned long _lastRegulatedTime = 0;

    void _setModeFromButtonsState();

    void _waitForButtonPressAndStabilization(Buttons button);

    bool _isRefreshDue(unsigned long &lastRefreshTime);

    void _waitForStabilization();
};


#endif //DESIGN2_PROTOTYPE_SCALE_H
