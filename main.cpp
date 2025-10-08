#include "src/ast/root.h"
# include "src/lexer/lexer.h"
# include "src/parser/parser.h"
# include "src/simplifier/simplifier.h"
# include "src/token/token.h"
# include "src/ast/PrintVisitor.h"
# include "src/semantic/globalScope.h"
# include "src/semantic/NameResolver.h"
# include "src/semantic/checker.h"
#include <memory>
#include <stdexcept>
# include <string>
# include <vector>

int main(){
    JaneZ::Simplifier simplifier("../RCompiler-Testcases/semantic-1/basic35/basic35.rx");
    //JaneZ::Simplifier simplifier("1.rs");
    std::string source_code = simplifier.work();
    //simplifier.print();
    JaneZ::Lexer lexer(source_code);
    std::vector<JaneZ::Token> tokens = lexer.work();
    //lexer.print();
    JaneZ::Parser parser(tokens);
    std::shared_ptr<JaneZ::ASTRootNode> root = parser.parse();
    JaneZ::PrintVisitor printer;
    printer.visit(*root);
    JaneZ::GlobalScopeBuilder global_scope_builder;
    JaneZ::NameResolver name_resolver;
    JaneZ::Checker checker;
    checker.semantic_check(global_scope_builder,name_resolver,*root);
    return 0;
}