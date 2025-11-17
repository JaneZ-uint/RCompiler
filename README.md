# RCompiler

## Overview
A compiler from a Rust-like language to RV32I Assembly via LLVM-IR.

## Structure

### Lexer

### Parser
- Pratt Parser (for expression parsing)  Reference: https://zhuanlan.zhihu.com/p/471075848 
- Recursive Descent Parser (for others)
- Simple semantic check during parsing (without constructing scope tree)
### Semantic check
- Scope Tree construction
- Type checking
- Borrow checking
### IR Generation
- IRNode build
- LLVM-IR Generation

## Base
The project is based on [RLanguage Reference](https://github.com/peterzheng98/RCompiler-Spec/).