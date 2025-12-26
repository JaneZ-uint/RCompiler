# pragma once
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
    std::shared_ptr<IRType> type;
    std::vector<std::shared_ptr<IRValue>> valueTable;
    std::vector<std::shared_ptr<IRBlock>> blockTable;

    IRPhi() = default;
    ~IRPhi() = default;
    void accept(IRVisitor &visitor) override {
        visitor.visit(*this);
    }
};

}