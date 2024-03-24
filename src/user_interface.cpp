#include "user_interface.h"
#include "units.h"

const unsigned long COMMON_REFRESH_INTERVAL_MS = 400;
const unsigned long MODE_REFRESH_INTERVAL_MS = 5;
const unsigned int MASS_DISPLAY_DIGITS_QUANTITY = 7;
const unsigned int MENU_INSTRUCTIONS_DIGITS_QUANTITY = 14;
const unsigned int MODE_DIGITS_QUANTITY = 9;

UserInterface::UserInterface(LiquidCrystal &lcd, unsigned int nbrRows, unsigned int nbrColumns):
        _lcd(lcd),_nbrRows(nbrRows),_nbrColumns(nbrColumns)  {

    _lcd.begin(_nbrColumns, _nbrRows);
    _lcd.clear();
    _massLastRefreshTime = 0;

}
bool UserInterface::isRefreshDue(unsigned long &lastRefreshTime, unsigned long interval) {
    unsigned long currentTime = millis();
    if (currentTime - lastRefreshTime >= interval) {
        lastRefreshTime = currentTime;
        return true;
    }
    return false;

}

void UserInterface::displayMass(double massGrams, Units unit) {
    if (isRefreshDue(_massLastRefreshTime, COMMON_REFRESH_INTERVAL_MS)) {
        _clearRow(0, 0, MASS_DISPLAY_DIGITS_QUANTITY+1);
        _lcd.home();

        double massToDisplay = massGrams;
        if(unit == Units::OUNCES){
            massToDisplay = gramsToOunces(massGrams);
            }

        _lcd.print(massToDisplay, 1);
        _lcd.setCursor(MASS_DISPLAY_DIGITS_QUANTITY - 1, 0);
        _lcd.print(unitToString(unit));
    }
}


void UserInterface::print(String &text) {
    _lcd.print(text);
}

void UserInterface::displayStability(bool isStable) {
    if (isRefreshDue(_stabilityLastRefreshTime, COMMON_REFRESH_INTERVAL_MS)){
        _lcd.setCursor(0, 1);

        if (isStable) {
            _lcd.print(":)");
        } else {
            _lcd.print(":S");
        }
    }
}

void UserInterface::displayMenuInstructions(String message){
    if (_messageInMenuInstruction != message) {
        clearMenuInstructionsZone();
        _lcd.setCursor(_nbrColumns - message.length(), _nbrRows - 1);
        _lcd.print(message);
        _messageInMenuInstruction = message;
    }
}

void UserInterface:: clearMenuInstructionsZone(){
    _clearRow(_nbrRows-1, _nbrColumns-MENU_INSTRUCTIONS_DIGITS_QUANTITY, _nbrColumns);
}

void UserInterface:: clearMassZone(){
    _clearRow(0, 0, MASS_DISPLAY_DIGITS_QUANTITY);
}

void UserInterface::displayMode(const String& mode){
    if (_lastDisplayedMode != mode){
        const int row = 0;
        _clearRow(row, _nbrColumns-MODE_DIGITS_QUANTITY, _nbrColumns - 1);
        _lcd.setCursor(_nbrColumns - mode.length(), row);
        _lcd.print(mode);
        _lastDisplayedMode = mode;
    }
}

void UserInterface::_clearRow(int row, unsigned int startIndex, unsigned int endIndex) {
    _lcd.setCursor(startIndex, row);
    for (unsigned int i = startIndex; i < endIndex; i++) {
        _lcd.print(" ");
    }
}

Buttons UserInterface::readButtons() {
    int adc_key_in = analogRead(0); //todo make const
    if (adc_key_in > 1000) return Buttons::none;
    if (adc_key_in < 50) return Buttons::right;
    if (adc_key_in < 250) return Buttons::up;
    if (adc_key_in < 450) return Buttons::down;
    if (adc_key_in < 650) return Buttons::left;
    if (adc_key_in < 850) return Buttons::select;
    return Buttons::none;
}

void UserInterface::displayAveragingTime(unsigned long averagingTime) {
    displayMenuInstructions(
            "Moy: "+ String(averagingTime) +" ms");
}