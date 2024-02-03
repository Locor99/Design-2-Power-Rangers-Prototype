#include "unity.h"
#include "Actuator.h"
#include "ArduinoFake.h"
#include "hardware_config.h"

using namespace fakeit;
const int PIN_MOCK = 0;
const double  MIN_FORCE = 1;
const double MAX_FORCE = 15;

void setUp(void) {
    Fake(Method(ArduinoFake(),pinMode));
    Fake(Method(ArduinoFake(),analogWrite));
}

void tearDown(void) {
}

void test_setMinForce_shouldUsePwm_withMinDutyCycle(void) {
    Actuator actuator(PIN_MOCK, MIN_FORCE, MAX_FORCE);

    actuator.setForceNewton(MIN_FORCE);

    Verify(Method(ArduinoFake(), analogWrite).Using(PIN_MOCK, ArduinoConfig::PWM_MIN_VALUE)).Once();
}

void test_setMaxForce_shouldUsePwm_withMaxDutyCycle(void) {
    Actuator actuator(PIN_MOCK,  MIN_FORCE, MAX_FORCE);

    actuator.setForceNewton(MAX_FORCE);

    Verify(Method(ArduinoFake(), analogWrite).Using(PIN_MOCK, ArduinoConfig::PWM_MAX_VALUE)).Once();
}

void test_settingAForce_shouldUpdateForceMember(void) {
    Actuator actuator(PIN_MOCK,  MIN_FORCE, MAX_FORCE);

    double aForce = 1.5;
    actuator.setForceNewton(aForce);

    TEST_ASSERT_EQUAL_DOUBLE(aForce, actuator.getActualForceN());
}


int main(int argc, char **argv) {
    UNITY_BEGIN();
    RUN_TEST(test_setMinForce_shouldUsePwm_withMinDutyCycle);
    RUN_TEST(test_setMaxForce_shouldUsePwm_withMaxDutyCycle);
    RUN_TEST(test_settingAForce_shouldUpdateForceMember);
    UNITY_END();

    return 0;
}
