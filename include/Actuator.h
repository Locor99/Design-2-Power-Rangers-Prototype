#ifndef ACTUATOR_H
#define ACTUATOR_H

#include <Arduino.h>
#include "dac.h"

class Actuator {
public:
    Actuator(DacMCP4725 &dac);
    void setVoltage(double voltage);

    private:
    DacMCP4725& _dac;
};

#endif // ACTUATOR_H
