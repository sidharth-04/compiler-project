#include "testutils.h"
#include "../util/typesystem/primitives.h"
#include "../util/structures/symbolTable.h"

void testCreateSymbolTable() {
	SymbolTableTy st = buildSymbolTable();
}

void testPutInt() {
	SymbolTableTy st = buildSymbolTable();
	st->put(st, "a", buildPrimitive(INT), 0);
	ASSERT_TRUE(st->contains(st, "a"));
	ASSERT_FALSE(st->contains(st, "b"));
	st->put(st, "b", buildPrimitive(CHAR), 0);
	ASSERT_TRUE(st->contains(st, "b"));
	ASSERT_TRUE(st->contains(st, "a"));
}

void testParentSymbolTableSearch() {
	SymbolTableTy st1 = buildSymbolTable();
	SymbolTableTy st2 = buildSymbolTable();
	SymbolTableTy st3 = buildSymbolTable();
	st1->put(st1, "a", buildPrimitive(INT), 0);
	st1->addChild(st1, st2); // Add st2 as child
	st3->setParent(st3, st2);
	ASSERT_TRUE(st1->contains(st1, "a"));
	ASSERT_FALSE(st3->contains(st3, "a"));
	ASSERT_FALSE(st2->contains(st3, "a"));
	ASSERT_TRUE(st3->search(st3, "a"));
}

void runSymbolTableTests() {
	testCreateSymbolTable();
	testPutInt();
	testParentSymbolTableSearch();
}
