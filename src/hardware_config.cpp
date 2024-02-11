#include "hardware_config.h"
//todo avoir les vraies valeurs
const double ArduinoConfig::OPERATING_VOLTAGE = 5.0;
const int ArduinoConfig::DISTANCE_SENSOR_PIN = A0;
static const int CURRENT_SENSOR_PIN = A1;
const int ArduinoConfig::MODE_BUTTON_PIN = 22;
const int ArduinoConfig::ANALOG_INPUT_MIN_VALUE = 0;
const int ArduinoConfig::ANALOG_INPUT_MAX_VALUE = 1023;
const double ArduinoConfig::ANALOG_INPUT_MIN_VOLTAGE = 0.0;
const double ArduinoConfig::ANALOG_INPUT_MAX_VOLTAGE = 5.0;
const int ArduinoConfig::PWM_MIN_VALUE = 0;
const int ArduinoConfig::PWM_MAX_VALUE = 255;

const double DistanceSensorConfig::DISTANCE_MM_VS_VOLTAGE_SLOPE = 3; // todo add real value
const double DistanceSensorConfig::DISTANCE_MM_VS_VOLTAGE_INTERCEPT = 0;//todo add real value

const double ActuatorConfig::MIN_FORCE_N = 0;
const double ActuatorConfig::MAX_FORCE_N = 2;

const int LcdScreenConfig::D4_ARDUINO_PIN = 26;
const int LcdScreenConfig::D5_ARDUINO_PIN = 28;
const int LcdScreenConfig::D6_ARDUINO_PIN = 30;
const int LcdScreenConfig::D7_ARDUINO_PIN = 32;
const int LcdScreenConfig::RS_ARDUINO_PIN = 22;
const int LcdScreenConfig::E_ARDUINO_PIN = 24;
const int LcdScreenConfig::NBR_COLUMNS = 16;
const int LcdScreenConfig:: NBR_ROWS = 2;
