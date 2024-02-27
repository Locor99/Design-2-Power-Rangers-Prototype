#include "DistanceSensor.h"

DistanceSensor::DistanceSensor(int pin, double distanceMmToVoltageSlope, double distanceMmToVoltageIntercept)
        : AnalogSensor(pin, distanceMmToVoltageSlope, distanceMmToVoltageIntercept) {}

double DistanceSensor::getDistanceMm() {
    return getPhysicalValue();
}

double DistanceSensor::getFilteredDistanceMm() {
    return getPhysicalFilteredValue();
}
