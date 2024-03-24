#ifndef DESIGN2_PROTOTYPE_DISPLAY_H
#define DESIGN2_PROTOTYPE_DISPLAY_H

#include "LiquidCrystal.h"
#include "hardware_config.h"
#include "Arduino.h"
#include "units.h"

enum class Buttons {
    select,
    up,
    down,
    left,
    right,
    none
};

class UserInterface {
public:
    UserInterface(LiquidCrystal &lcd, unsigned int nbrRows, unsigned int nbrColumns);
    void displayMass(double massGrams, Units unit);
    void displayStability(bool isStable);
    void displayMode(const String& mode);
    Buttons readButtons();
    void displayMenuInstructions(String message);
    void clearMenuInstructionsZone();
    void clearMassZone();
    void displayAveragingTime(unsigned long averagingTime);

private:
    LiquidCrystal _lcd;
    unsigned long _massLastRefreshTime, _modeLastRefreshTime, _stabilityLastRefreshTime, _menuInstructionLastRefreshTime;
    unsigned int _nbrRows, _nbrColumns;
    String _lastDisplayedMode = "";

    bool isRefreshDue(unsigned long &lastRefreshTime, unsigned long interval);
    void print(String &text);

    void _clearRow(int row, unsigned int startIndex, unsigned int endIndex);

};

#endif //DESIGN2_PROTOTYPE_DISPLAY_H
