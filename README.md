# RCompiler

## Overview
A compiler from a Rust-like language to RV32I Assembly via LLVM-IR.

## Structure

### Lexer

### Parser
- Pratt Parser (for expression parsing)  Reference: https://zhuanlan.zhihu.com/p/471075848 
- Recursive Descent Parser (for others)

### Semantic check
TBD:
- Function missing return statement
- Mutable variable
- Scope tree build

## Base
The project is based on [RLanguage Reference](https://github.com/peterzheng98/RCompiler-Spec/).