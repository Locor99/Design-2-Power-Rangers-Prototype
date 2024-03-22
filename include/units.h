#include "Arduino.h"
#ifndef DESIGN2_PROTOTYPE_UNITS_H
#define DESIGN2_PROTOTYPE_UNITS_H

enum class Units {
    GRAMS,
    OUNCES
};

double gramsToOunces(double massGrams);
String unitToString(Units unit);

#endif //DESIGN2_PROTOTYPE_UNITS_H
