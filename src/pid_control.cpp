#include "pid_control.h"

PidController::PidController(const PidParameters& pidParameters)
        : _pidParameters(pidParameters),
          _pid(&_input, &_output, &_setpoint, pidParameters.Kp, pidParameters.Ki, pidParameters.Kd, DIRECT){

    _pid.SetMode(AUTOMATIC);
    _pid.SetOutputLimits(pidParameters.outputLowerBound, pidParameters.outputUpperBound);
}

void PidController::setSetpoint(double setpoint) {
    _setpoint = setpoint;
}

void PidController::setInput(double input) {
    _input = input;
}

double PidController::computeOutput() {
    _pid.Compute();
    return _output;
}

void PidController::updateParameters(const PidParameters& parameters) {
    _pidParameters = parameters;
    _pid.SetTunings(_pidParameters.Kp, _pidParameters.Ki, _pidParameters.Kd);
}
