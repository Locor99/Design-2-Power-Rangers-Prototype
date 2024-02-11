#include "Actuator.h"

Actuator::Actuator(DacMCP4725 &dac) : _dac(dac) {
}

void Actuator::setVoltage(double voltage) {
    _dac.setOutputVoltage(voltage);
}
