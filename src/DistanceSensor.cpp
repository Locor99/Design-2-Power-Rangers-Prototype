#include "DistanceSensor.h"
#include "hardware_config.h"

DistanceSensor::DistanceSensor(int pin, double distanceMmVsVoltageSlope, double distanceMmVsVoltageIntercept):
        _pin(pin), _distanceMmVsVoltageSlope(distanceMmVsVoltageSlope),
        _distanceMmVsVoltageIntercept(distanceMmVsVoltageIntercept) {

    pinMode(_pin, INPUT);
}

double DistanceSensor::readDistanceMm() {
    int analogInputValue = analogRead(_pin);
    double sensorVoltage = static_cast<double>(analogInputValue) /
                           ArduinoConfig::ANALOG_INPUT_MAX_VALUE * ArduinoConfig::ANALOG_INPUT_MAX_VOLTAGE ;
    double distanceMm = _distanceMmVsVoltageSlope * sensorVoltage + _distanceMmVsVoltageIntercept;
    return distanceMm;
}

