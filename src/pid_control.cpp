#include "pid_control.h"
#include "Arduino.h"

PidController::PidController(double kp, double ki, double kd, bool direction)
        : kp(kp), _pid(&input, &output, &setpoint, kp, ki, kd, direction){
    _pid.SetMode(AUTOMATIC);
}

double PidController::computeOutput() {
    _pid.Compute();
    Serial.println("output dac:");
    Serial.println(output);
    return output;
}

void PidController::setOutputLimits(double min, double max) {
    _pid.SetOutputLimits(min, max);
}
