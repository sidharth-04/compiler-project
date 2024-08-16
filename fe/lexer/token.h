#ifndef token_h
#define token_h

#include <stdlib.h>

enum TokenType {
  	END_OF_FILE,
	ID,
	NUM,
	STRING,
	ERROR,
	DEF,
	LET,
	TYPE,
	IF,
	THEN,
	ELSE,
	OR,
	AND,
	LPAR,
	RPAR,
	LSQB,
	RSQB,
	COLON,
	COMMA,
	SEMI,
	PLUS,
	MINUS,
	STAR,
	SLASH,
	LESS,
	GREATER,
	EQUAL,
	DOT,
	PERCENT,
	LBRACE,
	RBRACE,
	EXCLM,
	EQEQUAL,
	NOTEQUAL,
	LESSEQUAL,
	GREATEREQUAL,
	PLUSEQUAL,
	MINEQUAL,
	STAREQUAL,
	SLASHEQUAL,
	PERCENTEQUAL,
	PLUSPLUS,
	MINMIN
};

typedef struct {
	char *lexeme;
	float numericValue;
	int lineNo;
	enum TokenType type;
	char *errorMsg;
} Token;


void buildToken(Token *token, enum TokenType type, int lineNo);
void buildErrToken(Token *token, int lineNo, char *errorMsg);
void destroyToken(Token *token);

#endif
