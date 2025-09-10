# pragma once

#include <memory>
#include <vector>
#include "SymbolTable.h"

namespace JaneZ {
class ScopeNode{
private:
    SymbolTable symbol_table;
    
public:
    std::shared_ptr<ScopeNode> parent;
    std::vector<std::shared_ptr<ScopeNode>> child;

};

}