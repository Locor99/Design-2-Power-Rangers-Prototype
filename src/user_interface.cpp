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
        _lcd.print("     ");
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
    _lcd.setCursor(_nbrColumns-mode.length(),0);
    _lcd.print(mode);
}