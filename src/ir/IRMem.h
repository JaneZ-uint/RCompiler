# pragma once

#include "IRNode.h"
#include "IRVar.h"
#include <memory>
namespace JaneZ {
class IRMemset : public IRNode {
public:
    
};

class IRMemcpy: public IRNode {
public:
    std::shared_ptr<IRVar> dest;
    std::shared_ptr<IRVar> value;
    int size;

    IRMemcpy() = default;
    IRMemcpy(std::shared_ptr<IRVar> dest, std::shared_ptr<IRVar> value, int size)
        : dest(dest), value(value), size(size) {}
    ~IRMemcpy() = default;
    void accept(IRVisitor &visitor) override {
        visitor.visit(*this);
    }
};
}