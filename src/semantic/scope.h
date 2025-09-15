# pragma once

#include "symbol.h"
#include <memory>
#include <unordered_map>
#include <vector>

namespace JaneZ {
class ScopeNode{
private:
    std::unordered_map<std::string, Symbol> value_map;
    
public:
    //std::shared_ptr<ASTNode> ast_node;
    std::shared_ptr<ScopeNode> parent;
    std::vector<std::shared_ptr<ScopeNode>> child;


};

}