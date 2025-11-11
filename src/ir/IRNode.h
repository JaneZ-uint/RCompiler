# pragma once
# include "IRVisitor.h"

namespace JaneZ{
class IRNode {
public:
    IRNode() = default;
    virtual ~IRNode() = default;
    virtual void accept(IRVisitor &visitor) = 0;
};

}