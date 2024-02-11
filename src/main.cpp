#include <Arduino.h>
#include "scale.h"
#include "display.h"
#include "DistanceSensor.h"
#include "Actuator.h"
#include "hardware_config.h"

int main(){
    LiquidCrystal lcd = LiquidCrystal(LcdScreenConfig::RS_ARDUINO_PIN, LcdScreenConfig::E_ARDUINO_PIN,
                                      LcdScreenConfig::DB4_ARDUINO_PIN, LcdScreenConfig::DB5_ARDUINO_PIN,
                                      LcdScreenConfig::DB6_ARDUINO_PIN, LcdScreenConfig:: DB7_ARDUINO_PIN);
    Display display = Display(lcd);
    DistanceSensor distanceSensor = DistanceSensor(ArduinoConfig::SENSOR_PIN,
                                   DistanceSensorConfig::DISTANCE_MM_VS_VOLTAGE_SLOPE,
                                   DistanceSensorConfig::DISTANCE_MM_VS_VOLTAGE_INTERCEPT);
    Actuator actuator = Actuator(ArduinoConfig::ACTUATOR_PIN,);
    Scale scale = Scale(display, distanceSensor, ac);

    return 0;
}