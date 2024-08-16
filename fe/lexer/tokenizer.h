#ifndef tokenizer_h
#define tokenizer_h

#include <stdlib.h>
#include "utility.h"
#include "bufin/bufferedStream.c"
#include "token.h"

typedef struct {
	char currId[1000];
	BufferedStream *stream;
} Tokenizer;


Tokenizer *buildTokenizer(char filename[]);
void destroyTokenizer(Tokenizer *tokenizer);
static void getToken(Tokenizer *tokenizer, Token *tok);

#endif
