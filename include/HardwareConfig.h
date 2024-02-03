// HardwareConfig.h
#ifndef HARDWARECONFIG_H
#define HARDWARECONFIG_H

class HardwareConfig {
public:
    static const int ACTUATOR_PIN;
    static const int MODE_BUTTON_PIN;
    static const int SENSOR_PIN;
    static const float OPERATING_VOLTAGE;
    static const int ANALOG_INPUT_MIN_VALUE;
    static const int ANALOG_INPUT_MAX_VALUE;

private:
    HardwareConfig() {}
};

#endif // HARDWARECONFIG_H
