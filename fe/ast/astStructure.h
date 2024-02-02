enum _mod_kind {
  Stmts_kind = 1
};
struct _mod {
  enum _mod_kind kind;
  char *name;
  union {
    struct {
      stmt_seq_ty body;
    } Stmts;
  } v;
};

struct _stmt_seq {
  QueueTy stmt_queue;
};
struct _expr_seq {
  QueueTy expr_queue;
};
struct _id_seq {
  QueueTy id_queue;
};

enum _stmt_kind {
  FunctionDef_kind = 1,
  Assignment_kind = 2
};
struct _stmt {
  enum _stmt_kind kind;
  union {
    struct {
      id_ty name;
      id_seq_ty args;
      stmt_seq_ty body;
      expr_ty ret;
    } FunctionDef;
    struct {
      id_ty target;
      expr_ty value;
    } Assignment;
  } v;
};

enum _expr_kind {
  Identifier_kind = 1,
  Number_kind = 2,
  Binop_kind = 3,
  Unaryop_kind = 4,
  FunctionCall_kind = 5,
  IfThenElse_kind = 6
};
struct _expr {
  enum _expr_kind kind;
  union {
    struct {
      id_ty id;
    } Identifier;
    struct {
      num_ty num;
    } Number;
    struct {
      expr_ty left;
      operator_ty op;
      expr_ty right;
    } Binop;
    struct {
      operator_ty op;
      expr_ty target;
    } Unaryop;
    struct {
      id_ty name;
      expr_seq_ty args;
    } FunctionCall;
    struct {
      expr_ty cond;
      expr_ty then;
      expr_ty orElse;
    } IfThenElse;
  } v;
};

struct _id {
  char *name;
};
struct _num {
  double v;
};
