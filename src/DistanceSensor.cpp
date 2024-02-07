#include "DistanceSensor.h"
#include "hardware_config.h"

DistanceSensor::DistanceSensor(int pin, double minReadableDistanceMm, double maxReadableDistanceMm):
        _pin(pin), _minReadableDistanceMm(minReadableDistanceMm), _maxReadableDistanceMm(maxReadableDistanceMm) {
    pinMode(_pin, INPUT);
    _signalToDistanceSlope = (_maxReadableDistanceMm - _minReadableDistanceMm)/
                             (ArduinoConfig::ANALOG_INPUT_MAX_VALUE - ArduinoConfig::ANALOG_INPUT_MIN_VALUE);

}

double DistanceSensor::readDistanceMm() {
    int sensorValue = analogRead(_pin);
    double distance = _signalToDistanceSlope * sensorValue + _minReadableDistanceMm;
    return distance;
}
