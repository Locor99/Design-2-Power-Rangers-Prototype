#include "analog_sensor.h"

AnalogSensor::AnalogSensor(int pin, double slope, double intercept)
        : _pin(pin), _slope(slope), _intercept(intercept) {}

double AnalogSensor::getPhysicalValue() const {
    int analogInputValue = analogRead(_pin);
    double sensorVoltage = static_cast<double>(analogInputValue) /
                           ArduinoConfig::ANALOG_INPUT_MAX_ADC_VALUE * ArduinoConfig::ANALOG_INPUT_MAX_VOLTAGE;
    return _slope * sensorVoltage + _intercept;
}

double AnalogSensor::getPhysicalFilteredValue() {
    double currentValue = getPhysicalValue();
    _lastPhysicalFilteredValue += _filterConstantAlpha * (currentValue - _lastPhysicalFilteredValue);
    return _lastPhysicalFilteredValue;
}

void AnalogSensor::setFilterConstant(double alpha) { _filterConstantAlpha = alpha; }
