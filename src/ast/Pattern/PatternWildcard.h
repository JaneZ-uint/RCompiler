# pragma once

#include "pattern.h"
#include <memory>
#include <utility>
namespace JaneZ {
class PatternWildCard : public Pattern {
public:
    std::shared_ptr<ExprUnderscore> pattern_wildcard;

    PatternWildCard(std::shared_ptr<ExprUnderscore> pw) : pattern_wildcard(std::move(pw)) {}

    ~PatternWildCard() = default;

    void accept(ASTVisitor &visitor) override {
        visitor.visit(*this);
    }
};
}