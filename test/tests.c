#include "stdio.h"
#include "testUtils.c"
#include "queueTests.c"
#include "stackTests.c"
#include "symbolTableTests.c"

int main() {
	runQueueTests();
	runStackTests();
	runSymbolTableTests();
}
