# pragma once

#include "expression.h"
#include <memory>
#include <vector>
namespace JaneZ {
class Pattern;
struct MatchArm{
    std::unique_ptr<Pattern> pattern;
    std::unique_ptr<Expression> guard;
    std::unique_ptr<Expression> body;

};
class ExprMatch : public Expression {

private:
    std::unique_ptr<Expression> Scrutinee;
    std::vector<MatchArm> MatchArms; 

public:
    ExprMatch(std::unique_ptr<Expression> scrutinee, std::vector<MatchArm> matchArms)
        : Scrutinee(std::move(scrutinee)), MatchArms(std::move(matchArms)) {}

    ~ExprMatch() = default;

    void accept(ASTVisitor &visitor) override {
        visitor.visit(*this);
    }
};
}