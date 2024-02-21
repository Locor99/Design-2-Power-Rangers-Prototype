#ifndef HARDWARECONFIG_H
#define HARDWARECONFIG_H
#include "Arduino.h"

//todo ajouter vraies valeurs
class ArduinoConfig {
public:
    static const double OPERATING_VOLTAGE;
    static const int DISTANCE_SENSOR_PIN;
    static const int CURRENT_SENSOR_PIN;
    static const int MODE_BUTTON_PIN;
    static const int ANALOG_INPUT_MIN_ADC_VALUE;
    static const int ANALOG_INPUT_MAX_ADC_VALUE;
    static const double ANALOG_INPUT_MIN_VOLTAGE;
    static const double ANALOG_INPUT_MAX_VOLTAGE;
    static const int PWM_MIN_VALUE;
    static const int PWM_MAX_VALUE;

private:
    ArduinoConfig();

};

class DistanceSensorConfig {
public:
    static const double DISTANCE_MM_VS_VOLTAGE_SLOPE;
    static const double DISTANCE_MM_VS_VOLTAGE_INTERCEPT;
    static const double FILTER_CONSTANT;
private:
    DistanceSensorConfig();
};

class CurrentSensorConfig {
public:
    static const double CURRENT_VS_VOLTAGE_SLOPE;
    static const double CURRENT_VS_VOLTAGE_INTERCEPT;
private:
    CurrentSensorConfig();
};

class ActuatorConfig {
public:
    static const double MIN_VOLTAGE_INPUT;
    static const double MAX_VOLTAGE_INPUT;
private:
    ActuatorConfig();
};

class LcdScreenConfig{
public:
    static const int D4_ARDUINO_PIN;
    static const int D5_ARDUINO_PIN;
    static const int D6_ARDUINO_PIN;
    static const int D7_ARDUINO_PIN;
    static const int RS_ARDUINO_PIN;
    static const int E_ARDUINO_PIN;
    static const int NBR_COLUMNS;
    static const int NBR_ROWS;
private:
    LcdScreenConfig();
};

class ScaleConfig{
public:
    static const double DISTANCE_SENSOR_TO_BLADE_MM;
private:
    ScaleConfig();
};




#endif // HARDWARECONFIG_H
