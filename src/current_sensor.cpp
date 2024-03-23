#include "current_sensor.h"

CurrentSensor::CurrentSensor(int pin,
                             double currentAmpsToVoltageSlope,
                             double currentAmpsToVoltageIntercept,
                             unsigned int sampleSize,
                             unsigned long minSampleIntervalMs)
        : AnalogSensor(pin, currentAmpsToVoltageSlope, currentAmpsToVoltageIntercept) {}

double CurrentSensor::getCurrent() {
    return getPhysicalValue();
}

double CurrentSensor::getAverageCurrent() {
    return getPhysicalAverageValue();
}
