#include <Arduino.h>
#include "scale.h"
#include "display.h"
#include "DistanceSensor.h"
#include "Actuator.h"
#include "hardware_config.h"

int main(){
    LiquidCrystal lcd = LiquidCrystal(LcdScreenConfig::RS_ARDUINO_PIN, LcdScreenConfig::E_ARDUINO_PIN,
                                      LcdScreenConfig::D4_ARDUINO_PIN, LcdScreenConfig::D5_ARDUINO_PIN,
                                      LcdScreenConfig::D6_ARDUINO_PIN, LcdScreenConfig:: D7_ARDUINO_PIN);
    Display display = Display(lcd);
    display.displayMass(100);

    return 0;
}