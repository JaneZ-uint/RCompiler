# pragma once

#include "expression.h"
#include <memory>
#include <vector>
namespace JaneZ {
class Pattern;
struct MatchArm{
    std::shared_ptr<Pattern> pattern;
    std::shared_ptr<Expression> guard;
    std::shared_ptr<Expression> body;

};
class ExprMatch : public Expression {
public:
    std::shared_ptr<Expression> Scrutinee;
    std::vector<MatchArm> MatchArms; 

    ExprMatch(std::shared_ptr<Expression> scrutinee, std::vector<MatchArm> matchArms)
        : Scrutinee(std::move(scrutinee)), MatchArms(std::move(matchArms)) {}

    ~ExprMatch() = default;

    void accept(ASTVisitor &visitor) override {
        visitor.visit(*this);
    }
};
}