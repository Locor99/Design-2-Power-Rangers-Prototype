#include "display.h"

Display::Display(LiquidCrystal &lcd): _lcd(lcd) {
    _lcd.begin(LcdScreenConfig::NBR_COLUMNS, LcdScreenConfig::NBR_ROWS);
}

void Display::displayMass(double mass) {
    _lcd.setCursor(0,0);
    _lcd.print(mass,2);
    _lcd.print(" g");
}