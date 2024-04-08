#ifndef HARDWARECONFIG_H
#define HARDWARECONFIG_H
#include "Arduino.h"

struct ArduinoConfig {
    static const int DISTANCE_SENSOR_PIN = A13;
    static const int CURRENT_SENSOR_PIN = A15;
    static const int MODE_BUTTON_PIN = 22;  // todo add real value
    static const int ANALOG_INPUT_MIN_ADC_VALUE = 0;
    static const int ANALOG_INPUT_MAX_ADC_VALUE = 1023;
    constexpr static const double ANALOG_INPUT_MIN_VOLTAGE = 0.0;
    constexpr static const double ANALOG_INPUT_MAX_VOLTAGE = 5.0;
};

struct DistanceSensorConfig {
    constexpr static const double DISTANCE_MM_VS_VOLTAGE_SLOPE = -4.05;
    constexpr static const double DISTANCE_MM_VS_VOLTAGE_INTERCEPT = 19.84;
};

struct CurrentSensorConfig {
    constexpr static const double CURRENT_VS_VOLTAGE_SLOPE = 0.7120;
    constexpr static const double CURRENT_VS_VOLTAGE_INTERCEPT = -0.0317;
};

struct ActuatorConfig {
    constexpr static const double MIN_VOLTAGE_INPUT_ON_AMPLI = 0;
    constexpr static const double MAX_VOLTAGE_INPUT_ON_AMPLI = 4.08;
    constexpr static const double MIN_CURRENT_INPUT_ON_AMPLI = 0;
    constexpr static const double MAX_CURRENT_INPUT_ON_AMPLI = 3;
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
    constexpr static const double DISTANCE_OF_BLADE_SETPOINT_MM = 15;
    constexpr static const double FORCE_APPLIED_BY_ACTUATOR_N_VS_CURRENT_A_SLOPE = 90.74;
    constexpr static const double FORCE_APPLIED_BY_ACTUATOR_N_VS_CURRENT_A_INTERCEPT = -18.28;

};

#endif // HARDWARECONFIG_H
