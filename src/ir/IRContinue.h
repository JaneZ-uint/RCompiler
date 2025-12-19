# pragma once

#include "IRNode.h"
namespace JaneZ {
class IRContinue : public IRNode {
public:
    IRContinue() = default;
    ~IRContinue() = default;
    void accept(IRVisitor &visitor) override {
        visitor.visit(*this);
    }
};

}