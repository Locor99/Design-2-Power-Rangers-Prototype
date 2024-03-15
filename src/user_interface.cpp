#include "user_interface.h"

const unsigned long REFRESH_INTERVAL_MS = 250;
const unsigned int MASS_DISPLAY_DIGITS_QUANTITY = 6;
const unsigned int MENU_INSTRUCTIONS_DIGITS_QUANTITY = 14;

UserInterface::UserInterface(LiquidCrystal &lcd, unsigned int nbrRows, unsigned int nbrColumns):
        _lcd(lcd),_nbrRows(nbrRows),_nbrColumns(nbrColumns)  {

    _lcd.begin(_nbrColumns, _nbrRows);
    _lcd.clear();
    _massLastRefreshTime = 0;

}
bool UserInterface::isRefreshDue(unsigned long &lastRefreshTime) {
    unsigned long currentTime = millis();
    if (currentTime - lastRefreshTime >= REFRESH_INTERVAL_MS) {
        lastRefreshTime = currentTime;
        return true;
    }
    return false;

}

void UserInterface::displayMass(double massGrams) {
    if (isRefreshDue(_massLastRefreshTime)) {
        _clearRow(0, 0, MASS_DISPLAY_DIGITS_QUANTITY);
        _lcd.home();
        _lcd.print(massGrams, 1);
        _lcd.setCursor(MASS_DISPLAY_DIGITS_QUANTITY - 1, 0);
        _lcd.print("g");
    }
}


void UserInterface::print(String &text) {
    _lcd.print(text);
}

void UserInterface::displayStability(bool isStable) {
    if (isRefreshDue(_stabilityLastRefreshTime)){
        _lcd.setCursor(0, 1);

        if (isStable) {
            _lcd.print("==");
        } else {
            _lcd.print("xx");
        }
    }
}

void UserInterface::displayMenuInstructions(String message){
    _clearRow(_nbrRows-1, _nbrColumns-MENU_INSTRUCTIONS_DIGITS_QUANTITY, _nbrColumns-1);
    _lcd.setCursor(_nbrColumns-message.length(),_nbrRows-1);
    _lcd.print(message);
}

void UserInterface::displayMode(const String& mode){
    _clearRow(0,6,_nbrColumns-1);
    _lcd.setCursor(_nbrColumns-mode.length(),0);
    _lcd.print(mode);
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