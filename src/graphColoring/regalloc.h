#pragma once

#include "../ir/IRRoot.h"
#include "../linearScan/ASMPrinter.h"
#include "../linearScan/InstrSelect.h"
#include "../linearScan/Peephole.h"
#include "GraphColoring.h"
#include <memory>

namespace JaneZ {
class graphColoringRegalloc {
public:
    void generate(std::shared_ptr<IRRoot> root) {
        InstrSelect selector;
        selector.select(root);
        Peephole peephole;
        peephole.optimize(selector.asmBlocks);
        GraphColoring allocator;
        allocator.deadCodeElimination(selector.asmBlocks);
        allocator.process(selector.asmBlocks);
        peephole.optimize(selector.asmBlocks, true);
        ASMPrinter printer(selector.asmBlocks);
        printer.print();
    }
};
} // namespace JaneZ
