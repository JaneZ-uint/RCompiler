# pragma once
# include "../ir/IRRoot.h"
# include "InstrSelect.h"
# include "LinearScan.h"
# include "ASMPrinter.h"
#include <memory>

namespace JaneZ {
class regalloc {
public:
    void generate(std::shared_ptr<IRRoot> root) {
        // Phase 1: Instruction selection with virtual registers
        InstrSelect selector;
        selector.select(root);

        // DEBUG: dump pre-allocation assembly to file
        {
            auto origBuf = std::cout.rdbuf();
            std::ofstream preOut("/tmp/pre_alloc.s");
            std::cout.rdbuf(preOut.rdbuf());
            ASMPrinter prePrinter(selector.asmBlocks);
            prePrinter.print();
            std::cout.rdbuf(origBuf);
        }

        // Phase 2: Linear scan register allocation
        LinearScan allocator;
        allocator.process(selector.asmBlocks);

        // Phase 3: Print assembly
        ASMPrinter printer(selector.asmBlocks);
        printer.print();
    }
};
} // namespace JaneZ
