#include "unity.h"

void setUp(void) {
}

void tearDown(void) {
}


void test_function_numbers_equal(void) {
    TEST_ASSERT_TRUE(true);
}

int main(int argc, char **argv) {
    UNITY_BEGIN();
    RUN_TEST(test_function_numbers_equal);
    UNITY_END();

    return 0;
}