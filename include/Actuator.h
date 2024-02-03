#ifndef ACTUATOR_H
#define ACTUATOR_H

#include <Arduino.h>
#include "dac.h"

class Actuator {
public:
    Actuator(double minForceN, double maxForceN, DacMCP4725& dac);
    double getActualForceN();
    void setForceN(double forceSetpoint);
private:
    double _minForceN, _maxForceN;
    double _actualForceN;
    double _forceNToDacOutSlope, _forceNToDacIntercept;
    DacMCP4725& _dac;
};

#endif // ACTUATOR_H
