#include "src/ast/root.h"
#include "src/ir/CodeGenerator.h"
#include "src/lexer/lexer.h"
#include "src/parser/parser.h"
#include "src/simplifier/simplifier.h"
#include "src/token/token.h"
#include "src/ast/PrintVisitor.h"
#include "src/semantic/globalScope.h"
#include "src/semantic/NameResolver.h"
#include "src/semantic/checker.h"
#include "src/semantic/ConstEvaluator.h"
#include "src/linearScan/regalloc.h"
#include "src/optimize/mem2reg.h"
#include "src/optimize/dominantTree.h"
#include "src/optimize/functionInline.h"
#include "src/optimize/constantFold.h"
#include <filesystem>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>
#include <algorithm>
#include <cctype>
#include <fstream>
#include <regex>
#include <map>
// if(cond) {1} else {2} -3;
namespace fs = std::filesystem;

long long int ir_cnt = 0;
int main(){
    JaneZ::Simplifier simplifier(std::cin);
    std::string source_code = simplifier.work();

    //lexer
    JaneZ::Lexer lexer(source_code);
    auto tokens = lexer.work();

    //parser
    JaneZ::Parser parser(tokens);
    auto root = parser.parse();
    
    //semantic check
    JaneZ::GlobalScopeBuilder global_scope_builder;
    JaneZ::NameResolver name_resolver;
    JaneZ::Checker checker;
    checker.semantic_check(global_scope_builder, name_resolver, *root);
    JaneZ::ConstEvaluator const_evaluator;
    const_evaluator.visit(*root);

    //IR generation
    JaneZ::CodeGenerator code_generator;
    code_generator.generateCode(*root);

    //optimize
    JaneZ::Mem2Reg mem2reg;
    // mem2reg.optimize(code_generator.irRoot);

    JaneZ::DominantTree domTree;
    domTree.optimize(code_generator.irRoot);

    JaneZ::FunctionInline functionInline;
    functionInline.optimize(code_generator.irRoot);

    JaneZ::ConstantFold constantFold;
    constantFold.optimize(code_generator.irRoot);

    //codegen
    JaneZ::regalloc cg;
    cg.generate(code_generator.irRoot);

    std::ifstream builtin("builtin.s");
    if (!builtin.is_open()) {
        std::cerr << "Failed to open builtin.s\n";
        return 1;
    }
    std::cerr << builtin.rdbuf();
}
