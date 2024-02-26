#include <Arduino.h>
#include "Scale.h"
#include "display.h"
#include "DistanceSensor.h"
#include "Actuator.h"
#include "hardware_config.h"
#include "pid_control.h"
#include "current_sensor.h"
#include "LiquidCrystal.h"
#include "pid_control.h"

const double KP = 0.2;
const double KI = 0.4;
const double KD = 0.003;

void setup() {
    Serial.begin(115200);
    LiquidCrystal lcd(LcdScreenConfig::RS_ARDUINO_PIN, LcdScreenConfig::E_ARDUINO_PIN,
                      LcdScreenConfig::D4_ARDUINO_PIN, LcdScreenConfig::D5_ARDUINO_PIN,
                      LcdScreenConfig::D6_ARDUINO_PIN, LcdScreenConfig::D7_ARDUINO_PIN);
    Display display(lcd);
    DistanceSensor distanceSensor(ArduinoConfig::DISTANCE_SENSOR_PIN,
                                  DistanceSensorConfig::DISTANCE_MM_VS_VOLTAGE_SLOPE,
                                  DistanceSensorConfig::DISTANCE_MM_VS_VOLTAGE_INTERCEPT);
    CurrentSensor currentSensor(ArduinoConfig::CURRENT_SENSOR_PIN,
                                CurrentSensorConfig::CURRENT_VS_VOLTAGE_SLOPE,
                                CurrentSensorConfig::CURRENT_VS_VOLTAGE_INTERCEPT);
    DacMCP4725 dac;
    Actuator actuator(dac);

    PidController pidController(KP, KI, KD, REVERSE);
    pidController.setOutputLimits(ActuatorConfig::MIN_VOLTAGE_INPUT, 2.5);
    pidController.setpoint = 1.92;//todo add real value
    distanceSensor.setFilterConstant(0.2);
    //todo remove print in PID lib
    Scale scale(display, distanceSensor, currentSensor, actuator, pidController);


    scale.executeMainLoop();
}
