#include "testutils.h"

int failure = 0;

void failTest() {
	failure = 1;
}
void resetTests() {
	failure = 0;
}
int passedTests() {
	return !failure;
}
