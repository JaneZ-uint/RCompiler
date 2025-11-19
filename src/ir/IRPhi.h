# pragma once
# include "IRNode.h"
# include "IRVisitor.h"
#include <memory>

namespace JaneZ {
class IRVar;
class IRLiteral;
class IRPhi : public IRNode {
public:
    std::shared_ptr<IRVar> condition;
    std::shared_ptr<IRVar> left;
    std::shared_ptr<IRLiteral> leftLiteral;
    std::shared_ptr<IRVar> right;
    std::shared_ptr<IRLiteral> rightLiteral;

    IRPhi(std::shared_ptr<IRVar> cond,
        std::shared_ptr<IRVar> l,
        std::shared_ptr<IRLiteral> lLit,
        std::shared_ptr<IRVar> r,
        std::shared_ptr<IRLiteral> rLit): condition(std::move(cond)),left(std::move(l)),
        leftLiteral(std::move(lLit)),right(std::move(r)),rightLiteral(std::move(rLit)){}
    ~IRPhi() = default;
    void accept(IRVisitor &visitor) override {
        visitor.visit(*this);
    }
};

}