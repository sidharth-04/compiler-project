#ifndef testutils_h
#define testutils_h

#include <stdio.h>
#include <string.h>
#include "../util/loggers/logger.h"

void testError(char *msg);
void assertTrue(int a);
void assertFalse(int b);
void assertInt(int actual, int expected);

#endif
