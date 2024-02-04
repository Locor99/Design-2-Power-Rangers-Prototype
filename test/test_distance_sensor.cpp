#include "unity.h"
#include "DistanceSensor.h"
#include "ArduinoFake.h"
#include "HardwareConfig.h"

using namespace fakeit;
const int ANY_PIN = 0;

void setUp(void) {
    Fake(Method(ArduinoFake(),pinMode));
}

void tearDown(void) {
}

void test_readingZeroVolts_shouldReturnMinDistance(void) {
    When(Method(ArduinoFake(), analogRead)).AlwaysReturn(HardwareConfig::ANALOG_INPUT_MIN_VALUE);
    float minDistance = 0;
    float maxDistance = 10;
    DistanceSensor sensor(ANY_PIN, minDistance, maxDistance);

    float sensedDistance = sensor.readDistanceMm();

    TEST_ASSERT_EQUAL(minDistance, sensedDistance);
}

void test_readingMaxVolts_shouldReturnMaxDistance(void) {
    When(Method(ArduinoFake(), analogRead)).AlwaysReturn(HardwareConfig::ANALOG_INPUT_MAX_VALUE);
    float minDistance = 0;
    float maxDistance = 10;
    DistanceSensor sensor(ANY_PIN, minDistance, maxDistance);

    float sensedDistance = sensor.readDistanceMm();

    TEST_ASSERT_EQUAL(maxDistance, sensedDistance);
}

int main(int argc, char **argv) {
    UNITY_BEGIN();
    RUN_TEST(test_readingZeroVolts_shouldReturnMinDistance);
    RUN_TEST(test_readingMaxVolts_shouldReturnMaxDistance);
    UNITY_END();

    return 0;
}
