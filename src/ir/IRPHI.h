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
class IRPHI : public IRNode {
public:
    std::shared_ptr<IRVar> result;
    std::shared_ptr<IRValue> firstState;
    std::shared_ptr<IRBlock> firstBlock;
    std::shared_ptr<IRValue> secondState;
    std::shared_ptr<IRBlock> secondBlock;

    IRPHI() = default;
    IRPHI(std::shared_ptr<IRVar> result,
          std::shared_ptr<IRValue> firstState,
          std::shared_ptr<IRBlock> firstBlock,
          std::shared_ptr<IRValue> secondState,
          std::shared_ptr<IRBlock> secondBlock)
        : result(std::move(result)),
          firstState(std::move(firstState)),
          firstBlock(std::move(firstBlock)),
          secondState(std::move(secondState)),
          secondBlock(std::move(secondBlock)) {}
    virtual ~IRPHI() = default;
    virtual void accept(IRVisitor &visitor) {}
};

}