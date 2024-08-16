#ifndef parser_h
#define parser_h

#include "../util/structures/symbolTable.h"
#include "../util/structures/stack.h"
#include "../util/typesystem/typeSystem.h"
#include "../util/typesystem/primitives.h"
#include "lexer/tokenizer.c"
#include "ast/ast.h"

typedef struct {
    Tokenizer *tokenizer;
	Token *currTok;
	StackTy stStack;
} parserState;

#include "../util/loggers/parserLogger.h"


// Function definitions
void buildParser(parserState *ps, char filename[], SymbolTableTy st);
void destroyParser(parserState *ps);
mod_ty parseProgram(char filename[], SymbolTableTy st);
mod_ty parseModule(parserState *ps);
stmt_seq_ty parseStatements(parserState *ps);
stmt_ty parseStatement(parserState *ps);
stmt_ty parseFunctionDef(parserState *ps);
stmt_ty parseAssignment(parserState *ps);
id_seq_ty parseParenthesizedIds(parserState *ps);
expr_seq_ty parseParenthesizedExpressions(parserState *ps);
expr_ty parseExpression(parserState *ps);
expr_ty parseTerm(parserState *ps);
expr_ty parseFactor(parserState *ps);
id_ty parseIdentifier(parserState *ps);
num_ty parseNumber(parserState *ps);

void advanceParser(parserState *ps);
int expectToken(parserState *ps, enum TokenType tt);
int expectAndAdvance(parserState *ps, enum TokenType tt);
Token *fetchCurrToken(parserState *ps);

#endif
