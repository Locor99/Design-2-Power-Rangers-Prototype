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
    value = constrain(value, minDacValue, maxDacValue);
    Wire.beginTransmission(address);
    Wire.write(0x40); // Command byte to update the DAC
    Wire.write(value >> 8);     // Send the upper 4 bits of the data
    Wire.write(value & 0xFF);   // Send the lower 8 bits of the data
    Wire.endTransmission();
}
