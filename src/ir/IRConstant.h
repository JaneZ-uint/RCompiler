# pragma once
# include "IRNode.h"
# include "IRVisitor.h"

namespace JaneZ {
class IRGlobal : public IRNode {
public:
    IRGlobal() : IRNode() {}
    virtual ~IRGlobal() = default;
    void accept(IRVisitor &visitor) override {
        visitor.visit(*this);   
    }
};

}