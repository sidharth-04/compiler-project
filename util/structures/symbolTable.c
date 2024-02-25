#include "symbolTable.h"
#include <string.h>

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
	QueueTy queue = st->entries;
	queue->resetQueue(queue);
   	if (queue->isEmpty) return 0;
    while (queue->hasNextElement(queue)) {
        STEntry *entry = (STEntry *)queue->getNextElement(queue);
		if (strcmp(entry->name, name) == 0) return 1;
	}
	return 0;
}

int search(SymbolTableTy st, char *name) {
	while (st) {
		if (st->contains(st, name)) return 1;
		st = st->parent;
	}
	return 0;
}

void put(SymbolTableTy st, char *name, TypeTy type) {
	STEntry *entry = buildSTEntry(type, name);
	QueueTy queue = st->entries;
	queue->attachNodeToQueue(queue, entry);
}

void addChild(SymbolTableTy st, SymbolTableTy child) {
	QueueTy queue = st->children;
	queue->attachNodeToQueue(queue, child);
}

void setParent(SymbolTableTy st, SymbolTableTy parent) {
	st->parent = parent;
}

void setType(SymbolTableTy st, char *name, TypeTy type) {
	STEntry *entry = find(st, name);
	entry->type = type;
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
	st->setValue = setValue;
	return st;
}

void destroySymbolTable(SymbolTableTy st) {
	return;
}
