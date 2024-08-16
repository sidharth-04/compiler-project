#include "symbolTable.h"
#include <string.h>

STEntry *buildSTEntry(char* name, TypeTy type, int typeDeclaration) {
	STEntry *entry = (STEntry*)malloc(sizeof(STEntry));
	entry->name = name;
	entry->type = type;
	entry->typeDeclaration = typeDeclaration;
	return entry;
}

// Generic find operation
STEntry *find(SymbolTableTy st, char *name) {
	QueueTy queue = st->entries;
	queue->resetQueue(queue);
   	if (queue->isEmpty) return 0;
    while (queue->hasNextElement(queue)) {
        STEntry *entry = (STEntry *)queue->getNextElement(queue);
		if (strcmp(entry->name, name) == 0) return entry;	
	}
	return 0;
}

int contains(SymbolTableTy st, char *name) {
	STEntry *entry = find(st, name);
	if (!entry) return 0;
	return 1;
}

int search(SymbolTableTy st, char *name) {
	while (st) {
		if (st->contains(st, name)) return 1;
		st = st->parent;
	}
	return 0;
}

void put(SymbolTableTy st, char *name, TypeTy type, int typeDeclaration) {
	STEntry *entry = buildSTEntry(name, type, typeDeclaration);
	QueueTy queue = st->entries;
	queue->attachNodeToQueue(queue, entry);
}

void addChild(SymbolTableTy st, SymbolTableTy child) {
	QueueTy queue = st->children;
	queue->attachNodeToQueue(queue, child);
	if (child->parent != st) child->setParent(child, st);
}

void setParent(SymbolTableTy st, SymbolTableTy parent) {
	st->parent = parent;
	QueueTy queue = parent->children;
	queue->resetQueue(queue);
	int alreadyAChild = 0;
	while (queue->hasNextElement(queue)) {
		if (queue->getNextElement(queue) != st) continue;
		alreadyAChild = 1;
		break;
	}
	if (!alreadyAChild) parent->addChild(parent, st);
}

void setType(SymbolTableTy st, char *name, TypeTy type) {
	STEntry *entry = find(st, name);
	entry->type = type;
}

TypeTy getType(SymbolTableTy st, char *name) {
	STEntry *entry = find(st, name);
	if (!entry) return 0;
	if (!entry->typeDeclaration) return 0;
	return entry->type;
}

void setValue(SymbolTableTy st, char *name, void *val) {
	STEntry *entry = find(st, name);
	entry->val = val;
}

SymbolTableTy buildSymbolTable() {
	SymbolTableTy st = (SymbolTableTy)malloc(sizeof(struct SymbolTable));
	st->entries = createQueue();
	st->children = createQueue();
	// methods
	st->contains = contains;
	st->search = search;
	st->put = put;
	st->addChild = addChild;
	st->setParent = setParent;
	st->setType = setType;
	st->getType = getType;
	st->setValue = setValue;
	return st;
}

void destroySymbolTable(SymbolTableTy st) {
	return;
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
		printf("%d %s: %s\n", i, entry->name, typeToString(entry->type));
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
