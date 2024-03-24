#include "analog_sensor.h"

const unsigned long  DEFAULT_SENSORS_MIN_SAMPLING_INTERVAL_MS = 10;
const unsigned int DEFAULT_SENSORS_AVERAGING_INTERVAL_MS = 1000;
const unsigned int DEFAULT_SENSORS_SAMPLE_SIZE = DEFAULT_SENSORS_AVERAGING_INTERVAL_MS / DEFAULT_SENSORS_MIN_SAMPLING_INTERVAL_MS;

AnalogSensor::AnalogSensor(int pin, double slope, double intercept)
        : _pin(pin), _slope(slope), _intercept(intercept){
    _sampleSize = DEFAULT_SENSORS_SAMPLE_SIZE;
    _minSampleIntervalMs = DEFAULT_SENSORS_MIN_SAMPLING_INTERVAL_MS;
    _lastSampleTimeMs = 0;
    _samples.reserve(_sampleSize);
}

double AnalogSensor::getPhysicalValue() const {
    int analogInputValue = getAdcValue();
    double sensorVoltage = static_cast<double>(analogInputValue) /
                           ArduinoConfig::ANALOG_INPUT_MAX_ADC_VALUE * ArduinoConfig::ANALOG_INPUT_MAX_VOLTAGE;
    return _slope * sensorVoltage + _intercept;
}

double AnalogSensor::getPhysicalAverageValue() {
    unsigned long currentTime = millis();
    if ((currentTime - _lastSampleTimeMs) >= _minSampleIntervalMs) {
        if (_samples.size() >= _sampleSize) {
            _samples.erase(_samples.begin());
        }
        _samples.push_back(getPhysicalValue());
        _lastSampleTimeMs = currentTime;
    }

    return _getSamplesAverage();
}


int AnalogSensor::getAdcValue() const {
    return analogRead(_pin);
}

double AnalogSensor::_getSamplesAverage() const {
    if (_samples.empty()) return 0.0;

    double sum = 0.0;
    for (double value : _samples) {
        sum += value;
    }
    return sum / _samples.size();
}

void AnalogSensor::setSampleSize(unsigned long timeToAverageMs) {
    _sampleSize = timeToAverageMs / _minSampleIntervalMs;
    _samples.reserve(timeToAverageMs);
}