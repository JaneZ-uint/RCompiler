#include "src/lexer/lexer.h"
#include "src/parser/parser.h"
# include "src/simplifier/simplifier.h"
#include "src/token/token.h"
#include <iostream>
#include <string>
#include <vector>

int main(){
    JaneZ::Simplifier simplifier("array1.rs");
    std::string source_code = simplifier.work();
    //simplifier.print();
    JaneZ::Lexer lexer(source_code);
    std::vector<JaneZ::Token> tokens = lexer.work();
    //lexer.print();
    JaneZ::Parser parser(tokens);
    parser.parse();
}