# pragma once
# include "IRNode.h"

namespace JaneZ {
class IRValue : public IRNode {
public:
    IRValue() = default;

    virtual ~IRValue() {}

    virtual void accept(IRVisitor &visitor) = 0;
};
}