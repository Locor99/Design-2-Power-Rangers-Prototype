#include "display.h"

Display::Display(LiquidCrystal &lcd): _lcd(lcd) {
    _lcd.begin(LcdScreenConfig::NBR_COLUMNS, LcdScreenConfig::NBR_ROWS);
}

void Display::displayMass(double massGrams) {
    _lcd.home();
    _lcd.print(massGrams, 2);
    _lcd.print(" g");
}

void Display::print(String &text) {
    _lcd.print(text);
}
