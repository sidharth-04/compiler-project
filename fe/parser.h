#ifndef parser_h
#define parser_h

#include "../util/structures/symbolTable.h"
#include "../util/structures/stack.h"
#include "lexer/tokenizer.c"
#include "ast/ast.h"

typedef struct {
    Tokenizer *tokenizer;
	Token *currTok;
	StackTy stStack;
} parserState;

#include "../util/loggers/parserLogger.h"


// Function definitions
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

void advanceParser(parserState *ps) {
    getToken(ps->tokenizer, ps->currTok);
}
int expectToken(parserState *ps, enum TokenType tt) {
    return ps->currTok->type == tt;
}
int expectAndAdvance(parserState *ps, enum TokenType tt) {
    if (expectToken(ps, tt)) {
        advanceParser(ps);
        return 1;
    }
    return 0;
}
Token *fetchCurrToken(parserState *ps) {
    return ps->currTok;
}

void buildParser(parserState *ps, char filename[], SymbolTableTy st) {
    ps->tokenizer = buildTokenizer(filename);
    ps->currTok = (Token *)malloc(sizeof(Token));
    advanceParser(ps);
	ps->stStack = createStack();
	ps->stStack->push(ps->stStack, st);
}
void destroyParser(parserState *ps) {
    destroyTokenizer(ps->tokenizer);
    destroyToken(ps->currTok);
	pop(ps->stStack);
	destroyStack(ps->stStack);
	free(ps);
}

#endif
