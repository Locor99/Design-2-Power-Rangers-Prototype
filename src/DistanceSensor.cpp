#include "DistanceSensor.h"
#include "HardwareConfig.h"

DistanceSensor::DistanceSensor(int pin, float minReadableDistanceMm, float maxReadableDistanceMm):
        _pin(pin), _minReadableDistanceMm(minReadableDistanceMm), _maxReadableDistanceMm(maxReadableDistanceMm) {
    pinMode(_pin, INPUT);
    _signalToDistanceSlope = (_maxReadableDistanceMm - _minReadableDistanceMm)/
                             (HardwareConfig::ANALOG_INPUT_MAX_VALUE - HardwareConfig::ANALOG_INPUT_MIN_VALUE);

}

float DistanceSensor::readDistanceMm() {
    int sensorValue = analogRead(_pin);
    double distance = _signalToDistanceSlope * sensorValue + _minReadableDistanceMm;
    return distance;
}
