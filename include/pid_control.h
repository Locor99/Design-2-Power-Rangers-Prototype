#ifndef DESIGN2_PROTOTYPE_PID_CONTROL_H
#define DESIGN2_PROTOTYPE_PID_CONTROL_H
#include <PID_v1.h>

class PidParameters {
public:
    double Kp;
    double Ki;
    double Kd;

    explicit PidParameters(double kp = 0.0, double ki = 0.0, double kd = 0.0) : Kp(kp), Ki(ki), Kd(kd) {}
};

class PidController {
private:
    PidParameters _pidParameters;
    double _setpoint, _input, _output;
    PID _pid;

public:
    PidController(const PidParameters& pidParameters);

    void setSetpoint(double setpoint);
    void setInput(double input);
    double getOutput() const;
    void compute();

    // Méthode pour ajuster dynamiquement les paramètres du PID
    void updateParameters(const PidParameters& params);
};

#endif //DESIGN2_PROTOTYPE_PID_CONTROL_H
