# pragma once

#include <memory>
#include <unordered_map>
#include "../ast/ast.h"
#include "symbol.h"
#include <vector>

namespace JaneZ {
class ScopeNode{    
public:
    std::shared_ptr<ASTNode> ast_node;
    std::shared_ptr<ScopeNode> parent;
   
    std::unordered_map<std::string, std::shared_ptr<Symbol>> type_table;
    std::unordered_map<std::string, std::shared_ptr<Symbol>> value_table;

};

}