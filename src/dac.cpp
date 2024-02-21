#include "dac.h"

DacMCP4725::DacMCP4725(){
    Wire.begin(); // Initialize I2C communication within the constructor
}

void DacMCP4725::setOutputInPercentage(double setpointInPercentage) const {
    int value = lround((setpointInPercentage / 100.0) * maxDacValue);
    sendValue(value);
}

void DacMCP4725::setOutputVoltage(double voltage) const {
    int value = lround((voltage / maxVoltage) * maxDacValue);
    sendValue(value);
}

void DacMCP4725::sendValue(int value) const {
    Serial.print("Valeur reçue par sendValue: ");
    Serial.println(value);//todo clean
    value = constrain(value, minDacValue, maxDacValue);
    byte msb = (byte)((value >> 8) & 0xFF); // Extrait le byte de poids fort
    byte lsb = (byte)(value & 0xFF);

    Wire.beginTransmission(address);
    Wire.write(msb);
    Wire.write(lsb);
    Wire.endTransmission();
    Serial.print("Valeur envoyée au DAC: ");
    Serial.println(value);
}
