#ifndef DESIGN2_PROTOTYPE_SCALE_H
#define DESIGN2_PROTOTYPE_SCALE_H

#include "user_interface.h"
#include "DistanceSensor.h"
#include "hardware_config.h"
#include "Actuator.h"
#include "pid_control.h"
#include "current_sensor.h"
#include "units.h"

enum class ScaleModes {
    NORMAL,
    TARE,
    CALIBRATION,
    COUNT
};

String scaleModeToString(ScaleModes mode);

class Scale {
public:
    Scale(UserInterface &display, DistanceSensor &distanceSensor, CurrentSensor &currentSensor,
          Actuator &actuator, PidController &positionRegulator, PidController &currentRegulator,
          double scaleCalibSlope, double scaleCalibIntercept);
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
    void _setModeFromButtonsState();
    void _waitForButtonPressAndStabilization(Buttons button);
    bool _isRefreshDue(unsigned long &lastRefreshTime);
    void _setUnitsFromButtonState();

    UserInterface& _userInterface;
    DistanceSensor& _distanceSensor;
    CurrentSensor& _actuatorCurrentSensor;
    Actuator& _actuator;
    PidController& _positionRegulator;
    PidController& _currentRegulator;
    ScaleModes _mode;
    double _scaleCalibrationSlope; // Ratio between the mass on the scale (g) and the force applied by actuator (N)
    double _scaleCalibrationIntercept;
    double _tareMassOffset = 0.0;
    unsigned long _timestampFirstInsideStabilityZone = 0;
    static const unsigned long DEFAULT_TIME_BEFORE_STABILITY_MS = 1;
    constexpr static double DEFAULT_STABILITY_POURCENTAGE = 5.0;
    unsigned long _lastRegulatedTime = 0;
    unsigned long _lastTimeUnitWasChanged = 0;
    Units _unit;


};


#endif //DESIGN2_PROTOTYPE_SCALE_H
