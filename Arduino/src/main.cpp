#include "PcArduinoSerialInterface.h"


void setup() {
    PcArduinoSerialInterface pcArduinoSerial;
    pinMode(2, INPUT); // Configure la broche 2 comme entrée
    Serial.println("booting...");

    while (true){
        bool state = digitalRead(2);
        pcArduinoSerial.sendBool(state);
        delay(10);
    }
}