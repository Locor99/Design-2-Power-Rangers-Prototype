#ifndef HARDWARECONFIG_H
#define HARDWARECONFIG_H
#include "Arduino.h"

class ArduinoConfig {
public:
    static const double OPERATING_VOLTAGE;
    static const int SENSOR_PIN; //todo mettre dans sensor
    static const int MODE_BUTTON_PIN;
    static const int ACTUATOR_PIN;//todo mettre dans actuator
    static const int ANALOG_INPUT_MIN_VALUE;
    static const int ANALOG_INPUT_MAX_VALUE;
    static const int PWM_MIN_VALUE;
    static const int PWM_MAX_VALUE;
};

class DistanceSensorConfig {
public:
    static const double MIN_READABLE_DISTANCE_MM;
    static const double MAX_READABLE_DISTANCE_MM;
};

class ActuatorConfig {
public:
    static const double MIN_FORCE_N;
    static const double MAX_FORCE_N;
};

#endif // HARDWARECONFIG_H
