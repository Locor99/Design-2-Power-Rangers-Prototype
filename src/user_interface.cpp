#include "user_interface.h"

const unsigned long REFRESH_INTERVAL_MS = 250;

UserInterface::UserInterface(LiquidCrystal &lcd, unsigned int nbrRows, unsigned int nbrColumns):
        _lcd(lcd),_nbrRows(nbrRows),_nbrColumns(nbrColumns)  {

    _lcd.begin(_nbrColumns, _nbrRows);
    _lcd.clear();
    lastRefreshTime = 0;

}
bool UserInterface::isRefreshDue(){
    unsigned long currentTime = millis();
    if (currentTime - lastRefreshTime >= REFRESH_INTERVAL_MS) {
        lastRefreshTime = currentTime;
        return true;
    }
    return false;

}

void UserInterface::displayMass(double massGrams) {
    if (isRefreshDue()){
        _lcd.home();
        _lcd.print("     ");//todo use clearRow method
        _lcd.home();
        _lcd.print(massGrams, 1);
        _lcd.setCursor(5,0);
        _lcd.print("g");
    }
}

void UserInterface::_print(String &text) {
    if (isRefreshDue()){
        _lcd.print(text);
    }
}

void UserInterface::markAsStable(bool isStable) {
    _lcd.setCursor(0,1);

    if (isStable){
        _lcd.print("======");
    }
    else{
        _lcd.print("xxxxxx");
    }
}

void UserInterface::displayMode(const String& mode){
    _clearRow(0,6,_nbrColumns-1);
    _lcd.setCursor(_nbrColumns-mode.length(),0);
    _lcd.print(mode);
}

void UserInterface::_clearRow(int row, unsigned int startIndex, unsigned int endIndex) {
    _lcd.setCursor(startIndex, row);
    for (unsigned int i = startIndex; i < _nbrColumns; i++) {
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
    return Buttons::reset;
}