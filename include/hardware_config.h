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
private:
    ArduinoConfig();
};

class DistanceSensorConfig {
public:
    static const double MIN_READABLE_DISTANCE_MM;
    static const double MAX_READABLE_DISTANCE_MM;
private:
    DistanceSensorConfig();
};

class ActuatorConfig {
public:
    static const double MIN_FORCE_N;
    static const double MAX_FORCE_N;
private:
    ActuatorConfig();
};

class LcdScreenConfig{
public:
    static const int DB4_ARDUINO_PIN;
    static const int DB5_ARDUINO_PIN;
    static const int DB6_ARDUINO_PIN;
    static const int DB7_ARDUINO_PIN;
    static const int RS_ARDUINO_PIN;
    static const int E_ARDUINO_PIN;
    static const int NBR_COLUMNS;
    static const int NBR_ROWS;
private:
    LcdScreenConfig();
};


#endif // HARDWARECONFIG_H
