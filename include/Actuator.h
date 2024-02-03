#ifndef ACTUATOR_H
#define ACTUATOR_H

#include <Arduino.h>
#include "hardware_config.h"

class Actuator {
public:
    Actuator(int pin, double minForceN, double maxForceN);
    double getActualForceN();
    void setForceNewton(double force);

private:
    int _pin;
    double _forceToPwmOutSlope;
    double _forceToPwmIntercept;
    double _minForceN;
    double _maxForceN;
    double _actualForceN = 0;
};

#endif // ACTUATOR_H
