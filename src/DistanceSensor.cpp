#include "DistanceSensor.h"

DistanceSensor::DistanceSensor(int pin,
                               double distanceMmToVoltageSlope,
                               double distanceMmToVoltageIntercept,
                               unsigned int sampleSize,
                               unsigned long minSampleIntervalMs)
        : AnalogSensor(pin, distanceMmToVoltageSlope, distanceMmToVoltageIntercept) {}

double DistanceSensor::getDistanceMm() {
    return getPhysicalValue();
}

double DistanceSensor::getAverageDistanceMm() {
    return getPhysicalAverageValue();
}
