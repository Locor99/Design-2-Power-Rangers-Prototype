#ifndef ANALOGSENSOR_H
#define ANALOGSENSOR_H

#include <Arduino.h>
#include "hardware_config.h"
#include <ArxContainer.h>

class AnalogSensor {
protected:
    int _pin;
    double _slope = 1;
    double _intercept = 0;
    std::vector<double> _samples;
    unsigned int _sampleSize;
    unsigned long _minSampleIntervalMs;
    unsigned long _lastSampleTimeMs;

public:
    AnalogSensor(int pin, double slope, double intercept, unsigned int sampleSize, unsigned long minSampleInterval);
    double getPhysicalAverageValue();
    int getAdcValue() const;
    void setSampleSize(unsigned long timeToAverageMs);

protected:
    double getPhysicalValue() const;

private:
    double _getSamplesAverage() const;
};

#endif // ANALOGSENSOR_H
