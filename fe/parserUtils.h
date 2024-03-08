SymbolTableTy getTopSymbolTable(parserState *ps) {
	return (SymbolTableTy)ps->stStack->getTop(ps->stStack);
}
