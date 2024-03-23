#include "DistanceSensor.h"

DistanceSensor::DistanceSensor(int pin,
                               double distanceMmToVoltageSlope,
                               double distanceMmToVoltageIntercept,
                               unsigned int sampleSize,
                               unsigned long minSampleIntervalMs)
        : AnalogSensor(pin, distanceMmToVoltageSlope, distanceMmToVoltageIntercept, sampleSize, minSampleIntervalMs) {}

double DistanceSensor::getDistanceMm() {
    return getPhysicalValue();
}

double DistanceSensor::getFilteredDistanceMm() {
    return getPhysicalFilteredValue();
}
