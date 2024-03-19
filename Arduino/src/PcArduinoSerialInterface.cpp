#include "PcArduinoSerialInterface.h"

PcArduinoSerialInterface::PcArduinoSerialInterface() {
    Serial.begin(9600);
}

void PcArduinoSerialInterface::sendBool(bool value) {
    // Envoie l'état booléen comme un caractère ('1' pour true, '0' pour false)
    Serial.println(value ? "1" : "0");
}
