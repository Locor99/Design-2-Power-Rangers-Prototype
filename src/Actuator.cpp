#include "Actuator.h"

Actuator::Actuator(DacMCP4725 &dac) : _dac(dac) {
}

void Actuator::setVoltage(double voltage) {
    Serial.print("Valeur reçue par setVoltage: ");
    Serial.println(voltage);//todo clean
    _dac.setOutputVoltage(voltage);
}

void Actuator::setOutputInPercentage(double percentage) {
    _dac.setOutputInPercentage(percentage);
}
