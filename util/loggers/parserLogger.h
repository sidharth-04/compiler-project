void logError(parserState *ps, char *msg) {
	printf("Error on line %d: %s\n", ps->currTok->lineNo, msg);
}
