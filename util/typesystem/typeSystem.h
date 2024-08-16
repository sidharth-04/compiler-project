#ifndef type_system_h
#define type_system_h

enum TypeCat {
	GENERIC,
	INT,
	BOOL,
	STR,
	CHAR,
};

typedef struct Type *TypeTy;

// NEED to improve the definition of this struct, it needs to WAY more flexible
// Tree like structure, can have nexted type definitions
struct Type {
	enum TypeCat cat;
	int numNested;
	TypeTy nested[];
};

int typeMatch(TypeTy first, TypeTy second);
int checkTypeCat(TypeTy type, enum TypeCat cat);
void coerceType(TypeTy first, TypeTy second);
const char *typeToString(TypeTy type);

#endif
