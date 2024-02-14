void testError(char *msg) {
	printf("Test Error: %s", msg);
}

void assertTrue(int a) {
	if (a != 1) {
		testError("Should be true\n");
	}
}

void assertFalse(int b) {
	if (b == 1) {
		testError("Should be false\n");
	}
}

void assertInt(int actual, int expected) {
	if (actual != expected) {
		printf("Test Error: Expected %i but received %i\n", expected, actual);
	}
}
