#include "src/lexer/lexer.h"
# include "src/simplifier/simplifier.h"
#include <iostream>
#include <string>

int main(){
    JaneZ::Simplifier simplifier("8.rs");
    std::string source_code = simplifier.work();
    //simplifier.print();
    JaneZ::Lexer lexer(source_code);
    lexer.work();
    lexer.print();
}