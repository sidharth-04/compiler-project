void runQueueTests();
void runStackTests();
void runSymbolTableTests();

#include "../util/loggers/logger.h"
#include "testutils.h"

int main() {
	runQueueTests();
	runStackTests();
	runSymbolTableTests();
	if (passedTests()) {
		log_success_header("all tests passed");
	} else {
		log_info_header("some tests failed");
	}
}
