#include <stdio.h>
#include <stdlib.h>

// LLVM Core Libraries
#include <llvm-c/Core.h>
#include <llvm-c/ExecutionEngine.h>
#include <llvm-c/Target.h>
#include <llvm-c/Analysis.h>
#include <llvm-c/BitWriter.h>

#include "util/structures/queue.c"
#include "util/structures/stack.c"
#include "util/typesystem/typeSystem.h"
#include "util/structures/symbolTable.c"
#include "fe/parser.c"
#include "visitors/visitor.h"
// #include "visitors/typecheckVisitor.h"
// #include "visitors/generatorVisitor.h"

#include "util/loggers/errorLogger.h";

// Populate symbol table with primitives
void populatePrimitives(SymbolTableTy st) {
	st->put(st, "int", primitives.Int, 1);
	st->put(st, "bool", primitives.Bool, 1);
	st->put(st, "str", primitives.Str, 1);
	st->put(st, "char", primitives.Char, 1);
	st->put(st, "gen", primitives.Generic, 1);
}

int main(int argc, char const *argv[]) {
    if (argc != 2) {
        logCompilerError("Usage: ./compiler program");
        exit(EXIT_FAILURE);
    }
	char *programName = strcat(argv[1], ".cd");

	buildPrimitives();
	SymbolTableTy st = buildSymbolTable();
	populatePrimitives(st);
	mod_ty astTree = parseProgram(programName, st);
	if (!astTree) return 0;
	// if (!typecheckASTTree(astTree, st)) return 0;

	// Now we can generate perfect llvm code without any errors, all errors have been taken care of
	// LLVMContextRef ctx = LLVMContextCreate();
	// LLVMModuleRef mod = LLVMModuleCreateWithNameInContext("my_module", ctx);
	// Generate the symbol table
	// generateASTTree(astTree, st, ctx, mod);
}
