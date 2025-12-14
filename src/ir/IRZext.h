# pragma once
# include "IRNode.h"
# include "IRType.h"
# include "IRVisitor.h"
# include "IRVar.h"

namespace JaneZ {
class IRZext : public IRNode {
public:
    std::shared_ptr<IRType> originalType;
    std::shared_ptr<IRVar> value;
    std::shared_ptr<IRType> targetType;
    std::shared_ptr<IRVar> result;

    IRZext(std::shared_ptr<IRType> originalType,
            std::shared_ptr<IRVar> value,
            std::shared_ptr<IRType> targetType,
            std::shared_ptr<IRVar> result)
        : originalType(std::move(originalType)), value(std::move(value)), targetType(std::move(targetType)), result(std::move(result)) {}
    ~IRZext() = default;
    void accept(IRVisitor &visitor) override {
        visitor.visit(*this);
    }
    
};
}
