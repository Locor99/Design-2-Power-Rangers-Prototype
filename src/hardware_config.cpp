#include "hardware_config.h"

const double ArduinoConfig::OPERATING_VOLTAGE = 5.0;
const int ArduinoConfig::DISTANCE_SENSOR_PIN = A0; // todo add real value
const int ArduinoConfig::CURRENT_SENSOR_PIN = A1; // todo add real value
const int ArduinoConfig::MODE_BUTTON_PIN = 22; // todo add real value
const int ArduinoConfig::ANALOG_INPUT_MIN_ADC_VALUE = 0;
const int ArduinoConfig::ANALOG_INPUT_MAX_ADC_VALUE = 1023;
const double ArduinoConfig::ANALOG_INPUT_MIN_VOLTAGE = 0.0;
const double ArduinoConfig::ANALOG_INPUT_MAX_VOLTAGE = 5.0;
const int ArduinoConfig::PWM_MIN_VALUE = 0;
const int ArduinoConfig::PWM_MAX_VALUE = 255;

const double DistanceSensorConfig::DISTANCE_MM_VS_VOLTAGE_SLOPE = 1; // todo add real value
const double DistanceSensorConfig::DISTANCE_MM_VS_VOLTAGE_INTERCEPT = 0;//todo add real value
const double DistanceSensorConfig::FILTER_CONSTANT = 0.5;


const double CurrentSensorConfig:: CURRENT_VS_VOLTAGE_SLOPE = 1;// todo add real value
const double CurrentSensorConfig:: CURRENT_VS_VOLTAGE_INTERCEPT = 0;// todo add real value

const double ActuatorConfig::MIN_VOLTAGE_INPUT = 0; // todo add real value
const double ActuatorConfig::MAX_VOLTAGE_INPUT = 5; // todo add real value

const int LcdScreenConfig::D4_ARDUINO_PIN = 26;
const int LcdScreenConfig::D5_ARDUINO_PIN = 28;
const int LcdScreenConfig::D6_ARDUINO_PIN = 30;
const int LcdScreenConfig::D7_ARDUINO_PIN = 32;
const int LcdScreenConfig::RS_ARDUINO_PIN = 22;
const int LcdScreenConfig::E_ARDUINO_PIN = 24;
const int LcdScreenConfig::NBR_COLUMNS = 16;
const int LcdScreenConfig:: NBR_ROWS = 2;

const double ScaleConfig::DISTANCE_SENSOR_TO_BLADE_MM = 50; // todo add real value