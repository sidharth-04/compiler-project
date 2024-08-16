#include "token.h"

const char *tokenStrings[] = {
	"END_OF_FILE", "ID", "NUM", "STRING", "ERROR",
	"def", "let", "type",
	"if", "then", "else",
	"or", "and",
	"(", ")", "[", "]", ":", ",", ";", "+", "-", "*", "/", "<", ">", "=", ".", "%", "{", "}", "!",
	"==", "!=", "<=", ">=", "+=", "-=", "*=", "/=", "%=", "++", "--"
};

void buildToken(Token *token, enum TokenType type, int lineNo) {
	token->type = type;
	token->lineNo = lineNo;
}

void buildErrToken(Token *token, int lineNo, char *errorMsg) {
	token->type = ERROR;
	token->lineNo = lineNo;
	token->errorMsg = errorMsg;
}

void destroyToken(Token *token) {
	free(token->lexeme);
	free(token->errorMsg);
	free(token);
}
