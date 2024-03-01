#include "Actuator.h"

Actuator::Actuator(DacMCP4725 &dac) : _dac(dac) {
}

void Actuator::setVoltage(double voltage) {
    _dac.setOutputVoltage(voltage);
}

void Actuator::setOutputInPercentage(double percentage) {
    _dac.setOutputInPercentage(percentage);
}

double Actuator::getAppliedForceNFromCurrentA(double currentAmps) {
    return currentAmps * 2 * M_PI * 66 * 0.0203 * 0.1128;//todo use constants or class members + make sure equation is right
}
