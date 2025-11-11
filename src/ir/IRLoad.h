# pragma once
# include "IRNode.h"
# include "IRVisitor.h"

namespace JaneZ {
class IRLoad : public IRNode {
public:
    IRLoad() : IRNode() {}
    virtual ~IRLoad() = default;
    void accept(IRVisitor &visitor) override {
        visitor.visit(*this);   
    }
};

}