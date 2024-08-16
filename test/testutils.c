#include "testutils.h"

int failure = 0;

void assertTrue(int a) {
	if (a != 1) {
		log_error_header("Should be true");
		failure = 1;
	}
}

void assertFalse(int b) {
	if (b == 1) {
		log_error_header("Should be true");
		failure = 1;
	}
}

void assertInt(int actual, int expected) {
	if (actual != expected) {
		log_error_header("Expected %i but received %i", expected, actual);
		failure = 1;
	}
}

int passedTests() {
	return !failure;
}
