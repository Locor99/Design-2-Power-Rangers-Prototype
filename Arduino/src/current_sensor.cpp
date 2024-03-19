#include "current_sensor.h"

CurrentSensor::CurrentSensor(int pin, double currentAmpsToVoltageSlope, double currentAmpsToVoltageIntercept)
        : AnalogSensor(pin, currentAmpsToVoltageSlope, currentAmpsToVoltageIntercept) {}

double CurrentSensor::getCurrent() {
    return getPhysicalValue();
}

double CurrentSensor::getFilteredCurrent() {
    return getPhysicalFilteredValue();
}
