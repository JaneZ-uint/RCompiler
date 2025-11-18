# pragma once
# include "IRNode.h"
# include "IRVisitor.h"
# include <vector>
#include <memory>

namespace JaneZ {
class IRReturn;
class IRBr;
class IRBlock : public IRNode {
public:
    std::vector<std::shared_ptr<IRNode>> instrList;
    std::shared_ptr<IRReturn> retInstr;
    std::shared_ptr<IRBr> brInstr;

    IRBlock(std::vector<std::shared_ptr<IRNode>> il,
            std::shared_ptr<IRReturn> ri,
            std::shared_ptr<IRBr> bi)
        : instrList(std::move(il)), retInstr(std::move(ri)), brInstr(std::move(bi)) {}
    ~IRBlock() = default;
    void accept(IRVisitor &visitor) override {
        visitor.visit(*this);
    }
};

}