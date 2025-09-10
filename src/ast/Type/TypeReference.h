# pragma once

#include "../ast.h"
#include <memory>

namespace JaneZ {
class TypeReference : public ASTNode {
public:
    std::shared_ptr<ASTNode> typeNoBounds;
    bool is_mut;

    TypeReference(std::shared_ptr<ASTNode> tnb,bool im = false) : 
    typeNoBounds(std::move(tnb)), is_mut(std::move(im)) {}

    ~TypeReference() = default;

    void accept(ASTVisitor &visitor) override {
        visitor.visit(*this);
    }
};
}