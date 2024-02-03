#include "Actuator.h"


Actuator::Actuator(int pin, double minForceN, double maxForceN) :
    _pin(pin), _minForceN(minForceN), _maxForceN(maxForceN) {
    pinMode(_pin, OUTPUT);
    _forceToPwmOutSlope = (ArduinoConfig::PWM_MAX_VALUE - ArduinoConfig::PWM_MIN_VALUE) / (_maxForceN - _minForceN);
    _forceToPwmIntercept = ArduinoConfig::PWM_MIN_VALUE - _forceToPwmOutSlope * _minForceN;
}

double Actuator::getActualForceN() {
    return _actualForceN;
}

void Actuator::setForceNewton(double force) {
    int pwmDutyCycle = round(force * _forceToPwmOutSlope + _forceToPwmIntercept);
    analogWrite(_pin, pwmDutyCycle);
    _actualForceN = force;
}