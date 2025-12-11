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
    int label;

    IRBlock() = default;
    IRBlock(std::vector<std::shared_ptr<IRNode>> instrList,
            std::shared_ptr<IRReturn> retInstr,
            std::shared_ptr<IRBr> brInstr,
            int label)
        : instrList(std::move(instrList)),
          retInstr(std::move(retInstr)),
          brInstr(std::move(brInstr)),
          label(label) {}
    ~IRBlock() = default;
    void accept(IRVisitor &visitor) override {
        visitor.visit(*this);
    }
};

}