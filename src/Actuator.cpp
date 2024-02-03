#include "Actuator.h"

Actuator::Actuator(double minForceN, double maxForceN, DacMCP4725& dac) :
    _minForceN(minForceN), _maxForceN(maxForceN), _dac(dac) {
    _forceNToDacOutSlope = 100.0 / (_maxForceN - _minForceN);
    _forceNToDacIntercept = -_forceNToDacOutSlope * _minForceN;
}

double Actuator::getActualForceN() {
    return _actualForceN;
}

void Actuator::setForceN(double forceSetpoint) {
    double percentageToSetDac = (forceSetpoint * _forceNToDacOutSlope + _forceNToDacIntercept);
    _dac.setOutputInPercentage(percentageToSetDac);
    _actualForceN = forceSetpoint;
}
