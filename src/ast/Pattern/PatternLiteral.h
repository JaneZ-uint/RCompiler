# pragma once

#include "pattern.h"
#include <memory>
#include <string>

namespace JaneZ {
class PatternLiteral : public Pattern {
private:
    std::string identifier;
    std::unique_ptr<ExprLiteral> pattern_literal;

public:
    PatternLiteral(std::string id, std::unique_ptr<ExprLiteral> literal)
        : identifier(std::move(id)), pattern_literal(std::move(literal)) {}

    ~PatternLiteral() = default;

    void accept(ASTVisitor &visitor) override {
        visitor.visit(*this);
    }
};
}