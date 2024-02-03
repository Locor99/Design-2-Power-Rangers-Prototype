#include "unity.h"
#include "DistanceSensor.h"
#include "ArduinoFake.h"
#include "hardware_config.h"

using namespace fakeit;
const int ANY_PIN = 0;

void setUp(void) {
    Fake(Method(ArduinoFake(),pinMode));
}

void tearDown(void) {
}

void test_readingZeroVolts_shouldReturnMinDistance(void) {
    When(Method(ArduinoFake(), analogRead)).AlwaysReturn(ArduinoConfig::ANALOG_INPUT_MIN_VALUE);
    double minDistance = 0;
    double maxDistance = 10;
    DistanceSensor sensor(ANY_PIN, minDistance, maxDistance);

    double sensedDistance = sensor.readDistanceMm();

    TEST_ASSERT_EQUAL_DOUBLE(minDistance, sensedDistance);
}

void test_readingMaxVolts_shouldReturnMaxDistance(void) {
    When(Method(ArduinoFake(), analogRead)).AlwaysReturn(ArduinoConfig::ANALOG_INPUT_MAX_VALUE);
    double minDistance = 0;
    double maxDistance = 10;
    DistanceSensor sensor(ANY_PIN, minDistance, maxDistance);

    double sensedDistance = sensor.readDistanceMm();

    TEST_ASSERT_EQUAL_DOUBLE(maxDistance, sensedDistance);
}

int main(int argc, char **argv) {
    UNITY_BEGIN();
    RUN_TEST(test_readingZeroVolts_shouldReturnMinDistance);
    RUN_TEST(test_readingMaxVolts_shouldReturnMaxDistance);
    UNITY_END();

    return 0;
}
