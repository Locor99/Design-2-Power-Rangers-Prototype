#include "analog_sensor.h"

AnalogSensor::AnalogSensor(int pin, double slope, double intercept, unsigned int sampleSize, unsigned long minSampleInterval)
        : _pin(pin), _slope(slope), _intercept(intercept), _sampleSize(sampleSize), _minSampleIntervalMs(minSampleInterval) {
    _lastSampleTimeMs = 0;
    _samples.reserve(sampleSize);
}

double AnalogSensor::getPhysicalValue() const {
    int analogInputValue = getAdcValue();
    double sensorVoltage = static_cast<double>(analogInputValue) /
                           ArduinoConfig::ANALOG_INPUT_MAX_ADC_VALUE * ArduinoConfig::ANALOG_INPUT_MAX_VOLTAGE;
    return _slope * sensorVoltage + _intercept;
}

double AnalogSensor::getPhysicalFilteredValue() {
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