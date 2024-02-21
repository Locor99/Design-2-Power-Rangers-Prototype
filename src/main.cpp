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

LiquidCrystal lcd = LiquidCrystal(LcdScreenConfig::RS_ARDUINO_PIN, LcdScreenConfig::E_ARDUINO_PIN,
                                  LcdScreenConfig::D4_ARDUINO_PIN, LcdScreenConfig::D5_ARDUINO_PIN,
                                  LcdScreenConfig::D6_ARDUINO_PIN, LcdScreenConfig:: D7_ARDUINO_PIN);
Display display = Display(lcd);
DistanceSensor distanceSensor = DistanceSensor(ArduinoConfig::DISTANCE_SENSOR_PIN,
                                               DistanceSensorConfig::DISTANCE_MM_VS_VOLTAGE_SLOPE,
                                               DistanceSensorConfig::DISTANCE_MM_VS_VOLTAGE_INTERCEPT);
CurrentSensor currentSensor = CurrentSensor(ArduinoConfig::CURRENT_SENSOR_PIN,
                                            CurrentSensorConfig::CURRENT_VS_VOLTAGE_SLOPE,
                                            CurrentSensorConfig:: CURRENT_VS_VOLTAGE_INTERCEPT);
DacMCP4725 dac = DacMCP4725();
Actuator actuator = Actuator(dac);
PidParameters pidParameters = PidParameters(KP, KI, KD,
                                            ActuatorConfig::MIN_VOLTAGE_INPUT, ActuatorConfig::MAX_VOLTAGE_INPUT); //todo mettre kp, ki, kd ailleurs?
PidController pidController = PidController(pidParameters);
Scale scale = Scale(display, distanceSensor, currentSensor, actuator, pidController);

void setup(){
    Serial.begin(115200);
    distanceSensor.setFilterConstant(DistanceSensorConfig::FILTER_CONSTANT);
}
void loop(){
    scale.executeMainLoop();

}