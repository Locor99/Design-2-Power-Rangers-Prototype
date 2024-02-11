#ifndef DISTANCESENSOR_H
#define DISTANCESENSOR_H

#include <Arduino.h>

class DistanceSensor {
public:
    DistanceSensor(int pin, double distanceMmVsVoltageSlope, double distanceMmVsVoltageIntercept);
    double readDistanceMm();

private:
    int _pin;
    double _distanceMmVsVoltageSlope;
    double _distanceMmVsVoltageIntercept;
};

#endif // DISTANCESENSOR_H
