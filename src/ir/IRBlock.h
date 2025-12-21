# pragma once
# include "IRNode.h"
# include "IRVisitor.h"
# include <vector>
#include <memory>

extern long long int ir_cnt;

namespace JaneZ {
class IRReturn;
class IRBr;
class IRBlock : public IRNode {
public:
    std::vector<std::shared_ptr<IRNode>> instrList;
    std::vector<std::shared_ptr<IRBlock>> blockList;
    long long int label;

    IRBlock() {
        label = ir_cnt++;
    }
    IRBlock(std::vector<std::shared_ptr<IRNode>> instrList)
        : instrList(std::move(instrList)){
            label = ir_cnt++;
    }
    ~IRBlock() = default;
    void accept(IRVisitor &visitor) override {
        visitor.visit(*this);
    }
};

}