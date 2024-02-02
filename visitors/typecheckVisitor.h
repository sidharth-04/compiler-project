#include "../util/typeSystem.h"

static VisitorTy typecheckVisitor;
// Place these in their own encapsulated structure
SymbolTableTy st;
int errorOccurred = 0;

static void* visitModule(mod_ty);
static void* visitStmts(stmt_seq_ty);
static void* visitExprs(expr_seq_ty);
static void* visitIds(id_seq_ty);
static void* visitStmt(stmt_ty);
static void* visitFunctionDef(stmt_ty);
static void* visitAssignment(stmt_ty);
static void* visitExpr(expr_ty);
static void* visitIdentifier(id_ty);
static void* visitNumber(num_ty);
static void* visitBinop(expr_ty);
static void* visitUnaryop(expr_ty);
static void* visitFunctionCall(expr_ty);
static void* visitIfThenElse(expr_ty);

static void print(char toPrint[]) {
	printf("%s\n", toPrint);
}
static void printInt(int toPrint) {
	printf("%d\n", toPrint);
}

static void *visitModule(mod_ty mod) {
    stmt_seq_ty body = mod->v.Stmts.body;
    typecheckVisitor->visitStmts(body);
	return 0;
}

static void *visitStmts(stmt_seq_ty stmts) {
    ast_queue_ty queue = stmts->stmt_queue;
    int n = queue->size;
   	if (n == 0) {
		return 0;
    }
    queue_node_ty currNode = (queue_node_ty)(queue->head);
    while (--n >= 0) {
        stmt_ty stmt = (stmt_ty)(currNode->value);
		typecheckVisitor->visitStmt(stmt);
        currNode = currNode->next;
		if (errorOccurred) return 0;
    }
	return 0;
}
static void *visitExprs(expr_seq_ty exprs) {
    ast_queue_ty queue = exprs->expr_queue;
    int n = queue->size;
    if (n == 0) {
		return 0;
    }
    queue_node_ty currNode = (queue_node_ty)queue->head;
    while (--n >= 0) {
        expr_ty expr = (expr_ty)(currNode->value);
		typecheckVisitor->visitExpr(expr);
        currNode = currNode->next;
    }
	return 0;
	// Need someway to check the types
}
static void *visitIds(id_seq_ty ids) {
    ast_queue_ty queue = ids->id_queue;
    int n = queue->size;
    if (n == 0) {
		return 0;
    }
    queue_node_ty currNode = (queue_node_ty)queue->head;
    while (--n >= 0) {
        id_ty id = (id_ty)(currNode->value);
        typecheckVisitor->visitIdentifier(id);
        currNode = currNode->next;
    }
	return 0;
}

static void *visitStmt(stmt_ty stmt) {
	switch (stmt->kind) {
		case FunctionDef_kind:
			typecheckVisitor->visitFunctionDef(stmt);
			break;
		case Assignment_kind:
			typecheckVisitor->visitAssignment(stmt);
			break;
	}
	return 0;
}
static void *visitFunctionDef(stmt_ty stmt) {
    // typecheckVisitor->visitIdentifier(stmt->v.FunctionDef.name);
	char *name = stmt->v.FunctionDef.name;
	typecheckVisitor->visitIds(stmt->v.FunctionDef.args);
	typecheckVisitor->visitStmts(stmt->v.FunctionDef.body);
	typecheckVisitor->visitExpr(stmt->v.FunctionDef.ret);
	return 0;
}
static void *visitAssignment(stmt_ty stmt) {
    TypeTy target = (TypeTy)typecheckVisitor->visitIdentifier(stmt->v.Assignment.target);
	TypeTy value = (TypeTy)typecheckVisitor->visitExpr(stmt->v.Assignment.value);
	if (!typeMatch(target, value)) {
		print("Type mismatch");
		errorOccurred = 1;
	}
}

