enum TypeCat {
	GENERIC,
	INT,
	FLOAT,
	STR,
	CHAR,
	BOOL,
	FUNC,
	REC,
};

typedef struct Type *TypeTy;

struct Type {
	enum TypeCat cat;
	int numNested;
	TypeTy nested[];
};

#include "primitives.h";

TypeTy buildFunctionType(int numNested, TypeTy nested[]) {
	TypeTy built = (TypeTy)malloc(sizeof(struct Type));
	built->cat = FUNC;
	built->numNested = numNested;
	for (int i = 0; i < numNested; i ++) {
		built->nested[i] = nested[i];
	}
	return built;
}

TypeTy buildRecordType(int numNested, TypeTy nested[]) {
	TypeTy built = (TypeTy)malloc(sizeof(struct Type));
	built->cat = REC;
	built->numNested = numNested;
	for (int i = 0; i < numNested; i ++) {
		built->nested[i] = nested[i];
	}
	return built;
}

int typeMatch(TypeTy first, TypeTy second) {
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
