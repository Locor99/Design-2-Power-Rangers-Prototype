#ifndef DESIGN2_PROTOTYPE_DISPLAY_H
#define DESIGN2_PROTOTYPE_DISPLAY_H

#include "LiquidCrystal.h"
#include "hardware_config.h"
#include "Arduino.h"

class Display {
public:
    explicit Display(LiquidCrystal &lcd);
    void displayMass(double massGrams);
    void markAsStable(bool isStable=true);

private:
    LiquidCrystal _lcd;
    unsigned long lastRefreshTime;

    bool isRefreshDue();
    void _print(String &text);
};

#endif //DESIGN2_PROTOTYPE_DISPLAY_H
