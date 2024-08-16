#ifndef testutils_h
#define testutils_h

#include <stdio.h>
#include <string.h>
#include "../util/loggers/logger.h"

// log_error_header(__VA_ARGS__); \

#define LOG_TEST_ERROR(...) \
    do { \
        LOG_ERROR("At %s, line %d:\n", __FILE__, __LINE__); \
		LOG_ERROR(__VA_ARGS__); \
		failTest(); \
    } while (0)

#define ASSERT_TRUE(condition) \
    do { \
        if (!(condition)) { \
            LOG_TEST_ERROR("Assertion failed: expected true, but got false.\n"); \
        } \
    } while (0)

#define ASSERT_FALSE(condition) \
    do { \
        if ((condition)) { \
            LOG_TEST_ERROR("Assertion failed: expected false, but got true.\n"); \
        } \
    } while (0)

#define ASSERT_INT(actual, expected) \
    do { \
		int _temp_actual = actual; \
		int _temp_expected = expected; \
        if ((_temp_actual) != (_temp_expected)) { \
            LOG_TEST_ERROR("Assertion failed: expected %d but got %d.\n", (_temp_expected), (_temp_actual)); \
        } \
    } while (0)


        // LOG_ERROR_HEADER("Test failed.\n"); \

#define FAIL_TEST() \
    do { \
		LOG_TEST_ERROR("Test forcefully failed.\n"); \
    } while (0)

void failTest();
void resetTests();
int passedTests();

#endif
