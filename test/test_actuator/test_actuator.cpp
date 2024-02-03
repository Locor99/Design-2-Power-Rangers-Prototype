#include "unity.h"
#include "ArduinoFake.h"
#include "Actuator.h"
#include "dac.h"

using namespace fakeit;

void setUp(void) {
    ArduinoFakeReset();
}

void tearDown(void) {
}

void test_ActuatorSetForce_shouldSetCorrectPercentage(void) {
    double minForceN = 0.0;
    double maxForceN = 10;
    double forceSetpoint = 5; // Setpoint for the test
    double expectedPercentage = 50.0;
    Mock<DacMCP4725> mockDac;
    When(Method(mockDac, setOutputInPercentage)).AlwaysReturn();

    DacMCP4725& mockDacRef = mockDac.get();
    Actuator actuator(minForceN, maxForceN, mockDacRef);

    actuator.setForceN(forceSetpoint);

    Verify(Method(mockDac, setOutputInPercentage).Using(expectedPercentage)).Once();
}

void test_ActuatorSetForce_ShouldSetActualForceCorrectly(void) {
    double minForceN = 0.0;
    double maxForceN = 10.0;
    double forceSetpoint = 5.0;
    Mock<DacMCP4725> mockDac;
    When(Method(mockDac, setOutputInPercentage)).AlwaysReturn();
    DacMCP4725& mockDacRef = mockDac.get();

    Actuator actuator(minForceN, maxForceN, mockDacRef);
    actuator.setForceN(forceSetpoint);

    TEST_ASSERT_EQUAL_DOUBLE(forceSetpoint, actuator.getActualForceN());
}


int main(int argc, char **argv) {
    UNITY_BEGIN();
    RUN_TEST(test_ActuatorSetForce_shouldSetCorrectPercentage);
    RUN_TEST(test_ActuatorSetForce_ShouldSetActualForceCorrectly);
    UNITY_END();

    return 0;
}
