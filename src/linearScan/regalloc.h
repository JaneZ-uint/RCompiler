# pragma once
# include "../ir/IRRoot.h"
# include "InstrSelect.h"
# include "LinearScan.h"
# include "ASMPrinter.h"
#include <memory>
#include <fstream>

namespace JaneZ {
class regalloc {
public:
    void generate(std::shared_ptr<IRRoot> root) {
        InstrSelect selector;
        selector.select(root);
        LinearScan allocator;
        allocator.process(selector.asmBlocks);
        ASMPrinter printer(selector.asmBlocks);
        printer.print();
    }
};
} // namespace JaneZ
