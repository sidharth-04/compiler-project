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

const char *tokenStrings[] = {
	"END_OF_FILE", "ID", "NUM", "STRING", "ERROR",
	"def", "let", "type",
	"if", "then", "else",
	"or", "and",
	"(", ")", "[", "]", ":", ",", ";", "+", "-", "*", "/", "<", ">", "=", ".", "%", "{", "}", "!",
	"==", "!=", "<=", ">=", "+=", "-=", "*=", "/=", "%=", "++", "--"
};

typedef struct {
	char *lexeme;
	float numericValue;
	int lineNo;
	enum TokenType type;
	char *errorMsg;
} Token;

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
}
