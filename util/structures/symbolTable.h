#ifndef symboltable_h
#define symboltable_h

#include "../values/BooleanValue.h"
#include "../values/CharValue.h"
#include "../values/FloatValue.h"
#include "../values/FunctionValue.h"
#include "../values/IntValue.h"
#include "../values/RecordValue.h"
#include "../values/StringValue.h"

#include "queue.h"
#include <stdio.h>

typedef struct SymbolTable *SymbolTableTy;

enum stCat {
	VALUE,
	TYPEDEF,
	SCOPEDEF
};

typedef struct {
	void *val;
	char *name;
	TypeTy type;
	int typeDeclaration;
} STEntry;

struct SymbolTable {
	QueueTy entries;
	SymbolTableTy parent;
	QueueTy children;
	// methods
	int (*contains)(SymbolTableTy, char*);
	int (*search)(SymbolTableTy, char*);
	void (*put)(SymbolTableTy, char*, TypeTy, int);
	void (*addChild)(SymbolTableTy, SymbolTableTy);
	void (*setParent)(SymbolTableTy, SymbolTableTy);
	void (*setType)(SymbolTableTy, char*, TypeTy);
	TypeTy (*getType)(SymbolTableTy, char*);
	void (*setValue)(SymbolTableTy, char*, void*);
};

STEntry *buildSTEntry(char* name, TypeTy type, int typeDeclaration) {
	STEntry *entry = (STEntry*)malloc(sizeof(STEntry));
	entry->name = name;
	entry->type = type;
	entry->typeDeclaration = typeDeclaration;
	return entry;
}

STEntry *find(SymbolTableTy st, char *name);
int contains(SymbolTableTy st, char *name);
int search(SymbolTableTy st, char *name);
void put(SymbolTableTy st, char *name, TypeTy type, int typeDeclaration);
void addChild(SymbolTableTy st, SymbolTableTy child);
void setParent(SymbolTableTy st, SymbolTableTy parent);
void setType(SymbolTableTy st, char *name, TypeTy type);
TypeTy getType(SymbolTableTy st, char *name);
void setValue(SymbolTableTy st, char *name, void *val);
SymbolTableTy buildSymbolTable();
void destroySymbolTable(SymbolTableTy st);

#endif
