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
    std::ofstream out("../test.ll");
    if (!out.is_open()) {
        std::cerr << "Failed to open log file\n";
        return 1;
    }

    // 2. 备份原来的 streambuf
    auto *cout_buf = std::cout.rdbuf();
    auto *cerr_buf = std::cerr.rdbuf();

    // 3. 重定向
    std::cout.rdbuf(out.rdbuf());
    std::cerr.rdbuf(out.rdbuf());
    JaneZ::Simplifier simplifier("../tmp.rx");
    std::string source_code = simplifier.work();

    JaneZ::Lexer lexer(source_code);
    auto tokens = lexer.work();

    JaneZ::Parser parser(tokens);
    auto root = parser.parse();
    
    // JaneZ::PrintVisitor print_visitor;
    // print_visitor.visit(*root);

    JaneZ::GlobalScopeBuilder global_scope_builder;
    JaneZ::NameResolver name_resolver;
    JaneZ::Checker checker;
    
    checker.semantic_check(global_scope_builder, name_resolver, *root);
    
    JaneZ::ConstEvaluator const_evaluator;
    const_evaluator.visit(*root);

    JaneZ::CodeGenerator code_generator;
    code_generator.generateCode(*root);

    std::cout.rdbuf(cout_buf);
    std::cerr.rdbuf(cerr_buf);
}