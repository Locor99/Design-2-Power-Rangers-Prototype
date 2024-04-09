#include <Arduino.h>
#include "Scale.h"
#include "user_interface.h"
#include "DistanceSensor.h"
#include "Actuator.h"
#include "hardware_config.h"
#include "pid_control.h"
#include "current_sensor.h"
#include "LiquidCrystal.h"

const double POSITION_PID_KP = 0.03;
const double POSITION_PID_KI = 0.05;
const double POSITION_PID_KD = 0;

const double CURRENT_PID_KP = 0.2;
const double CURRENT_PID_KI = 2.5;
const double CURRENT_PID_KD= 0.008;

void setup() {
    Serial.begin(115200);
    LiquidCrystal lcd(LcdScreenConfig::RS_ARDUINO_PIN, LcdScreenConfig::E_ARDUINO_PIN,
                      LcdScreenConfig::D4_ARDUINO_PIN, LcdScreenConfig::D5_ARDUINO_PIN,
                      LcdScreenConfig::D6_ARDUINO_PIN, LcdScreenConfig::D7_ARDUINO_PIN);
    UserInterface display(lcd, LcdScreenConfig::NBR_ROWS, LcdScreenConfig::NBR_COLUMNS);
    DistanceSensor distanceSensor(ArduinoConfig::DISTANCE_SENSOR_PIN,
                                  DistanceSensorConfig::DISTANCE_MM_VS_VOLTAGE_SLOPE,
                                  DistanceSensorConfig::DISTANCE_MM_VS_VOLTAGE_INTERCEPT);
    CurrentSensor currentSensor(ArduinoConfig::CURRENT_SENSOR_PIN,
                                CurrentSensorConfig::CURRENT_VS_VOLTAGE_SLOPE,
                                CurrentSensorConfig::CURRENT_VS_VOLTAGE_INTERCEPT);
    DacMCP4725 dac;
    Actuator actuator(dac);

    PidController positionRegulator(POSITION_PID_KP, POSITION_PID_KI, POSITION_PID_KD, DIRECT);
    positionRegulator.setOutputLimits(ActuatorConfig::MIN_CURRENT_INPUT_ON_AMPLI, ActuatorConfig::MAX_CURRENT_INPUT_ON_AMPLI);
    positionRegulator.setpoint = ScaleConfig::DISTANCE_OF_BLADE_SETPOINT_MM;

    PidController currentRegulator(CURRENT_PID_KP, CURRENT_PID_KI, CURRENT_PID_KD, DIRECT);
    currentRegulator.setOutputLimits(ActuatorConfig::MIN_VOLTAGE_INPUT_ON_AMPLI, ActuatorConfig::MAX_VOLTAGE_INPUT_ON_AMPLI);

    Scale scale(display,
                distanceSensor,
                currentSensor,
                actuator,
                positionRegulator,
                currentRegulator,
                ScaleConfig::FORCE_APPLIED_BY_ACTUATOR_N_VS_CURRENT_A_SLOPE,
                ScaleConfig::FORCE_APPLIED_BY_ACTUATOR_N_VS_CURRENT_A_INTERCEPT);

    const unsigned long periodTime = 7000;
    unsigned long lastTime;

    while(true){

        scale._positionRegulator.setpoint = 10;
        lastTime = millis();
        while(millis() < lastTime + periodTime){
            scale._regulateScale();
        }

        scale._positionRegulator.setpoint = 25;
        lastTime = millis();
        while(millis() < lastTime + periodTime){
            scale._regulateScale();
        }
    }
}
