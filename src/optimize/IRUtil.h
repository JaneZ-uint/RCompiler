#pragma once

#include <functional>
#include <memory>
#include <vector>
#include "../ir/IRAlloca.h"
#include "../ir/IRBinaryop.h"
#include "../ir/IRBlock.h"
#include "../ir/IRBr.h"
#include "../ir/IRCall.h"
#include "../ir/IRExit.h"
#include "../ir/IRFunction.h"
#include "../ir/IRGetint.h"
#include "../ir/IRGetptr.h"
#include "../ir/IRLoad.h"
#include "../ir/IRMem.h"
#include "../ir/IRParam.h"
#include "../ir/IRPhi.h"
#include "../ir/IRPHI.h"
#include "../ir/IRPrint.h"
#include "../ir/IRReturn.h"
#include "../ir/IRSext.h"
#include "../ir/IRStore.h"
#include "../ir/IRTrunc.h"
#include "../ir/IRValue.h"
#include "../ir/IRVar.h"
#include "../ir/IRZext.h"

namespace JaneZ::IRUtil {

inline void forEachInstruction(const std::shared_ptr<IRFunction> &func,
                               const std::function<void(const std::shared_ptr<IRNode>&)> &fn) {
    if (!func || !func->body) return;
    for (auto &instr : func->body->instrList) fn(instr);
    for (auto &blk : func->body->blockList) {
        if (!blk) continue;
        for (auto &instr : blk->instrList) fn(instr);
    }
}

inline std::vector<std::shared_ptr<IRVar>> defs(const std::shared_ptr<IRNode> &instr) {
    std::vector<std::shared_ptr<IRVar>> out;
    auto add = [&](const std::shared_ptr<IRVar> &var) {
        if (var) out.push_back(var);
    };

    if (auto p = std::dynamic_pointer_cast<IRAlloca>(instr)) add(p->var);
    else if (auto p = std::dynamic_pointer_cast<IRBinaryop>(instr)) add(p->result);
    else if (auto p = std::dynamic_pointer_cast<IRLoad>(instr)) add(p->tmp);
    else if (auto p = std::dynamic_pointer_cast<IRGetptr>(instr)) add(p->res);
    else if (auto p = std::dynamic_pointer_cast<IRCall>(instr)) add(p->retVar);
    else if (auto p = std::dynamic_pointer_cast<IRGetint>(instr)) add(p->result);
    else if (auto p = std::dynamic_pointer_cast<IRSext>(instr)) add(p->result);
    else if (auto p = std::dynamic_pointer_cast<IRZext>(instr)) add(p->result);
    else if (auto p = std::dynamic_pointer_cast<IRTrunc>(instr)) add(p->result);
    else if (auto p = std::dynamic_pointer_cast<IRPhi>(instr)) add(p->result);
    else if (auto p = std::dynamic_pointer_cast<IRPHI>(instr)) add(p->result);

    return out;
}

inline void addValueUse(const std::shared_ptr<IRValue> &value,
                        std::vector<std::shared_ptr<IRVar>> &out) {
    if (auto var = std::dynamic_pointer_cast<IRVar>(value)) out.push_back(var);
}

inline void addNodeUse(const std::shared_ptr<IRNode> &node,
                       std::vector<std::shared_ptr<IRVar>> &out) {
    if (auto value = std::dynamic_pointer_cast<IRValue>(node)) addValueUse(value, out);
}

inline std::vector<std::shared_ptr<IRVar>> uses(const std::shared_ptr<IRNode> &instr) {
    std::vector<std::shared_ptr<IRVar>> out;
    auto add = [&](const std::shared_ptr<IRVar> &var) {
        if (var) out.push_back(var);
    };

    if (auto p = std::dynamic_pointer_cast<IRStore>(instr)) {
        add(p->storeValue);
        add(p->address);
    } else if (auto p = std::dynamic_pointer_cast<IRLoad>(instr)) {
        add(p->addressVar);
    } else if (auto p = std::dynamic_pointer_cast<IRGetptr>(instr)) {
        add(p->base);
        add(p->index);
    } else if (auto p = std::dynamic_pointer_cast<IRBinaryop>(instr)) {
        addValueUse(p->leftValue, out);
        addValueUse(p->rightValue, out);
    } else if (auto p = std::dynamic_pointer_cast<IRBr>(instr)) {
        add(p->condition);
    } else if (auto p = std::dynamic_pointer_cast<IRReturn>(instr)) {
        add(p->returnValue);
    } else if (auto p = std::dynamic_pointer_cast<IRCall>(instr)) {
        if (p->pList) {
            for (auto &param : p->pList->paramList) addNodeUse(param, out);
        }
    } else if (auto p = std::dynamic_pointer_cast<IRPrint>(instr)) {
        addValueUse(p->printVar, out);
    } else if (auto p = std::dynamic_pointer_cast<IRSext>(instr)) {
        add(p->value);
    } else if (auto p = std::dynamic_pointer_cast<IRZext>(instr)) {
        add(p->value);
    } else if (auto p = std::dynamic_pointer_cast<IRTrunc>(instr)) {
        add(p->value);
    } else if (auto p = std::dynamic_pointer_cast<IRPhi>(instr)) {
        add(p->secondState);
    } else if (auto p = std::dynamic_pointer_cast<IRPHI>(instr)) {
        addValueUse(p->firstState, out);
        addValueUse(p->secondState, out);
        for (auto &entry : p->entries) addValueUse(entry.first, out);
    } else if (auto p = std::dynamic_pointer_cast<IRMemcpy>(instr)) {
        add(p->dest);
        add(p->value);
    } else if (auto p = std::dynamic_pointer_cast<IRMemset>(instr)) {
        add(p->dest);
    } else if (auto p = std::dynamic_pointer_cast<IRExit>(instr)) {
        addValueUse(p->exitCode, out);
    }

    return out;
}

inline bool hasSideEffect(const std::shared_ptr<IRNode> &instr) {
    return std::dynamic_pointer_cast<IRStore>(instr) ||
           std::dynamic_pointer_cast<IRCall>(instr) ||
           std::dynamic_pointer_cast<IRGetint>(instr) ||
           std::dynamic_pointer_cast<IRPrint>(instr) ||
           std::dynamic_pointer_cast<IRExit>(instr) ||
           std::dynamic_pointer_cast<IRReturn>(instr) ||
           std::dynamic_pointer_cast<IRBr>(instr) ||
           std::dynamic_pointer_cast<IRMemcpy>(instr) ||
           std::dynamic_pointer_cast<IRMemset>(instr);
}

inline bool isPureRemovable(const std::shared_ptr<IRNode> &instr) {
    return !hasSideEffect(instr) && !defs(instr).empty();
}

} // namespace JaneZ::IRUtil
