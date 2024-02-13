#include "analog_sensor.h"

AnalogSensor::AnalogSensor(int pin, double slope, double intercept) : _pin(pin), _slope(slope), _intercept(intercept) {}

double AnalogSensor::getPhysicalValue() {
    int analogInputValue = analogRead(_pin);
    double sensorVoltage = static_cast<double>(analogInputValue) /
                           ArduinoConfig::ANALOG_INPUT_MAX_VALUE * ArduinoConfig::ANALOG_INPUT_MAX_VOLTAGE ;
    return _slope * sensorVoltage + _intercept;
}
