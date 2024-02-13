#ifndef ANALOGSENSOR_H
#define ANALOGSENSOR_H

#include <Arduino.h>
#include "hardware_config.h"

class AnalogSensor {
protected:
    int _pin;
    double _slope;
    double _intercept;
    virtual double getPhysicalValue();
    double _slope = 1;
    double _intercept = 0;

public:
    AnalogSensor(int pin, double slope, double intercept);
    virtual ~AnalogSensor() = 0;
};

#endif // ANALOGSENSOR_H
