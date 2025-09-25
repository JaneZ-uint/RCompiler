# pragma once

#include "../ast/ast.h"
#include <memory>
#include <string>

namespace JaneZ {
enum SymbolType{
    Variable,
    Function,
    Const,
    Struct,
    Enum,
    Trait,
};

class Symbol{
public:
    std::shared_ptr<ASTNode> ast_node;
    SymbolType symbol_type;
    std::string identifier;

    Symbol(std::shared_ptr<ASTNode> node, SymbolType type, const std::string &id)
        : ast_node(node), symbol_type(type), identifier(id) {}

    ~Symbol() = default;
};

}