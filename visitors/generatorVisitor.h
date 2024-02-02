static VisitorTy genVisitor;
LLVMContextRef llvmCtx;
LLVMModuleRef llvmModule;
LLVMBuilderRef llvmBuilder;
SymbolTableTy st;

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
    genVisitor->visitStmts(body);
	return 0;
}

static void *visitStmts(stmt_seq_ty stmts) {
    ast_queue_ty queue = stmts->stmt_queue;
    int n = queue->size;
 	print("Num Stmts:");
	printInt(n);
   	if (n == 0) {
		return 0;
    }
    queue_node_ty currNode = (queue_node_ty)(queue->head);
    while (--n >= 0) {
        stmt_ty stmt = (stmt_ty)(currNode->value);
		genVisitor->visitStmt(stmt);
        currNode = currNode->next;
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
		genVisitor->visitExpr(expr);
        currNode = currNode->next;
    }
	return 0;
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
        genVisitor->visitIdentifier(id);
        currNode = currNode->next;
    }
	return 0;
}

static void *visitStmt(stmt_ty stmt) {
	switch (stmt->kind) {
		case FunctionDef_kind:
			genVisitor->visitFunctionDef(stmt);
			break;
		case Assignment_kind:
			genVisitor->visitAssignment(stmt);
			break;
	}
	return 0;
}
static void *visitFunctionDef(stmt_ty stmt) {
    genVisitor->visitIdentifier(stmt->v.FunctionDef.name);
	genVisitor->visitIds(stmt->v.FunctionDef.args);
	genVisitor->visitStmts(stmt->v.FunctionDef.body);
	genVisitor->visitExpr(stmt->v.FunctionDef.ret);
	return 0;
}
static void *visitAssignment(stmt_ty stmt) {
	print("Starting Assnmt");
    LLVMValueRef result = (LLVMValueRef)genVisitor->visitIdentifier(stmt->v.Assignment.target);
	genVisitor->visitExpr(stmt->v.Assignment.value);
	print("Assignment complete");
	LLVMDumpValue(result);
	return 0;
}

static void *visitExpr(expr_ty expr) {
	switch (expr->kind) {
		case Identifier_kind:
			return genVisitor->visitIdentifier(expr->v.Identifier.id);
		case Number_kind:
			return genVisitor->visitNumber(expr->v.Number.num);
		case Binop_kind:
			return genVisitor->visitBinop(expr);
		case Unaryop_kind:
			return genVisitor->visitUnaryop(expr);
		case FunctionCall_kind:
			return genVisitor->visitFunctionCall(expr);	
		case IfThenElse_kind:
			return genVisitor->visitIfThenElse(expr);
	}
	return 0;
}
static void *visitIdentifier(id_ty id) {
    print(id->name);
	return LLVMConstReal(LLVMFloatTypeInContext(llvmCtx), 10.0);
}
static void *visitNumber(num_ty num) {
	LLVMValueRef result = (LLVMValueRef)LLVMConstReal(LLVMFloatTypeInContext(llvmCtx), num->v);
	LLVMDumpValue(result);
	return result;
}
static void *visitBinop(expr_ty expr) {
 	LLVMValueRef left = (LLVMValueRef)genVisitor->visitExpr(expr->v.Binop.left);
	LLVMValueRef right = (LLVMValueRef)genVisitor->visitExpr(expr->v.Binop.right);
	switch (expr->v.Binop.op) {
        case Add:
            return LLVMBuildFAdd(llvmBuilder, left, right, "fadd");
        case Sub:
            return LLVMBuildFSub(llvmBuilder, left, right, "fsub");
        case Mult:
			return LLVMBuildFMul(llvmBuilder, left, right, "fmult");
        case Div:
            return LLVMBuildFDiv(llvmBuilder, left, right, "fdiv");
		default:
			return LLVMBuildFRem(llvmBuilder, left, right, "frem");
    }
}
static void *visitUnaryop(expr_ty expr) {
	LLVMValueRef target = (LLVMValueRef)genVisitor->visitExpr(expr->v.Unaryop.target);
    switch (expr->v.Unaryop.op) {
        case Not:
			return LLVMBuildNot(llvmBuilder, target, "not");
		default:
			return LLVMBuildFNeg(llvmBuilder, target, "fneg");
    }
}
static void *visitFunctionCall(expr_ty expr) {
    genVisitor->visitIdentifier(expr->v.FunctionCall.name);
	genVisitor->visitExprs(expr->v.FunctionCall.args);
	return 0;
}
static void *visitIfThenElse(expr_ty expr) {
	genVisitor->visitExpr(expr->v.IfThenElse.cond);
	genVisitor->visitExpr(expr->v.IfThenElse.then);
	genVisitor->visitExpr(expr->v.IfThenElse.orElse);
	return 0;
}


void buildGeneratorVisitor(mod_ty mod) {
    genVisitor = (VisitorTy)malloc(sizeof(Visitor));
    genVisitor->entry = mod;
    // methods
    genVisitor->visitModule = visitModule;
    genVisitor->visitStmts = visitStmts;
    genVisitor->visitExprs = visitExprs;
    genVisitor->visitIds = visitIds;
	genVisitor->visitStmt = visitStmt;
    genVisitor->visitFunctionDef = visitFunctionDef;
    genVisitor->visitAssignment = visitAssignment;
	genVisitor->visitExpr = visitExpr;
	genVisitor->visitIdentifier = visitIdentifier;
    genVisitor->visitNumber = visitNumber;
	genVisitor->visitBinop = visitBinop;
    genVisitor->visitUnaryop = visitUnaryop;
    genVisitor->visitFunctionCall = visitFunctionCall;
    genVisitor->visitIfThenElse = visitIfThenElse;
}

void generateASTTree(mod_ty mod, SymbolTableTy stRef, LLVMContextRef ctxRef, LLVMModuleRef moduleRef) {
    buildGeneratorVisitor(mod);
	st = stRef;
	llvmCtx = ctxRef;
	llvmModule = moduleRef;
	llvmBuilder = LLVMCreateBuilderInContext(llvmCtx);
	traverseVisitor(genVisitor);
}
