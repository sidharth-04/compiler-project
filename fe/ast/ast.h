#ifndef ast_h
#define ast_h

#include <string.h>
#include <stdio.h>
#include "astStructure.h"

mod_ty createModuleAST(char name[], stmt_seq_ty body) {
    mod_ty mod = (mod_ty)malloc(sizeof(struct _mod));
   	mod->kind = Stmts_kind;
	mod->name = name;
    mod->v.Stmts.body = body;
    return mod;
}

stmt_seq_ty createStmsAST() {
	stmt_seq_ty stmts = (stmt_seq_ty)malloc(sizeof(struct _stmt_seq));
    stmts->stmt_queue = createQueue();
    return stmts;
}
stmt_seq_ty attachStmtToStmtsAST(stmt_seq_ty stmts, stmt_ty tail) {
	QueueTy queue = stmts->stmt_queue;
    queue->attachNodeToQueue(queue, tail);
    return stmts;
}

expr_seq_ty createExprsAST() {
    expr_seq_ty exprs = (expr_seq_ty)malloc(sizeof(struct _expr_seq));
    exprs->expr_queue = createQueue();
    return exprs;
}
expr_seq_ty attachExprToExprsAST(expr_seq_ty exprs, expr_ty tail) {
	QueueTy queue = exprs->expr_queue;
    queue->attachNodeToQueue(queue, tail);
    return exprs;
}

id_seq_ty createIdsAST() {
    id_seq_ty ids = (id_seq_ty)malloc(sizeof(struct _id_seq));
    ids->id_queue = createQueue();
    return ids;
}
id_seq_ty attachIdToIdsAST(id_seq_ty ids, id_ty tail) {
	QueueTy queue = ids->id_queue;
    queue->attachNodeToQueue(queue, tail);
    return ids;
}

stmt_ty createFunctionDefAST(id_ty name, id_seq_ty args, stmt_seq_ty body, expr_ty ret) {
    stmt_ty functionDef = (stmt_ty)malloc(sizeof (struct _stmt));
	functionDef->kind = FunctionDef_kind;
    functionDef->v.FunctionDef.name = name;
    functionDef->v.FunctionDef.args = args;
    functionDef->v.FunctionDef.body = body;
    functionDef->v.FunctionDef.ret = ret;
    return functionDef;
}

stmt_ty createAssignmentAST(id_ty target, expr_ty value) {
    stmt_ty assignment = (stmt_ty)malloc(sizeof (struct _stmt));
	assignment->kind = Assignment_kind;
    assignment->v.Assignment.target = target;
    assignment->v.Assignment.value = value;
    return assignment;
}

stmt_ty createTypeDefAST(id_ty target, expr_ty value) {
    stmt_ty typeDef = (stmt_ty)malloc(sizeof (struct _stmt));
	typeDef->kind = TypeDef_kind;
    typeDef->v.TypeDef.target = target;
    typeDef->v.TypeDef.value = value;
    return typeDef;
}

expr_ty createExprIdentifierAST(id_ty id) {
    expr_ty identifier = (expr_ty)malloc(sizeof(struct _expr));
	identifier->kind = Identifier_kind;
    identifier->v.Identifier.id = id;
    return identifier;
}

expr_ty createExprNumberAST(num_ty num) {
    expr_ty number = (expr_ty)malloc(sizeof(struct _expr));
	number->kind = Number_kind;
    number->v.Number.num = num;
    return number;
}

expr_ty createBinopAST(expr_ty left, operator_ty op, expr_ty right) {
    expr_ty binop = (expr_ty)malloc(sizeof(struct _expr));
	binop->kind = Binop_kind;
    binop->v.Binop.left = left;
    binop->v.Binop.op = op;
    binop->v.Binop.right = right;
    return binop;
}

expr_ty createUnaryAST(expr_ty target, operator_ty op) {
    expr_ty unaryop = (expr_ty)malloc(sizeof(struct _expr));
	unaryop->kind = Unaryop_kind;
    unaryop->v.Unaryop.target = target;
    unaryop->v.Unaryop.op = op;
    return unaryop;
}

expr_ty createFunctionCallAST(id_ty name, expr_seq_ty args) {
    expr_ty functionCall = (expr_ty)malloc(sizeof(struct _expr));
	functionCall->kind = FunctionCall_kind;
    functionCall->v.FunctionCall.name = name;
    functionCall->v.FunctionCall.args = args;
    return functionCall;
}

expr_ty createIfThenElseAST(expr_ty cond, expr_ty then, expr_ty orElse) {
    expr_ty ifThenElse = (expr_ty)malloc(sizeof(struct _expr));
	ifThenElse->kind = IfThenElse_kind;
    ifThenElse->v.IfThenElse.cond = cond;
    ifThenElse->v.IfThenElse.then = then;
    ifThenElse->v.IfThenElse.orElse = orElse;
    return ifThenElse;
}

id_ty createIdentifierAST(char name[]) {
    id_ty identifier = (id_ty)malloc(sizeof(struct _id));
    identifier->name = strdup(name);
    return identifier;
}

num_ty createNumberAST(double value) {
    num_ty number = (num_ty)malloc(sizeof(struct _num));
    number->v = value;
    return number;
}

#endif
