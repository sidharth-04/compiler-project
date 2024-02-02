struct PrimitiveTypeList {
	TypeTy Int;
	TypeTy Bool;
	TypeTy Str;
	TypeTy Char;
};

TypeTy buildPrimitive(enum TypeCat cat) {
	TypeTy built = (TypeTy)malloc(sizeof(struct Type));
	built->cat = cat;
	built->numNested = 0;
	return built;
}

struct PrimitiveTypeList primitives;
void buildPrimitives() {
	primitives.Int = buildPrimitive(INT);
	primitives.Bool = buildPrimitive(BOOL);
	primitives.Str = buildPrimitive(STR);
	primitives.Char = buildPrimitive(CHAR);
}

TypeTy getPrimitive(enum TypeCat cat) {
	switch(cat) {
		case INT:
			return primitives.Int;
		case BOOL:
			return primitives.Bool;
		case STR:
			return primitives.Str;
		case CHAR:
			return primitives.Char;
	};
	return 0;
}
