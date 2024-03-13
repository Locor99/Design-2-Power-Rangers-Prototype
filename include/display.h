#ifndef DESIGN2_PROTOTYPE_DISPLAY_H
#define DESIGN2_PROTOTYPE_DISPLAY_H

#include "LiquidCrystal.h"
#include "hardware_config.h"
#include "Arduino.h"

class Display {
public:
    Display(LiquidCrystal &lcd, unsigned int nbrRows, unsigned int nbrColumns);
    void displayMass(double massGrams);
    void markAsStable(bool isStable=true);

private:
    LiquidCrystal _lcd;
    unsigned long lastRefreshTime;
    unsigned int _nbrRows, _nbrColumns;

    bool isRefreshDue();
    void _print(String &text);
};

#endif //DESIGN2_PROTOTYPE_DISPLAY_H
