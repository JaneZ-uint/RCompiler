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

### Code Generation
- Instruction Selection (from LLVM-IR to RV32I assembly)
- Stack Management
- Assembly Code Generation (RV32I target)
- Builtin Functions Support (builtin.s)

### Register Allocation
- Linear Scan Register Allocation Algorithm
- Graph Coloring Register Allocation Algorithm TBD

### IR Generation Optimization 
- Mem2Reg 
- Function Inlining TBD
- SCCP TBD
- Dead Code Elimination TBD
- Strength Reduction TBD
- Loop Analyis and Optimization TBD
- Maybe more

## Test
You can find all testcases in [RCompiler-Testcases](https://github.com/peterzheng98/RCompiler-Testcases).We only test testcases under the `semantic2` folder, which are more comprehensive and cover all features of the language.
### IR Generation Test
```bash
./ir_test.sh
```

### ASM Generation Test
```bash
./asm_test.sh
```

## RxLanguage Reference
The project is based on [RLanguage Reference](https://github.com/peterzheng98/RCompiler-Spec/).

## Acknowledgements
- Thanks to TAs for the RLanguage Reference and their guidance.
- Thanks to my boyfriend for his support and encouragement throughout the project.
- Thanks to my roommate for her patience and understanding during late-night coding sessions.