#include "testutils.h"
#include "../util/typesystem/primitives.h"
#include "../util/structures/symbolTable.h"

void testCreateSymbolTable() {
	SymbolTableTy st = buildSymbolTable();
}

void testPutInt() {
	SymbolTableTy st = buildSymbolTable();
	st->put(st, "a", buildPrimitive(INT), 0);
	assertTrue(st->contains(st, "a"));
	assertFalse(st->contains(st, "b"));
	st->put(st, "b", buildPrimitive(CHAR), 0);
	assertTrue(st->contains(st, "b"));
	assertTrue(st->contains(st, "a"));
}

void testParentSymbolTableSearch() {
	SymbolTableTy st1 = buildSymbolTable();
	SymbolTableTy st2 = buildSymbolTable();
	SymbolTableTy st3 = buildSymbolTable();
	st1->put(st1, "a", buildPrimitive(INT), 0);
	st1->addChild(st1, st2); // Add st2 as child
	st3->setParent(st3, st2);
	assertTrue(st1->contains(st1, "a"));
	assertFalse(st3->contains(st3, "a"));
	assertFalse(st2->contains(st3, "a"));
	assertTrue(st3->search(st3, "a"));
}

void runSymbolTableTests() {
	printf("running symbol table tests\n");
	testCreateSymbolTable();
	testPutInt();
	testParentSymbolTableSearch();
}
