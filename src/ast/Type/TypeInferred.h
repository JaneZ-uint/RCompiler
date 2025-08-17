# pragma once

#include "type.h"
namespace JaneZ {
class TypeInferred : public Type {
public:
    TypeInferred(){}

    ~TypeInferred() = default;

    void accept(ASTVisitor &visitor) override {
        visitor.visit(*this);
    }
};
}