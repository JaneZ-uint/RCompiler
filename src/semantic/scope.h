# pragma once

#include <memory>
#include <vector>

namespace JaneZ {
class ScopeNode{
private:

public:
    std::unique_ptr<ScopeNode> parent;
    std::vector<std::unique_ptr<ScopeNode>> child;
    
};

}