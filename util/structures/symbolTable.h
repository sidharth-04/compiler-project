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
} STEntry;

struct SymbolTable {
	QueueTy entries;
	SymbolTableTy parent;
	QueueTy children;
	// methods
	int (*contains)(SymbolTableTy, char*);
	int (*search)(SymbolTableTy, char*);
	void (*put)(SymbolTableTy, char*, TypeTy);
	void (*addChild)(SymbolTableTy, SymbolTableTy);
	void (*setParent)(SymbolTableTy, SymbolTableTy);
	void (*setType)(SymbolTableTy, char*, TypeTy);
	void (*setValue)(SymbolTableTy, char*, void*);
};

STEntry *buildSTEntry(TypeTy type, char* name) {
	STEntry *entry = (STEntry*)malloc(sizeof(STEntry));
	entry->type = type;
	entry->name = name;
	return entry;
}
