// Utility to print out the AST
static VisitorTy printVisitor;

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

// Printing helper vars and functions
int depth = 0;
void printSpaces() {
    int n = depth;
    while (--n >= 0) {
        printf("  ");
    }
}

static void *visitModule(mod_ty mod) {
    printSpaces();
    printf("BEGIN MODULE: %s\n", mod->name);
    depth ++;
    stmt_seq_ty body = mod->v.Stmts.body;
    printVisitor->visitStmts(body);
    depth --;
    printSpaces();
    printf("END MODULE\n");
	return 0;
}

static void *visitStmts(stmt_seq_ty stmts) {
    printSpaces();
    printf("BEGIN STMTS:\n");
    depth ++;
    ast_queue_ty queue = stmts->stmt_queue;
    int n = queue->size;
    if (n == 0) {
        printSpaces();
        printf("-\n");
    }
    queue_node_ty currNode = (queue_node_ty)(queue->head);
    while (--n >= 0) {
        stmt_ty stmt = (stmt_ty)(currNode->curr);
		printVisitor->visitStmt(stmt);
        currNode = currNode->next;
    }
    depth --;
    printSpaces();
    printf("END\n");
	return 0;
}
static void *visitExprs(expr_seq_ty exprs) {
    printf("BEGIN EXPRS: ");
    ast_queue_ty queue = exprs->expr_queue;
    int n = queue->size;
    if (n == 0) {
        printf("- ");
    }
    queue_node_ty currNode = (queue_node_ty)queue->head;
    while (--n >= 0) {
        expr_ty expr = (expr_ty)(currNode->curr);
		printVisitor->visitExpr(expr);
        currNode = currNode->next;
        if (n > 0) printf(",");
        printf(" ");
    }
    printf("END");
	return 0;
}
static void *visitIds(id_seq_ty ids) {
    printf("BEGIN IDS: ");
    ast_queue_ty queue = ids->id_queue;
    int n = queue->size;
    if (n == 0) {
        printf("- ");
    }
    queue_node_ty currNode = (queue_node_ty)queue->head;
    while (--n >= 0) {
        id_ty id = (id_ty)(currNode->curr);
        printVisitor->visitIdentifier(id);
        currNode = currNode->next;
        if (n > 0) printf(",");
        printf(" ");
    }
    printf("END");
	return 0;
}

static void *visitStmt(stmt_ty stmt) {
	switch (stmt->kind) {
		case FunctionDef_kind:
			printVisitor->visitFunctionDef(stmt);
			break;
		case Assignment_kind:
			printVisitor->visitAssignment(stmt);
			break;
	}
	return 0;
}
static void *visitFunctionDef(stmt_ty stmt) {
    printSpaces();
    printf("BEGIN FUNCTION DEF: ");
    printVisitor->visitIdentifier(stmt->v.FunctionDef.name);
    printf("\n");
    depth ++;
    printSpaces();
    printf("ARGS: ");
	printVisitor->visitIds(stmt->v.FunctionDef.args);
    printf("\n");
	printVisitor->visitStmts(stmt->v.FunctionDef.body);
    printSpaces();
    printf("RETURNS: ");
	printVisitor->visitExpr(stmt->v.FunctionDef.ret);
    printf("\n");
    depth --;
    printSpaces();
    printf("END\n");
	return 0;
}
static void *visitAssignment(stmt_ty stmt) {
    printSpaces();
    printf("ASSIGNMENT: ");
    printVisitor->visitIdentifier(stmt->v.Assignment.target);
    printf(" TO ");
	printVisitor->visitExpr(stmt->v.Assignment.value);
    printf("\n");
	return 0;
}

static void *visitExpr(expr_ty expr) {
	switch (expr->kind) {
		case Identifier_kind:
			printVisitor->visitIdentifier(expr->v.Identifier.id);
			break;
		case Number_kind:
			printVisitor->visitNumber(expr->v.Number.num);
			break;
		case Binop_kind:
			printVisitor->visitBinop(expr);
			break;
		case Unaryop_kind:
			printVisitor->visitUnaryop(expr);
			break;
		case FunctionCall_kind:
			printVisitor->visitFunctionCall(expr);	
			break;
		case IfThenElse_kind:
			printVisitor->visitIfThenElse(expr);
			break;
	}
	return 0;
}
static void *visitIdentifier(id_ty id) {
    printf("%s", id->name);
	return 0;
}
static void *visitNumber(num_ty num) {
    printf("%.2f", num->v);
	return 0;
}
static void *visitBinop(expr_ty expr) {
    printf("(");
    switch (expr->v.Binop.op) {
        case Add:
            printf("+");
            break;
        case Sub:
            printf("-");
            break;
        case Mult:
            printf("*");
            break;
        case Div:
            printf("/");
            break;
        default:
            printf("%%");
            break;
    }
    printf(" ");
	printVisitor->visitExpr(expr->v.Binop.left);
    printf(" ");
	printVisitor->visitExpr(expr->v.Binop.right);
    printf(")");
	return 0;
}
static void *visitUnaryop(expr_ty expr) {
    printf("(");
    switch (expr->v.Unaryop.op) {
        case Not:
            printf("NOT");
            break;
		default:
			printf("-");
			break;
    }
    printf(" ");
	printVisitor->visitExpr(expr->v.Unaryop.target);
    printf(")");
	return 0;
}
static void *visitFunctionCall(expr_ty expr) {
    printf("FUNCTION CALL: ");
    printVisitor->visitIdentifier(expr->v.FunctionCall.name);
    printf(" WITH ");
	printVisitor->visitExprs(expr->v.FunctionCall.args);
    printf(" ");
	return 0;
}
static void *visitIfThenElse(expr_ty expr) {
    printf("(if ");
	printVisitor->visitExpr(expr->v.IfThenElse.cond);
    printf(" then ");
	printVisitor->visitExpr(expr->v.IfThenElse.then);
    printf(" else ");
	printVisitor->visitExpr(expr->v.IfThenElse.orElse);
    printf(")");
	return 0;
}


void buildPrintVisitor(mod_ty mod) {
    printVisitor = (VisitorTy)malloc(sizeof(Visitor));
    printVisitor->entry = mod;
    // methods
    printVisitor->visitModule = visitModule;
    printVisitor->visitStmts = visitStmts;
    printVisitor->visitExprs = visitExprs;
    printVisitor->visitIds = visitIds;
	printVisitor->visitStmt = visitStmt;
    printVisitor->visitFunctionDef = visitFunctionDef;
    printVisitor->visitAssignment = visitAssignment;
	printVisitor->visitExpr = visitExpr;
	printVisitor->visitIdentifier = visitIdentifier;
    printVisitor->visitNumber = visitNumber;
	printVisitor->visitBinop = visitBinop;
    printVisitor->visitUnaryop = visitUnaryop;
    printVisitor->visitFunctionCall = visitFunctionCall;
    printVisitor->visitIfThenElse = visitIfThenElse;
}

void printASTTree(mod_ty mod) {
    buildPrintVisitor(mod);
    traverseVisitor(printVisitor);
}
