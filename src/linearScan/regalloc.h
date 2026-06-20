# pragma once
# include "../ir/IRRoot.h"
# include "InstrSelect.h"
# include "LinearScan.h"
# include "Peephole.h"
# include "ASMPrinter.h"
#include <memory>
#include <fstream>

namespace JaneZ {
class regalloc {
public:
    void generate(std::shared_ptr<IRRoot> root) {
        InstrSelect selector;
        selector.select(root);
        Peephole peephole;
        peephole.optimize(selector.asmBlocks);
        LinearScan allocator;
        allocator.deadCodeElimination(selector.asmBlocks);
        allocator.process(selector.asmBlocks);
        peephole.optimize(selector.asmBlocks, true);
        ASMPrinter printer(selector.asmBlocks);
        printer.print();
    }
};
} // namespace JaneZ
