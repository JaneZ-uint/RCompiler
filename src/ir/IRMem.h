# pragma once

#include "IRNode.h"
#include "IRVar.h"
#include <memory>
namespace JaneZ {
class IRMemset : public IRNode {
public:
    std::shared_ptr<IRVar> dest;
    int size;
    int value = 0;

    IRMemset() = default;
    IRMemset(std::shared_ptr<IRVar> dest, int size) : dest(dest), size(size) {}
    ~IRMemset() = default;
    void accept(IRVisitor &visitor) override {
        visitor.visit(*this);
    }
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