#ifndef DESIGN2_PROTOTYPE_DISPLAY_H
#define DESIGN2_PROTOTYPE_DISPLAY_H

#include "LiquidCrystal.h"
#include "hardware_config.h"
#include "Arduino.h"

class Display {
public:
    Display(LiquidCrystal lcd);
private:
    LiquidCrystal _lcd;
};

#endif //DESIGN2_PROTOTYPE_DISPLAY_H
