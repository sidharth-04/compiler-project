#include "stdio.h"
#include "queueTests.c"
#include "stackTests.c"
#include "symbolTableTests.c"

int main() {
	runQueueTests();
	runStackTests();
	runSymbolTableTests();
}
