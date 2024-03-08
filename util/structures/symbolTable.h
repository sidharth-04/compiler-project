#include "../values/BooleanValue.h"
#include "../values/CharValue.h"
#include "../values/FloatValue.h"
#include "../values/FunctionValue.h"
#include "../values/IntValue.h"
#include "../values/RecordValue.h"
#include "../values/StringValue.h"

typedef struct SymbolTable *SymbolTableTy;

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

void printSymbolTable(SymbolTableTy st) {
	printf("Printing SymbolTable...\n");
	QueueTy queue = st->entries;
	queue->resetQueue(queue);
	int i = 1;
	printf("----------------------\n");
	if (queue->isEmpty) printf("Queue is empty!\n");
	while (queue->hasNextElement(queue)) {
		STEntry *entry = (STEntry *)queue->getNextElement(queue);
		printf("%d: %s\n", i, entry->name);
		i ++;
	}
	QueueTy children = st->children;
	children->resetQueue(children);
	if (!children->isEmpty) printf("Here are the children:\n");
	while (children->hasNextElement(children)) {
		printSymbolTable(children->getNextElement(children));
	}
	printf("----------------------\n");
}
