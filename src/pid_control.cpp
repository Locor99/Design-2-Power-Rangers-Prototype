#include "pid_control.h"

PidController::PidController(double kp, double ki, double kd, bool direction)
        : kp(kp), _pid(&_input, &_output, &setpoint, kp, ki, kd, direction){
    _pid.SetMode(AUTOMATIC);
}


double PidController::computeOutput() {
    _pid.Compute();
    return _output;
}

void PidController::setOutputLimits(double min, double max) {
    _pid.SetOutputLimits(min, max);
}
