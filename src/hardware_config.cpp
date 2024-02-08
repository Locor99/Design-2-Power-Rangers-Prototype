#include "hardware_config.h"
//todo avoir les vraies valeurs
const double ArduinoConfig::OPERATING_VOLTAGE = 5.0;
const int ArduinoConfig::SENSOR_PIN = A0;
const int ArduinoConfig::MODE_BUTTON_PIN = 22;
const int ArduinoConfig::ACTUATOR_PIN = 2;
const int ArduinoConfig::ANALOG_INPUT_MIN_VALUE = 0;
const int ArduinoConfig::ANALOG_INPUT_MAX_VALUE = 1023;
const int ArduinoConfig::PWM_MIN_VALUE = 0;
const int ArduinoConfig::PWM_MAX_VALUE = 255;

const double DistanceSensorConfig::MIN_READABLE_DISTANCE_MM = 0;
const double DistanceSensorConfig::MAX_READABLE_DISTANCE_MM = 100;

const double ActuatorConfig::MIN_FORCE_N = 0;
const double ActuatorConfig::MAX_FORCE_N = 2;

const int LcdScreenConfig::DB4_ARDUINO_PIN = 9;
const int LcdScreenConfig::DB5_ARDUINO_PIN = 10;
const int LcdScreenConfig::DB6_ARDUINO_PIN = 11;
const int LcdScreenConfig::DB7_ARDUINO_PIN = 12;
const int LcdScreenConfig::RS_ARDUINO_PIN = 7;
const int LcdScreenConfig::E_ARDUINO_PIN = 8;
