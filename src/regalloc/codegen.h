# pragma once
# include "../ir/IRRoot.h"
# include "InstrSelect.h"
# include "LinearScan.h"
# include "ASMPrinter.h"
#include <memory>

namespace JaneZ {
class codegen{
public:
    void generate(std::shared_ptr<IRRoot> root){
        InstrSelect selector;
        selector.select(root);
        LinearScan allocator;
        allocator.run(selector.asmBlocks);
        ASMPrinter printer(selector.asmBlocks);
        printer.print();
    }
};
}
