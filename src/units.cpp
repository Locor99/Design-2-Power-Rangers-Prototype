#include "units.h"

double gramsToOunces(double massGrams){
    return massGrams / 28.35;
}

String unitToString(Units unit){
    if (unit == Units::GRAMS){
        return "g";
    }
    else if(unit == Units::OUNCES){
        return "oz";
    }
    else{
        return "";
    }
}