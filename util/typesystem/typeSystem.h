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

#include "primitives.h"
int checkTypeCat(TypeTy, enum TypeCat);
int typeMatch(TypeTy, TypeTy);

int typeMatch(TypeTy first, TypeTy second) {
	if (checkTypeCat(first, GENERIC) || checkTypeCat(second, GENERIC)) return 1;
	if (first->cat != second->cat) return 0;
	if (first->numNested != second->numNested) return 0;
	for (int i = 0; i < first->numNested; i ++) {
		if (!typeMatch(first->nested[i], second->nested[i])) return 0;
	}
	return 1;
}

int checkTypeCat(TypeTy type, enum TypeCat cat) {
	if (type->cat != cat) return 0;
	return 1;
}

void coerceType(TypeTy first, TypeTy second) {
	if (checkTypeCat(first, GENERIC)) {
			
	}
}

char *typeToString(TypeTy type) {
	switch (type->cat) {
		case GENERIC:
			return "generic";
		case INT:
			return "int";
		case BOOL:
			return "bool";
		case STR:
			return "str";
		case CHAR:
			return "char";
	}
}
