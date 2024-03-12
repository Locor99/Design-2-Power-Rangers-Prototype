#include "display.h"

const unsigned long REFRESH_INTERVAL_MS = 250;

Display::Display(LiquidCrystal &lcd): _lcd(lcd) {
    _lcd.begin(LcdScreenConfig::NBR_COLUMNS, LcdScreenConfig::NBR_ROWS);
    _lcd.clear();
    lastRefreshTime = 0;

}
bool Display::isRefreshDue(){
    unsigned long currentTime = millis();
    if (currentTime - lastRefreshTime >= REFRESH_INTERVAL_MS) {
        lastRefreshTime = currentTime;
        return true;
    }
    return false;

}

void Display::displayMass(double massGrams) {
    if (isRefreshDue()){
        _lcd.home();
        _lcd.print("     ");
        _lcd.home();
        _lcd.print(massGrams, 1);
        _lcd.setCursor(5,0);
        _lcd.print("g");
    }
}

void Display::print(String &text) {
    if (isRefreshDue()){
        _lcd.print(text);
    }
}
