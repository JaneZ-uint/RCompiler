# pragma once
# include "IRNode.h"
#include "IRVar.h"
# include "IRVisitor.h"
#include <memory>

namespace JaneZ {
class IRVar;
class IRBlock;
class IRBr : public IRNode {
public:
    std::shared_ptr<IRVar> condition;
    std::shared_ptr<IRBlock> trueLabel;
    std::shared_ptr<IRBlock> falseLabel;

    IRBr(std::shared_ptr<IRVar> cond,
         std::shared_ptr<IRBlock> tLabel,
         std::shared_ptr<IRBlock> fLabel)
        : condition(std::move(cond)), trueLabel(std::move(tLabel)), falseLabel(std::move(fLabel)) {}
    ~IRBr() = default;
    void accept(IRVisitor &visitor) override {
        visitor.visit(*this);
    }
};

}