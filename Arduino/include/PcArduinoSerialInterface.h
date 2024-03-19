#ifndef PcArduinoSerialInterface_h
#define PcArduinoSerialInterface_h

#include "Arduino.h"

class PcArduinoSerialInterface {
public:
    PcArduinoSerialInterface(); // Constructeur
    void sendBool(bool value);  // Méthode pour envoyer un booléen
};

#endif
