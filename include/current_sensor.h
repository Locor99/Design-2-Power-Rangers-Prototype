#ifndef DESIGN2_PROTOTYPE_CURRENT_SENSOR_H
#define DESIGN2_PROTOTYPE_CURRENT_SENSOR_H

#include "analog_sensor.h"

class CurrentSensor : public AnalogSensor {
public:
    CurrentSensor(int pin,
                  double currentAmpsToVoltageSlope,
                  double currentAmpsToVoltageIntercept,
                  unsigned int sampleSize,
                  unsigned long minSampleIntervalMs);

    double getCurrent();
    double getAverageCurrent();
};

#endif //DESIGN2_PROTOTYPE_CURRENT_SENSOR_H
