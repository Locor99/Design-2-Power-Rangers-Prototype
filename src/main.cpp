#include <Arduino.h>
#include "scale.h"
#include "display.h"
#include "DistanceSensor.h"
#include "Actuator.h"
#include "hardware_config.h"

int main(){
    DistanceSensor distanceSensor = DistanceSensor(ArduinoConfig::SENSOR_PIN,
                                                   )
    Scale scale = Scale();

    return 0;
}