# pragma once

#include "pattern.h"
#include <memory>

namespace JaneZ {
class PatternLiteral : public Pattern {
public:
    bool isMinus = false;
    std::shared_ptr<ExprLiteral> pattern_literal;

    PatternLiteral(bool _isMinus, std::shared_ptr<ExprLiteral> literal)
        : isMinus(_isMinus), pattern_literal(std::move(literal)) {}

    ~PatternLiteral() = default;

    void accept(ASTVisitor &visitor) override {
        visitor.visit(*this);
    }
};
}