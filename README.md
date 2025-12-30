# RCompiler

## Overview
A compiler from a Rust-like language to RV32I Assembly via LLVM-IR.

## Build

### Prerequisites
- CMake (>= 3.10)
- C++17 compliant compiler (GCC/Clang)

### Steps
```bash
mkdir build
cd build
cmake ..
make
```

## Usage
The compiler currently reads the source file from `tmp.rx` in the project root and outputs LLVM IR to `test.ll`.

```bash
cd build
./RCompiler
```

## Structure

### Simplifier
- Pre-processes the source code (handles `tmp.rx`).

### Lexer
- Tokenizes the simplified source code.

### Parser
- Pratt Parser (for expression parsing)  Reference: https://zhuanlan.zhihu.com/p/471075848 
- Recursive Descent Parser (for others)
- Simple semantic check during parsing (without constructing scope tree)

### Semantic check
- Scope Tree construction
- Type checking
- Borrow checking
- Constant Evaluation

### IR Generation
- IRTree build
- LLVM-IR Generation (Text format)

## RxLanguage Reference
The project is based on [RLanguage Reference](https://github.com/peterzheng98/RCompiler-Spec/).

## Acknowledgements
- Thanks to TAs for the RLanguage Reference and their guidance.
- Thanks to my boyfriend for his support and encouragement throughout the project.
- Thanks to my roommate for her patience and understanding during late-night coding sessions.