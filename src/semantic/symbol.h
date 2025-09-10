# pragma once

#include <memory>
#include <string>
namespace JaneZ {
enum SymbolType{
    Variable,
    Type,
    Function,
    Enum,
    Const,
    Trait,
    Struct,
};



class Symbol{
public:
    std::string name;
    SymbolType type;
    
};
}