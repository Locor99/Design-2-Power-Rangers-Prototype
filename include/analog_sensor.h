#ifndef ANALOGSENSOR_H
#define ANALOGSENSOR_H

#include <Arduino.h>
#include "hardware_config.h"

class AnalogSensor {
protected:
    int _pin;
    double _slope = 1;
    double _intercept = 0;
    double _lastPhysicalFilteredValue = 0.0;
    double _filterConstantAlpha = 1;

public:
    AnalogSensor(int pin, double slope, double intercept);
    void setFilterConstant(double alpha);
    int getAdcValue() const;

protected:
    double getPhysicalValue() const;
    double getPhysicalFilteredValue();
};

#endif // ANALOGSENSOR_H