static void *visitExpr(expr_ty expr) {
	switch (expr->kind) {
		case Identifier_kind:
			return typecheckVisitor->visitIdentifier(expr->v.Identifier.id);
		case Number_kind:
			return typecheckVisitor->visitNumber(expr->v.Number.num);
		case Binop_kind:
			return typecheckVisitor->visitBinop(expr);
		case Unaryop_kind:
			return typecheckVisitor->visitUnaryop(expr);
		case FunctionCall_kind:
			return typecheckVisitor->visitFunctionCall(expr);	
		case IfThenElse_kind:
			return typecheckVisitor->visitIfThenElse(expr);
	}
	return 0;
}
static void *visitIdentifier(id_ty id) {
    print(id->name);
	return 0;
}
static void *visitNumber(num_ty num) {
	printInt(num->v);
	return 0;
}
static void *visitBinop(expr_ty expr) {
 	TypeTy left = (TypeTy)typecheckVisitor->visitExpr(expr->v.Binop.left);
	TypeTy right = typecheckVisitor->(TypeTy)visitExpr(expr->v.Binop.right);
	// if (!left || !right) return 0;
	if (!checkTypeCat(left, INT) || !checkTypeCat(rigth, INT)) {
		errorOcurred = 1;
		return 0;
	}
	return buildPrimitive(INT);
}
static void *visitUnaryop(expr_ty expr) {
	TypeTy type = typecheckVisitor->visitExpr(expr->v.Unaryop.target);
    switch (expr->v.Unaryop.op) {
        case Not:
			if (!checkTypeCat(type, BOOL)) return 0;
			return buildPrimitive(BOOL);
			break;
		default:
			if (!checkTypeCat(type, INT)) return 0;
			return buildPrimitive(INT);
			break;
    }
	return 0;
}
static void *visitFunctionCall(expr_ty expr) {
	// We need to do a full function type match
    typecheckVisitor->visitIdentifier(expr->v.FunctionCall.name);
	st = st->next;
	typecheckVisitor->visitExprs(expr->v.FunctionCall.args);
	return 0;
}
static void *visitIfThenElse(expr_ty expr) {
	TypeTy cond = typecheckVisitor->visitExpr(expr->v.IfThenElse.cond);
	// if (!cond) return 0;
	if (!checkTypeCat(cond, BOOL) retunr 0;
	TypeTy first = typecheckVisitor->visitExpr(expr->v.IfThenElse.then);
	TypeTy second = typecheckVisitor->visitExpr(expr->v.IfThenElse.orElse);
	// We woud log an error here for type mismatch
	if (!checkTypeMatch(first, second)) return 0;
	return 1;
}


void buildTypecheckVisitor(mod_ty mod) {
    typecheckVisitor = (VisitorTy)malloc(sizeof(Visitor));
    typecheckVisitor->entry = mod;
    // methods
    typecheckVisitor->visitModule = visitModule;
    typecheckVisitor->visitStmts = visitStmts;
    typecheckVisitor->visitExprs = visitExprs;
    typecheckVisitor->visitIds = visitIds;
	typecheckVisitor->visitStmt = visitStmt;
    typecheckVisitor->visitFunctionDef = visitFunctionDef;
    typecheckVisitor->visitAssignment = visitAssignment;
	typecheckVisitor->visitExpr = visitExpr;
	typecheckVisitor->visitIdentifier = visitIdentifier;
    typecheckVisitor->visitNumber = visitNumber;
	typecheckVisitor->visitBinop = visitBinop;
    typecheckVisitor->visitUnaryop = visitUnaryop;
    typecheckVisitor->visitFunctionCall = visitFunctionCall;
    typecheckVisitor->visitIfThenElse = visitIfThenElse;
}

int typecheckASTTree(mod_ty mod, SymbolTableTy stRef) {
    buildTypecheckVisitor(mod);
	st = stRef;
	traverseVisitor(typecheckVisitor);
}
