#include <Arduino.h>
#include "Scale.h"
#include "user_interface.h"
#include "DistanceSensor.h"
#include "Actuator.h"
#include "hardware_config.h"
#include "pid_control.h"
#include "current_sensor.h"
#include "LiquidCrystal.h"

const double POSITION_PID_KP = 0.5;
const double POSITION_PID_KI = 0;
const double POSITION_PID_KD = 0;

const double CURRENT_PID_KP = 0.75;
const double CURRENT_PID_KI = 1;
const double CURRENT_PID_KD= 0;

void regulate(CurrentSensor& currentSensor,
              PidController& currentRegulator,
              DacMCP4725 &dac){
    double current = currentSensor.getCurrent();
    currentRegulator.input = current;
    Serial.println("courant:");
    Serial.println(current);

    double voltageToDac = currentRegulator.computeOutput();
    dac.setOutputVoltage(voltageToDac);
    Serial.println("Tension dac:");
    Serial.println(voltageToDac);
}

void setup() {
    Serial.begin(115200);
    DacMCP4725 dac;
    PidController currentRegulator(CURRENT_PID_KP, CURRENT_PID_KI, CURRENT_PID_KD, DIRECT);
    currentRegulator.setOutputLimits(ActuatorConfig::MIN_VOLTAGE_INPUT_ON_AMPLI, ActuatorConfig::MAX_VOLTAGE_INPUT_ON_AMPLI);
    CurrentSensor currentSensor(ArduinoConfig::CURRENT_SENSOR_PIN,
                                CurrentSensorConfig::CURRENT_VS_VOLTAGE_SLOPE,
                                CurrentSensorConfig::CURRENT_VS_VOLTAGE_INTERCEPT);

    const unsigned long periodTime = 3000;
    unsigned long lastTime;

    currentRegulator.setpoint = 1;

    while(true){

        currentRegulator.setpoint = 1;
        lastTime = millis();
        while(millis() < lastTime + periodTime){
            regulate(currentSensor, currentRegulator, dac);
        }

        currentRegulator.setpoint = 2;
        lastTime = millis();
        while(millis() < lastTime + periodTime){
            regulate(currentSensor, currentRegulator, dac);
        }
    }
}

