# Compiler Project

This project is my attempt at creating a compiler for an OCaml like language in pure C.

So far I have a working frontend with a tokenizer and parser to create an AST. I have implemented a generic visitor pattern, and have visitors for printing out the tree (debugging tool) and type checking. The last phase of the visitor will be code generation. I plan to use the LLVM infrastructure for this.

References:
- Compilers: Principles, Techniques, and Tools (the dragon book)
- Engineering a Compiler (Cooper and Torczon)
- Crafting Interpreters (Bob Nystrom)

