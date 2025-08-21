# pragma once

#include "../ast.h"
#include <memory>
namespace JaneZ {
class Path;
class TypePath : public ASTNode {
private:
    std::unique_ptr<Path> typePath;

public:
    TypePath(std::unique_ptr<Path> tp) : typePath(std::move(tp)) {}

    ~TypePath() = default;

    void accept(ASTVisitor &visitor) override {
        visitor.visit(*this);
    }
};
}