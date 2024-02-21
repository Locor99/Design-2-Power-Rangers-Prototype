#include <Arduino.h>
#include "scale.h"
#include "display.h"
#include "DistanceSensor.h"
#include "Actuator.h"
#include "hardware_config.h"
#include "pid_control.h"
#include "current_sensor.h"
#include <PID_v1.h>

const double KP = 100;
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

double setpoint = 1.88;
double input=0, output;
double Kp=0.5, Ki=0, Kd=0;
PID pidController(&input, &output, &setpoint, Kp, Ki, Kd, REVERSE);

void setup(){
    Serial.begin(115200);
    distanceSensor.setFilterConstant(DistanceSensorConfig::FILTER_CONSTANT);
    pidController.SetMode(AUTOMATIC);
    pidController.SetOutputLimits(0, 2.5);

}
void loop(){
    double distanceSensorVoltage = distanceSensor.getPhysicalFilteredValue();
    Serial.print("distance sensor voltage:");
    Serial.println(distanceSensorVoltage);//todo clean
    input = distanceSensorVoltage;

    pidController.Compute();
    Serial.print("output voltage given to actuator:");
    Serial.println(output);
    actuator.setVoltage(output);
    delay(100);

}