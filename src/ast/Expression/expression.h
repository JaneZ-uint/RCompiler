# pragma once
# include "../ast.h"
#include "../../semantic/symbol.h"
#include <memory>

namespace JaneZ {
class Expression : public ASTNode{
public:
    std::shared_ptr<Symbol> resolvedSymbol1 = nullptr;
    std::shared_ptr<Symbol> resolvedSymbol2 = nullptr;
    long long int constValue = 0;

    Expression() : ASTNode() {}
    virtual ~Expression() = default;
    virtual void accept(ASTVisitor &visitor) = 0;
};
}