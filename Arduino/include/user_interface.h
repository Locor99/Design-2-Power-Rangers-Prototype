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
    none
};

class UserInterface {
public:
    UserInterface(LiquidCrystal &lcd, unsigned int nbrRows, unsigned int nbrColumns);
    void displayMass(double massGrams);
    void displayStability(bool isStable);
    void displayMode(const String& mode);
    Buttons readButtons();
    void displayMenuInstructions(String message);
    void clearMenuInstructionsZone();
    void clearMassZone();

private:
    LiquidCrystal _lcd;
    unsigned long _massLastRefreshTime, _modeLastRefreshTime, _stabilityLastRefreshTime;
    unsigned int _nbrRows, _nbrColumns;
    String _lastDisplayedMode = "";

    bool isRefreshDue(unsigned long &lastRefreshTime, unsigned long interval);
    void print(String &text);

    void _clearRow(int row, unsigned int startIndex, unsigned int endIndex);

    void _sendDataToPC(const String &data);
};

#endif //DESIGN2_PROTOTYPE_DISPLAY_H
