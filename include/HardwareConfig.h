// HardwareConfig.h
#ifndef HARDWARECONFIG_H
#define HARDWARECONFIG_H

class HardwareConfig {
public:
//todo add real configs
    static const int ACTUATOR_PIN;
    static const int MODE_BUTTON_PIN;
    static const int SENSOR_PIN;
    static const double OPERATING_VOLTAGE;
    static const int ANALOG_INPUT_MIN_VALUE;
    static const int ANALOG_INPUT_MAX_VALUE;
    static const int PWM_MIN_VALUE;
    static const int PWM_MAX_VALUE;

private:
    HardwareConfig() {}
};

#endif // HARDWARECONFIG_H
