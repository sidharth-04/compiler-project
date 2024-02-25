typedef struct Stack *StackTy;
typedef struct StackNode *StackNodeTy;

struct StackNode {
	void *curr;
	StackNodeTy prev;
};
struct Stack {
	StackNodeTy top;
	void (*push)(StackTy, void*);
	void *(*pop)(StackTy);
	void *(*getTop)(StackTy);
};


