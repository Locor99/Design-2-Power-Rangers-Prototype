#ifndef DAC_H
#define DAC_H

#include <Arduino.h>
#include <Wire.h>
#include <math.h>

class DacMCP4725 {
public:
    DacMCP4725();
    virtual void setOutputInPercentage(double setpointInPercentage) const;
    virtual void sendValue(int value) const;

    static const uint8_t address = 0x60;
    static const int minSetpoint = 0;
    static const int maxSetpoint = 4095;
private:

};

#endif // DAC_H
