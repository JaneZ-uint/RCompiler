# pragma once

#include "type.h"
#include <memory>

namespace JaneZ {
class TypeReference : public Type {
private:
    std::unique_ptr<Type> typeNoBounds;
    bool is_mut;

public:
    TypeReference(std::unique_ptr<Type> tnb,bool im = false) : typeNoBounds(std::move(tnb)), is_mut(std::move(im)) {}

    ~TypeReference() = default;

    void accept(ASTVisitor &visitor) override {
        visitor.visit(*this);
    }
};
}