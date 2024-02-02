typedef struct {
    mod_ty entry;
    void* (*visitModule)(mod_ty);
    void* (*visitStmts)(stmt_seq_ty);
    void* (*visitExprs)(expr_seq_ty);
    void* (*visitIds)(id_seq_ty);
	void* (*visitStmt)(stmt_ty);
    void* (*visitFunctionDef)(stmt_ty);
    void* (*visitAssignment)(stmt_ty);
	void* (*visitExpr)(expr_ty);
	void* (*visitIdentifier)(id_ty);
    void* (*visitNumber)(num_ty);
	void* (*visitBinop)(expr_ty);
    void* (*visitUnaryop)(expr_ty);
    void* (*visitFunctionCall)(expr_ty);
    void* (*visitIfThenElse)(expr_ty);
} Visitor;

typedef Visitor *VisitorTy;

void traverseVisitor(VisitorTy visitor) {
    visitor->visitModule(visitor->entry);
}

void destroyVisitor(VisitorTy visitor) {
    // Implement to free memory
}
