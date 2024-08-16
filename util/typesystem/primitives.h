#ifndef type_primitives_h
#define type_primitives_h

#include <stdlib.h>
#include "typeSystem.h"

struct PrimitiveTypeList {
	TypeTy Int;
	TypeTy Bool;
	TypeTy Str;
	TypeTy Char;
	TypeTy Generic;
};

TypeTy buildPrimitive(enum TypeCat cat);
void buildPrimitives();
TypeTy getPrimitive(enum TypeCat cat);

#endif
