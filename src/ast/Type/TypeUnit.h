# pragma once

#include "../ast.h"

namespace JaneZ {
class TypeUnit : public ASTNode {
public:
    TypeUnit() {}

    ~TypeUnit() = default;

    void accept(ASTVisitor &visitor) override {
        visitor.visit(*this);
    }
};
}