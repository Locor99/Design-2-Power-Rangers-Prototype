#include <Arduino.h>
#include "scale.h"
#include "display.h"
#include "DistanceSensor.h"
#include "Actuator.h"
#include "hardware_config.h"
#include "pid_control.h"
#include "current_sensor.h"

const double KP = 1;
const double KI = 0;
const double KD = 0;

DacMCP4725 dac = DacMCP4725();
Actuator actuator = Actuator(dac);

void setup(){
    Serial.begin(115200);

}
void loop(){
    Serial.println("test_dac");
    actuator.setVoltage(0);
    delay(3000);
    actuator.setVoltage(3);
    delay(3000);

}