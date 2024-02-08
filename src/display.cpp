#include "display.h"
const int NUMBER_OF_COLUMN = 16;
const int NUMBER_OF_ROWS = 2;

Display::Display(LiquidCrystal &lcd): _lcd(lcd) {
    _lcd.begin(NUMBER_OF_COLUMN, NUMBER_OF_ROWS);
}

void Display::displayMass(double mass) {
    _lcd.setCursor(0,0);
    _lcd.print(mass,2);
    _lcd.print(" g");
}