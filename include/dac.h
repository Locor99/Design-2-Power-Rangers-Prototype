#ifndef DAC_H
#define DAC_H

#include <Arduino.h>
#include <Wire.h>
#include <math.h>

class DacMCP4725 {
public:
    DacMCP4725();
    virtual void setOutputInPercentage(double setpointInPercentage) const;
    void setOutputVoltage(double voltage) const;
    virtual void sendValue(int value) const;

    static const int address = 0x60;
    static const int minDacValue = 0;
    static const int maxDacValue = 4095;
    constexpr static double minVoltage = 0.0;
    constexpr static double maxVoltage = 5.0;
private:

};

#endif // DAC_H
