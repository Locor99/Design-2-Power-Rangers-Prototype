#include "PcArduinoSerialInterface.h"


void setup() {
    PcArduinoSerialInterface pcArduinoSerial;
    pinMode(2, INPUT); // Configure la broche 2 comme entrée
    Serial.println("booting...");

    while (true){
        bool state = digitalRead(2);
        double analogInputState = analogRead(A0);
        //pcArduinoSerial.sendBool(state);
        Serial.println("{\"Mass\":"+String(analogInputState)+"}");
        delay(100);
    }
}