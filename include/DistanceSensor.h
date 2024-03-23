#ifndef DISTANCESENSOR_H
#define DISTANCESENSOR_H

#include "analog_sensor.h"

class DistanceSensor : public AnalogSensor {
public:
    DistanceSensor(int pin, double distanceMmToVoltageSlope, double distanceMmToVoltageIntercept);
    double getDistanceMm();
    double getAverageDistanceMm();
};

#endif // DISTANCESENSOR_H
