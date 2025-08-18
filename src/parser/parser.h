#pragma once

#include <vector>
namespace JaneZ {
class Token;
class Parser{
private:
    std::vector<Token> tokens;

public:
    Parser(std::vector<Token> t) : tokens(std::move(t)) {}

    
};

}