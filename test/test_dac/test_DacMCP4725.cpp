#include "unity.h"
#include "ArduinoFake.h"
#include "dac.h"
#include "Wire.h"
#include "WireFake.h"

using namespace fakeit;

namespace {
    const uint8_t dacAddress = 0x60; // The I2C address for the DAC
}

void setUp(void) {
    ArduinoFakeReset();
    When(OverloadedMethod(ArduinoFake(Wire), begin, void(void))).AlwaysReturn();
    When(OverloadedMethod(ArduinoFake(Wire), beginTransmission, void(uint8_t))).AlwaysReturn();
    When(OverloadedMethod(ArduinoFake(Wire), write, size_t(uint8_t))).AlwaysReturn();
    When(OverloadedMethod(ArduinoFake(Wire), endTransmission, uint8_t(void))).AlwaysReturn();
}

void tearDown(void) {
}

void test_sendValue_shouldCallAllNecessaryMethods(void) {
    DacMCP4725 dac;

    dac.setOutputInPercentage(50.0);

    Verify(OverloadedMethod(ArduinoFake(Wire), beginTransmission, void(uint8_t)).Using(dacAddress)).Once();
    Verify(OverloadedMethod(ArduinoFake(Wire), write, size_t(uint8_t)).Using(0x40)).Once();
    Verify(OverloadedMethod(ArduinoFake(Wire), endTransmission, uint8_t())).Once();
}

void test_setOutputInPercentage_WithinRange_shouldSetDacAccoringly(void) {
    const double setpointInPercentage = 50.0;
    const int expectedDacValue = lround(setpointInPercentage/100 * DacMCP4725::maxSetpoint);
    DacMCP4725 dac;

    dac.setOutputInPercentage(setpointInPercentage);

    Verify(OverloadedMethod(ArduinoFake(Wire), write, size_t(uint8_t)).Using(expectedDacValue >> 8));
    Verify(OverloadedMethod(ArduinoFake(Wire), write, size_t(uint8_t)).Using((expectedDacValue & 0xFF) << 4)).Once();
}

void test_sendValue_belowMinimum_shouldSetDacToMinimumValue(void) {
    const double setpointInPercentage = -50.0;
    DacMCP4725 dac;
    const int expectedDacValue = dac.minSetpoint;

    dac.setOutputInPercentage(setpointInPercentage);

    Verify(OverloadedMethod(ArduinoFake(Wire), write, size_t(uint8_t)).Using(expectedDacValue >> 8));
}

void test_sendValue_AboveMaximum_shouldSetDacToMaximumValue(void) {
    const double setpointInPercentage = 150.0;
    DacMCP4725 dac;
    const int expectedDacValue = dac.maxSetpoint;

    dac.setOutputInPercentage(setpointInPercentage);

    Verify(OverloadedMethod(ArduinoFake(Wire), write, size_t(uint8_t)).Using(expectedDacValue >> 8)).Once();
}


int main(int argc, char **argv) {
    UNITY_BEGIN();
    RUN_TEST(test_setOutputInPercentage_WithinRange_shouldSetDacAccoringly);
    RUN_TEST(test_sendValue_shouldCallAllNecessaryMethods);
    RUN_TEST(test_sendValue_belowMinimum_shouldSetDacToMinimumValue);
    RUN_TEST(test_sendValue_AboveMaximum_shouldSetDacToMaximumValue);
    UNITY_END();

    return 0;
}
