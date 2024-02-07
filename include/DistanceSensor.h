#ifndef DISTANCESENSOR_H
#define DISTANCESENSOR_H

#include <Arduino.h>
#include "HardwareConfig.h"

class DistanceSensor {
public:
    DistanceSensor(int pin, double minReadableDistanceMm, double maxReadableDistanceMm);
    double readDistanceMm();

private:
    int _pin;
    double _minReadableDistanceMm;
    double _maxReadableDistanceMm;
    double _signalToDistanceSlope;
};

#endif // DISTANCESENSOR_H
