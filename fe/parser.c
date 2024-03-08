#include "parser.h"
#include "../util/loggers/parserLogger.h"

mod_ty parseModule(parserState *ps) {
    stmt_seq_ty body;
    if (!(body = parseStatements(ps))) return 0;
    if (!expectToken(ps, END_OF_FILE)) {
		logError(ps, "Expected end of file");
		return 0;
	}
    return createModuleAST("entry", body);
}

stmt_seq_ty parseStatements(parserState *ps) {
    stmt_seq_ty body = createStmsAST();
    while (expectToken(ps, DEF) || expectToken(ps, LET) || expectToken(ps, TYPE)) {
        stmt_ty stmt;
        if (!(stmt = parseStatement(ps))) return 0;
        attachStmtToStmtsAST(body, stmt);
    }
    return body;
}

stmt_ty parseStatement(parserState *ps) {
    if (expectAndAdvance(ps, DEF)) {
		return parseFunctionDef(ps);
	}
	if (expectAndAdvance(ps, LET)) {
		return parseAssignment(ps);
	}
	if (expectAndAdvance(ps, TYPE)) {
		return parseAssignment(ps);
	}
	return 0;
}

stmt_ty parseFunctionDef(parserState *ps) {
	id_ty returntype;
    id_ty name;
    id_seq_ty args;
    stmt_seq_ty body;
    expr_ty ret;	
    if (!(returntype = parseIdentifier(ps))) return 0;
	SymbolTableTy topST = (SymbolTableTy)ps->stStack->getTop(ps->stStack);
	TypeTy typehint;
	if (!(typehint = topST->getType(topST, returntype->name))) {
		logError(ps, "Expected type hint but got something else");
		return 0;
	}
	if (!expectAndAdvance(ps, COLON)) {
		logError(ps, "Expected colon after type hint");
		return 0;
	}
	if (!(expectToken(ps, ID))) {
		logError(ps, "Expected identifier");
		return 0;
	}
	if (!(name = parseIdentifier(ps))) return 0;
	if (topST->contains(topST, name->name)) {
		logError(ps, ("Cannot redfine function %s", name->name));
		return 0;
	} else {
		topST->put(topST, name->name, typehint, 0);
	}
	SymbolTableTy newST = buildSymbolTable();
	ps->stStack->push(ps->stStack, newST);
	newST->setParent(newST, topST);
    if (!(args = parseParenthesizedIds(ps))) return 0;
    if (!expectAndAdvance(ps, EQUAL)) {
		logError(ps, "Expected equals sign");
		return 0;
	}
    if (!(body = parseStatements(ps))) return 0;
    if (!(ret = parseExpression(ps))) return 0;
    if (!expectAndAdvance(ps, SEMI)) {
		logError(ps, "Expected semicolon");
		return 0;
	}
	ps->stStack->pop(ps->stStack);
    return createFunctionDefAST(name, args, body, ret);
}

stmt_ty parseAssignment(parserState *ps) {
    id_ty first;
	id_ty second;
    expr_ty value;
    if (!(expectToken(ps, ID))) {
		logError(ps, "Expected identifier");
		return 0;
	}
    if (!(first = parseIdentifier(ps))) return 0;
	SymbolTableTy topST = (SymbolTableTy)ps->stStack->getTop(ps->stStack);
	TypeTy typehint;
	if ((typehint = topST->getType(topST, first->name))) {
		if (!expectAndAdvance(ps, COLON)) {
			logError(ps, "Expected colon after type hint");
			return 0;
		}
		if (!(expectToken(ps, ID))) {
			logError(ps, "Expected identifier");
			return 0;
		}
		if (!(second = parseIdentifier(ps))) return 0;
		if (topST->contains(topST, second->name)) {
			logError(ps, ("Identifier %s has already been defined", second->name));
			return 0;
		}
		topST->put(topST, second->name, typehint, 0);
	} else {
		if (topST->contains(topST, first->name)) {
			logError(ps, ("Identifier %s has already been defined", first->name));
			return 0;
		}
		else {
			topST->put(topST, first->name, getPrimitive(GENERIC), 0);
		}
	}
    if (!expectAndAdvance(ps, EQUAL)) {
		logError(ps, "Expected equals sign");
		return 0;
	}
    if (!(value = parseExpression(ps))) return 0;
    if (!expectAndAdvance(ps, SEMI)) {
		logError(ps, "Expected semicolon");
		return 0;
	}
    return createAssignmentAST(first, value);
}

id_seq_ty parseParenthesizedIds(parserState *ps) {
    if (!expectAndAdvance(ps, LPAR)) {
		logError(ps, "Expected '('");
		return 0;
	}
    id_seq_ty body = createIdsAST();
    if (expectAndAdvance(ps, RPAR)) return body;
    id_ty toAdd;
    if (!(expectToken(ps, ID))) {
		logError(ps, "Expected identifier");
		return 0;
	}
    if (!(toAdd = parseIdentifier(ps))) return 0;
	SymbolTableTy topST = (SymbolTableTy)ps->stStack->getTop(ps->stStack);
	if (topST->contains(topST, toAdd->name)) {
		logError(ps, ("Identifier %s has already been defined", toAdd->name));
		return 0;
	}
	topST->put(topST, toAdd->name, getPrimitive(GENERIC), 0);
    attachIdToIdsAST(body, toAdd);
    while (expectAndAdvance(ps, COMMA)) {
		if (!(expectToken(ps, ID))) {
			logError(ps, "Expected identifier");
			return 0;
		}
    	if (!(toAdd = parseIdentifier(ps))) return 0;
		if (topST->contains(topST, toAdd->name)) {
			logError(ps, ("Identifier %s has already been defined", toAdd->name));
			return 0;
		}
		topST->put(topST, toAdd->name, getPrimitive(GENERIC), 0);
        attachIdToIdsAST(body, toAdd);
    }
    if (!expectAndAdvance(ps, RPAR)) {
		logError(ps, "Missing closing ')'");
		return 0;
	}
    return body;
}

