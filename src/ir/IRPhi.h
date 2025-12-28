# pragma once
#include "IRBlock.h"
# include "IRNode.h"
#include "IRType.h"
# include "IRVisitor.h"
#include "IRValue.h"
#include <memory>
#include <vector>

namespace JaneZ {
class IRVar;
class IRLiteral;
class IRPhi : public IRNode {
public:
    std::shared_ptr<IRVar> result;
    bool firstState;
    std::shared_ptr<IRBlock> firstBlock;
    std::shared_ptr<IRVar> secondState;
    std::shared_ptr<IRBlock> secondBlock;

    IRPhi() = default;
    ~IRPhi() = default;
    void accept(IRVisitor &visitor) override {
        visitor.visit(*this);
    }
};

}