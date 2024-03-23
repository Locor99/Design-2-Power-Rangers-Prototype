#include "current_sensor.h"

CurrentSensor::CurrentSensor(int pin,
                             double currentAmpsToVoltageSlope,
                             double currentAmpsToVoltageIntercept,
                             unsigned int sampleSize,
                             unsigned long minSampleIntervalMs)
        : AnalogSensor(pin, currentAmpsToVoltageSlope, currentAmpsToVoltageIntercept, sampleSize, minSampleIntervalMs) {}

double CurrentSensor::getCurrent() {
    return getPhysicalValue();
}

double CurrentSensor::getFilteredCurrent() {
    return getPhysicalAverageValue();
}
