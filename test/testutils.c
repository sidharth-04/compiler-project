#include "testutils.h"

#define TEST_ERROR(...) log_error(__VA_ARGS__)

void assertTrue(int a) {
	if (a != 1) {
		TEST_ERROR("Should be true");
	}
}

void assertFalse(int b) {
	if (b == 1) {
		TEST_ERROR("Should be true");
	}
}

void assertInt(int actual, int expected) {
	if (actual != expected) {
		TEST_ERROR("Expected %i but received %i", expected, actual);
	}
}
