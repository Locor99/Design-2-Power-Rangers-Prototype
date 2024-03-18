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

const double CURRENT_PID_KP = 0.1;
const double CURRENT_PID_KI = 0;
const double CURRENT_PID_KD= 0;

void setup() {
    Serial.begin(115200);
    PidController currentRegulator(CURRENT_PID_KP, CURRENT_PID_KI, CURRENT_PID_KD, DIRECT);
    currentRegulator.setOutputLimits(ActuatorConfig::MIN_VOLTAGE_INPUT_ON_AMPLI, ActuatorConfig::MAX_VOLTAGE_INPUT_ON_AMPLI);

   while(true){

   }
}
