#ifndef DESIGN2_PROTOTYPE_DISPLAY_H
#define DESIGN2_PROTOTYPE_DISPLAY_H

#include "LiquidCrystal.h"
#include "hardware_config.h"
#include "Arduino.h"
enum class Buttons {
    select,
    up,
    down,
    left,
    right,
    reset,
    none
};

class UserInterface {
public:
    UserInterface(LiquidCrystal &lcd, unsigned int nbrRows, unsigned int nbrColumns);
    void displayMass(double massGrams);
    void markAsStable(bool isStable=true);
    void displayMode(const String& mode);
    Buttons readButtons();

private:
    LiquidCrystal _lcd;
    unsigned long lastRefreshTime;
    unsigned int _nbrRows, _nbrColumns;

    bool isRefreshDue();
    void _print(String &text);

    void _clearRow(int row, unsigned int startIndex, unsigned int endIndex);
};

#endif //DESIGN2_PROTOTYPE_DISPLAY_H
