#ifndef DESIGN2_PROTOTYPE_PID_CONTROL_H
#define DESIGN2_PROTOTYPE_PID_CONTROL_H
#include <PID_v1.h>

class PidController {
public:
    double kp, ki, kd;
    double setpoint = 0;
    double input, output;

private:
    PID _pid;

public:
    PidController(double kp, double ki, double kd, bool direction = false);

    double computeOutput();
    void setOutputLimits(double min, double max);
};

#endif //DESIGN2_PROTOTYPE_PID_CONTROL_H
