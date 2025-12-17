# pragma once
# include "IRNode.h"
# include "IRType.h"
# include "IRVisitor.h"
# include "IRVar.h"
#include <memory>

namespace JaneZ {
class IRTrunc : public IRNode {
public:
    std::shared_ptr<IRType> originalType;
    std::shared_ptr<IRVar> value;
    std::shared_ptr<IRType> targetType;
    std::shared_ptr<IRVar> result;
    
    IRTrunc() = default;
    IRTrunc(std::shared_ptr<IRType> oT,
            std::shared_ptr<IRVar> val,
            std::shared_ptr<IRType> tT, std::shared_ptr<IRVar> res)
        : originalType(std::move(oT)), value(std::move(val)), targetType(std::move(tT)), result(std::move(res)) {}
    ~IRTrunc() = default;
    void accept(IRVisitor &visitor) override {
        visitor.visit(*this);
    }

};
}