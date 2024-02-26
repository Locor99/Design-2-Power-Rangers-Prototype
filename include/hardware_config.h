#ifndef HARDWARECONFIG_H
#define HARDWARECONFIG_H
#include "Arduino.h"

struct ArduinoConfig {
    static const int DISTANCE_SENSOR_PIN = A14;  // todo add real value
    static const int CURRENT_SENSOR_PIN = A15;  // todo add real value
    static const int MODE_BUTTON_PIN = 22;  // todo add real value
    static const int ANALOG_INPUT_MIN_ADC_VALUE = 0;
    static const int ANALOG_INPUT_MAX_ADC_VALUE = 1023;
    constexpr static const double ANALOG_INPUT_MIN_VOLTAGE = 0.0;
    constexpr static const double ANALOG_INPUT_MAX_VOLTAGE = 5.0;
};

struct DistanceSensorConfig {
    constexpr static const double DISTANCE_MM_VS_VOLTAGE_SLOPE = 1;  // todo add real value
    constexpr static const double DISTANCE_MM_VS_VOLTAGE_INTERCEPT = 0;  //todo add real value
};

struct CurrentSensorConfig {
    constexpr static const double CURRENT_VS_VOLTAGE_SLOPE = 1;  // todo add real value
    constexpr static const double CURRENT_VS_VOLTAGE_INTERCEPT = 0;  // todo add real value
};

struct ActuatorConfig {
    constexpr static const double MIN_VOLTAGE_INPUT = 0;  // todo add real value
    constexpr static const double MAX_VOLTAGE_INPUT = 2.5;  // todo add real value
};

struct LcdScreenConfig{
    static const int D4_ARDUINO_PIN = 4;
    static const int D5_ARDUINO_PIN = 5;
    static const int D6_ARDUINO_PIN = 6;
    static const int D7_ARDUINO_PIN = 7;
    static const int RS_ARDUINO_PIN = 8;
    static const int E_ARDUINO_PIN = 9;
    static const int NBR_COLUMNS = 16;
    static const int NBR_ROWS = 2;
};

struct ScaleConfig{
    constexpr static const double DISTANCE_SENSOR_TO_BLADE_MM = 50;  // todo add real value
};

#endif // HARDWARECONFIG_H
