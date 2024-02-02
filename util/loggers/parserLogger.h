void logError(parserState *ps, char *msg) {
    ps->errorState = 1;
	printf("Error on line %d: %s\n", ps->currTok->lineNo, msg);
}