expr_seq_ty parseParenthesizedExpressions(parserState *ps) {
    if (!expectAndAdvance(ps, LPAR)) return 0;
    expr_seq_ty body = createExprsAST();
    if (expectAndAdvance(ps, RPAR)) return body;
    expr_ty toAdd;
    if (!(toAdd = parseExpression(ps))) {
		return 0;
	}
    attachExprToExprsAST(body, toAdd);
    while (expectAndAdvance(ps, COMMA)) {
        if (!(toAdd = parseExpression(ps)))	{
			return 0;
		}
        attachExprToExprsAST(body, toAdd);
    }
    if (!expectAndAdvance(ps, RPAR)) {
		logError(ps, "Mising closing ')");
		return 0;
	}
    return body;
}

expr_ty parseExpression(parserState *ps) {
    expr_ty left;
    if (!(left = parseTerm(ps))) return 0;
    if (expectToken(ps, PLUS) || expectToken(ps, MINUS) || expectToken(ps, AND) || expectToken(ps, OR)) {
        operator_ty operator;
        if (expectToken(ps, PLUS)) operator = Add;
        if (expectToken(ps, MINUS)) operator = Sub;
		if (expectToken(ps, AND)) operator = And;
		if (expectToken(ps, OR)) operator = Or;
        advanceParser(ps);
        expr_ty right;
        if (!(right = parseExpression(ps))) return 0;
        return createBinopAST(left, operator, right);
    }
    return left;
}

expr_ty parseTerm(parserState *ps) {
    expr_ty left;
    if (!(left = parseFactor(ps))) return 0;
    if (expectToken(ps, STAR) || expectToken(ps, SLASH) || expectToken(ps, PERCENT)) {
        operator_ty operator;
        if (expectToken(ps, STAR)) operator = Mult;
        if (expectToken(ps, SLASH)) operator = Div;
        if (expectToken(ps, PERCENT)) operator = Mod;
        advanceParser(ps);
        expr_ty right;
        if (!(right = parseTerm(ps))) return 0;
        return createBinopAST(left, operator, right);
    }
    return left;
}

expr_ty parseFactor(parserState *ps) {
    if (expectAndAdvance(ps, LPAR)) {
        expr_ty expression;
        if (!(expression = parseExpression(ps))) return 0;
        if (!expectAndAdvance(ps, RPAR)) return 0;
        return expression;
    }
    if (expectAndAdvance(ps, IF)) {
        expr_ty cond;
        expr_ty then;
        expr_ty orElse;
        if (!(cond = parseExpression(ps))) return 0;
        if (!expectAndAdvance(ps, THEN)) return 0;
        if (!(then = parseExpression(ps))) return 0;
        if (!expectAndAdvance(ps, ELSE)) return 0;
        if (!(orElse = parseExpression(ps))) return 0;
        return createIfThenElseAST(cond, then, orElse);
    }
    id_ty name;
    if (expectToken(ps, ID) && (name = parseIdentifier(ps))) {
		SymbolTableTy topST = (SymbolTableTy)ps->stStack->getTop(ps->stStack);
		if (!topST->search(topST, name->name)) {
			logError(ps, "Identifier has not yet been defined");
			return 0;
		}
        if (expectToken(ps, LPAR)) {
			// We have a function call
            expr_seq_ty args;
            if (!(args = parseParenthesizedExpressions(ps))) return 0;
            return createFunctionCallAST(name, args);
        }
		// We have a normal var
        return createExprIdentifierAST(name);
    }
    num_ty num;
    if (expectToken(ps, NUM) && (num = parseNumber(ps))) {
        return createExprNumberAST(num);
    }
	expr_ty target;
	if (expectAndAdvance(ps, MINUS)) {
		if (!(target = parseFactor(ps))) return 0;
		return createUnaryAST(target, Min);
	}
	if (expectAndAdvance(ps, EXCLM)) {
		if (!(target = parseFactor(ps))) return 0;
		return createUnaryAST(target, Not);
	}
    return 0;
}

id_ty parseIdentifier(parserState *ps) {
    if (expectAndAdvance(ps, ID)) {
        Token *t = fetchCurrToken(ps);
        return createIdentifierAST(t->lexeme);
    }
    return 0;
}

num_ty parseNumber(parserState *ps) {
    if (expectAndAdvance(ps, NUM)) {
        Token *t = fetchCurrToken(ps);
        return createNumberAST(t->numericValue);
    }
    return 0;
}

mod_ty parseProgram(char filename[], SymbolTableTy st) {
    parserState parser;
    buildParser(&parser, filename, st);
    mod_ty entryModule = parseModule(&parser);
    destroyParser(&parser);
    if (entryModule) {
        printf("===============\n");
        printf("SUCCESFUL PARSE\n");
        printf("===============\n");
		return entryModule;
    } else {
        printf("============\n");
        printf("FAILED PARSE\n");
        printf("============\n");
    	return 0;
    }
}
