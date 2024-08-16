void runQueueTests();
void runStackTests();
void runSymbolTableTests();

#include "../util/loggers/logger.h"
#include "testutils.h"

#define INTERPRET_TESTS() \
	if (passedTests()) { \
		LOG_SUCCESS_HEADER("all tests passed\n"); \
	} \
	resetTests();

int main() {
	printf("-------------\n");
	LOG_INFO_HEADER("running queue tests...\n");
	runQueueTests();
	INTERPRET_TESTS();
	printf("-------------\n\n");

	printf("-------------\n");
	LOG_INFO_HEADER("running stack tests...\n");
	runStackTests();
	INTERPRET_TESTS();
	printf("-------------\n\n");

	printf("-------------\n");
	LOG_INFO_HEADER("running symbol table tests...\n");
	runSymbolTableTests();	
	INTERPRET_TESTS();
	printf("-------------\n\n");
}
