# pragma once

#include "../ast/astvisitor.h"

namespace JaneZ {
class NameResolver : public ASTVisitor{
public:
    NameResolver() = default;

    ~NameResolver() = default;
    
};
}