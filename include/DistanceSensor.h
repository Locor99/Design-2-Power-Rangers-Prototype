#ifndef DISTANCESENSOR_H
#define DISTANCESENSOR_H

#include "analog_sensor.h"

class DistanceSensor : public AnalogSensor {
public:
    DistanceSensor(int pin,
                   double distanceMmToVoltageSlope,
                   double distanceMmToVoltageIntercept,
                   unsigned int sampleSize,
                   unsigned long minSampleIntervalMs);
    double getDistanceMm();
    double getFilteredDistanceMm();
};

#endif // DISTANCESENSOR_H
