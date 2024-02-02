typedef struct _mod *mod_ty;
typedef struct _stmt *stmt_ty;
typedef struct _expr *expr_ty;
typedef struct _id *id_ty;
typedef struct _num *num_ty;

typedef struct _stmt_seq *stmt_seq_ty;
typedef struct _expr_seq *expr_seq_ty;
typedef struct _id_seq *id_seq_ty;

typedef enum _boolop { And=1, Or=2 } boolop_ty;
typedef enum _operator { Add=1, Sub=2, Mult=3, Div=4, Mod=5} operator_ty;
typedef enum _unaryop { Not=1, Min=2 } unaryop_ty;
typedef enum _cmpop { Eq=1, NotEq=2, Lt=3, LtE=4, Gt=5, GtE=6 } cmpop_ty;
