# pragma once

#include "../ast.h"
#include <memory>
#include "../../semantic/symbol.h"

namespace JaneZ {
class Path;
class TypePath : public ASTNode {
public:
    std::shared_ptr<Path> typePath;

    std::shared_ptr<Symbol> resolvedSymbol = nullptr;

    TypePath(std::shared_ptr<Path> tp) : typePath(std::move(tp)) {}

    ~TypePath() = default;

    void accept(ASTVisitor &visitor) override {
        visitor.visit(*this);
    }
};
}