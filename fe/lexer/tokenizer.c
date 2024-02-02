#include <stdlib.h>
#include "utility.h"
#include "bufin/bufferedStream.c"

typedef struct {
	char currId[1000];
	BufferedStream *stream;
} Tokenizer;

void buildTokenizer(Tokenizer *tokenizer, char filename[]) {
	tokenizer->stream = (BufferedStream *)malloc(sizeof(BufferedStream));
	buildBufferedStream(tokenizer->stream, filename);
}
void destroyTokenizer(Tokenizer *tokenizer) {
	destroyBufferedStream(tokenizer->stream);
	free(tokenizer->stream);
}

static void getToken(Tokenizer *tokenizer, Token *tok) {
	BufferedStream *stream = tokenizer->stream;
	char c = streamRead(stream);

	while (isWhitespace(c)) {
		c = streamRead(stream);
	}

	// Probably do this better
	while (c == '/' && streamPeek(stream) == '/') {
		c = streamRead(stream);
		while ((c = streamRead(stream)) != '\n') {
			if (isEOF(c)) {
				buildToken(tok, END_OF_FILE, streamLineCount(stream));
				return;
			}
		}
		c = streamRead(stream);
		while (isWhitespace(c)) {
			c = streamRead(stream);
		}
	}

	if (isEOF(c)) {
		buildToken(tok, END_OF_FILE, streamLineCount(stream));
		return;
	}

	// Check all trivial terminals
	if (c == '(') {
		buildToken(tok, LPAR, streamLineCount(stream));
		return;
	}
	if (c == ')') {
		buildToken(tok, RPAR, streamLineCount(stream));
		return;
	}
	if (c == '[') {
		buildToken(tok, LSQB, streamLineCount(stream));
		return;
	}
	if (c == ']') {
		buildToken(tok, RSQB, streamLineCount(stream));
		return;
	}
	if (c == '{') {
		buildToken(tok, LBRACE, streamLineCount(stream));
		return;
	}
	if (c == '}') {
		buildToken(tok, RBRACE, streamLineCount(stream));
		return;
	}
	if (c == '!') {
		buildToken(tok, EXCLM, streamLineCount(stream));
		return;
	}
	if (c == ':') {
		buildToken(tok, COLON, streamLineCount(stream));
		return;
	}
	if (c == '.') {
		buildToken(tok, DOT, streamLineCount(stream));
		return;
	}
	if (c == ',') {
		buildToken(tok, COMMA, streamLineCount(stream));
		return;
	}
	if (c == ';') {
		buildToken(tok, SEMI, streamLineCount(stream));
		return;
	}
	if (c == '+') {
		if (streamPeek(stream) == '=') {
			buildToken(tok, PLUSEQUAL, streamLineCount(stream));
			streamRead(stream);
			return;
		}
		if (streamPeek(stream) == '+') {
			buildToken(tok, PLUSPLUS, streamLineCount(stream));
			streamRead(stream);
			return;
		}
		buildToken(tok, PLUS, streamLineCount(stream));
		return;
	}
	if (c == '-') {
		if (streamPeek(stream) == '=') {
			buildToken(tok, MINEQUAL, streamLineCount(stream));
			streamRead(stream);
			return;
		}
		if (streamPeek(stream) == '-') {
			buildToken(tok, MINMIN, streamLineCount(stream));
			streamRead(stream);
			return;
		}
		buildToken(tok, MINUS, streamLineCount(stream));
		return;
	}
	if (c == '*') {
		if (streamPeek(stream) == '=') {
			buildToken(tok, STAREQUAL, streamLineCount(stream));
			streamRead(stream);
			return;
		}
		buildToken(tok, STAR, streamLineCount(stream));
		return;
	}
	if (c == '/') {
		if (streamPeek(stream) == '=') {
			buildToken(tok, SLASHEQUAL, streamLineCount(stream));
			streamRead(stream);
			return;
		}
		buildToken(tok, SLASH, streamLineCount(stream));
		return;
	}
	if (c == '%') {
		if (streamPeek(stream) == '=') {
			buildToken(tok, PERCENTEQUAL, streamLineCount(stream));
			streamRead(stream);
			return;
		}
		buildToken(tok, PERCENT, streamLineCount(stream));
		return;
	}
	if (c == '<') {
		if (streamPeek(stream) == '=') {
			buildToken(tok, LESSEQUAL, streamLineCount(stream));
			streamRead(stream);
			return;
		}
		buildToken(tok, LESS, streamLineCount(stream));
		return;
	}
	if (c == '>') {
		if (streamPeek(stream) == '=') {
			buildToken(tok, GREATEREQUAL, streamLineCount(stream));
			streamRead(stream);
			return;
		}
		buildToken(tok, GREATER, streamLineCount(stream));
		return;
	}
	if (c == '=') {
		if (streamPeek(stream) == '=') {
			buildToken(tok, EQEQUAL, streamLineCount(stream));
			streamRead(stream);
			return;
		}
		buildToken(tok, EQUAL, streamLineCount(stream));
		return;
	}


	if (isalpha(c)) {
		int i = 0;
		tokenizer->currId[i++] = c;
		c = streamRead(stream);
		while (isalnum(c)) {
			tokenizer->currId[i++] = c;
			c = streamRead(stream);
		}
		streamUnread(stream);
		// Add more identifiers
		if (strncmp(tokenizer->currId, "def", 3) == 0 && i == 3) {
			buildToken(tok, DEF, streamLineCount(stream));
		} else if (strncmp(tokenizer->currId, "let", 3) == 0 && i == 3) {
			buildToken(tok, LET, streamLineCount(stream));
		} else if (strncmp(tokenizer->currId, "if", 2) == 0 && i == 2) {
			buildToken(tok, IF, streamLineCount(stream));
		} else if (strncmp(tokenizer->currId, "then", 4) == 0 && i == 4) {
			buildToken(tok, THEN, streamLineCount(stream));
		} else if (strncmp(tokenizer->currId, "else", 4) == 0 && i == 4) {
			buildToken(tok, ELSE, streamLineCount(stream));
		} else if (strncmp(tokenizer->currId, "and", 3) == 0 && i == 3) {
			buildToken(tok, AND, streamLineCount(stream));
		} else if (strncmp(tokenizer->currId, "or", 2) == 0 && i == 2) {
			buildToken(tok, OR, streamLineCount(stream));
		} else {
			buildToken(tok, ID, streamLineCount(stream));
			setLexeme(tok, tokenizer->currId, i);
		}
		memset(tokenizer->currId, 0, i);
		return;
	}

	if (c == '.' || isNonzeroDigit(c) || (c == '0' && streamPeek(stream) == '.') || (c == '0' && !isdigit(streamPeek(stream)))) {
		int dotUsed = (c == '.' ? 1 : 0);
		int i = 0;
		tokenizer->currId[i++] = c;
		c = streamRead(stream);
		while (isdigit(c) || (c == '.' && !dotUsed)) {
			if (c == '.') dotUsed = 1;
			tokenizer->currId[i++] = c;
			c = streamRead(stream);
		}
		streamUnread(stream);
		// TODO: MAKE THESE ERRORS BETTER
		if (streamPeek(stream) == '.' && dotUsed) {
			// ERROR: dot used after float
			buildErrToken(tok, streamLineCount(stream), "Cannot have dot after float");
		} else if (isalpha(streamPeek(stream))) {
			// ERROR: invalid number literal
			buildErrToken(tok, streamLineCount(stream), "Cannot start identifier with integers");
		} else {
			buildToken(tok, NUM, streamLineCount(stream));
			setLexeme(tok, tokenizer->currId, i);
			tok->numericValue = atof(tok->lexeme);
		}
		memset(tokenizer->currId, 0, i);
		return;
	}

	// Have reached an invalid token
	buildErrToken(tok, streamLineCount(stream), "Invalid character");
}

int testTokenizer() {
	Tokenizer tokenizer;
	buildTokenizer(&tokenizer, "hello.cd");
	while (1) {
		Token tok;
		getToken(&tokenizer, &tok);
		if (tok.type == END_OF_FILE) return 0;
		printToken(&tok);
		if (tok.type == ERROR) return 0;
	}
	return 0;
}
