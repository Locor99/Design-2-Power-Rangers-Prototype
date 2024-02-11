#include "pid_control.h"

PidController::PidController(const PidParameters& pidParameters)
        : _pidParameters(pidParameters),
          _pid(&_input, &_output, &_setpoint, pidParameters.Kp, pidParameters.Ki, pidParameters.Kd, DIRECT){

    _pid.SetMode(AUTOMATIC);
    _pid.SetOutputLimits(0, 255); //todo add real values
}

void PidController::setSetpoint(double setpoint) {
    _setpoint = setpoint;
}

void PidController::setInput(double input) {
    _input = input;
}

double PidController::getOutput() const {
    return _output;
}

void PidController::compute() {
    _pid.Compute();
}

void PidController::updateParameters(const PidParameters& params) {
    _pidParameters = params;
    _pid.SetTunings(_pidParameters.Kp, _pidParameters.Ki, _pidParameters.Kd);
}
