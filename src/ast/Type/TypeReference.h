# pragma once

#include "../ast.h"
#include <memory>

namespace JaneZ {
class TypeReference : public ASTNode {
private:
    std::unique_ptr<ASTNode> typeNoBounds;
    bool is_mut;

public:
    TypeReference(std::unique_ptr<ASTNode> tnb,bool im = false) : 
    typeNoBounds(std::move(tnb)), is_mut(std::move(im)) {}

    ~TypeReference() = default;

    void accept(ASTVisitor &visitor) override {
        visitor.visit(*this);
    }
};
}