#pragma once

#include <algorithm>
#include <map>
#include <memory>
#include <set>
#include <string>
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
#include "../ir/IRImpl.h"
#include "../ir/IRLiteral.h"
#include "../ir/IRMem.h"
#include "../ir/IRParam.h"
#include "../ir/IRPhi.h"
#include "../ir/IRPHI.h"
#include "../ir/IRPrint.h"
#include "../ir/IRReturn.h"
#include "../ir/IRRoot.h"
#include "../ir/IRSext.h"
#include "../ir/IRStore.h"
#include "../ir/IRTrunc.h"
#include "../ir/IRValue.h"
#include "../ir/IRVar.h"
#include "../ir/IRZext.h"

namespace JaneZ {

class SROA {
public:
    void optimize(const std::shared_ptr<IRRoot> &root) {
        if (!root) return;
        for (auto &child : root->children) {
            if (auto func = std::dynamic_pointer_cast<IRFunction>(child)) {
                for (auto &nested : func->funcList) optimizeFunc(nested);
                optimizeFunc(func);
            } else if (auto impl = std::dynamic_pointer_cast<IRImpl>(child)) {
                for (auto &func : impl->functions) optimizeFunc(func);
            }
        }
    }

private:
    struct FieldInfo {
        int index = 0;
        std::shared_ptr<IRType> type;
        std::shared_ptr<IRVar> slot;
        bool w64tag = false;
        bool utag = false;
    };

    struct Candidate {
        std::shared_ptr<IRVar> root;
        std::shared_ptr<IRType> type;
        std::vector<FieldInfo> fields;
        bool escaped = false;
        bool zeroInit = false;
        std::set<IRVar*> initSources;
        std::set<IRVar*> copyPeers;
        std::set<int> writtenFields;
    };

    struct FieldAddress {
        IRVar *root = nullptr;
        int index = -1;
    };

    std::map<IRVar*, Candidate> candidates;
    std::map<IRVar*, FieldAddress> fieldAddress;
    std::set<IRVar*> approved;
    static constexpr int kMaxScalarizedFields = 4;

    void optimizeFunc(const std::shared_ptr<IRFunction> &func) {
        if (!func || !func->body) return;

        candidates.clear();
        fieldAddress.clear();
        approved.clear();

        collectCandidates(func);
        if (candidates.empty()) return;

        collectFieldAddresses(func);
        analyzeUses(func);
        chooseApproved();
        if (approved.empty()) return;

        transformFunction(func);
    }

    void collectCandidates(const std::shared_ptr<IRFunction> &func) {
        auto scan = [&](const std::shared_ptr<IRBlock> &blk) {
            if (!blk) return;
            for (auto &instr : blk->instrList) {
                auto alloca = std::dynamic_pointer_cast<IRAlloca>(instr);
                if (!alloca || !alloca->var || !alloca->allocatedType) continue;
                auto fields = directScalarFields(alloca->allocatedType);
                if (fields.empty()) continue;
                Candidate candidate;
                candidate.root = alloca->var;
                candidate.type = alloca->allocatedType;
                candidate.fields = std::move(fields);
                for (auto &field : candidate.fields) {
                    field.slot = makeSlot(candidate.root, field);
                }
                candidates[alloca->var.get()] = std::move(candidate);
            }
        };
        scan(func->body);
        for (auto &blk : func->body->blockList) scan(blk);
    }

    std::vector<FieldInfo> directScalarFields(const std::shared_ptr<IRType> &type) {
        std::vector<FieldInfo> fields;
        if (auto st = std::dynamic_pointer_cast<IRStructType>(type)) {
            if (st->memberTypes.empty() ||
                st->memberTypes.size() > kMaxScalarizedFields) return {};
            for (int i = 0; i < static_cast<int>(st->memberTypes.size()); i++) {
                if (!isScalarFieldType(st->memberTypes[i].second)) return {};
                fields.push_back(makeFieldInfo(i, st->memberTypes[i].second));
            }
        } else if (auto arr = std::dynamic_pointer_cast<IRArrayType>(type)) {
            if (arr->length <= 0 || arr->length > kMaxScalarizedFields) return {};
            if (!isScalarFieldType(arr->elementType)) return {};
            for (int i = 0; i < arr->length; i++) {
                fields.push_back(makeFieldInfo(i, arr->elementType));
            }
        }
        return fields;
    }

    bool isScalarFieldType(const std::shared_ptr<IRType> &type) const {
        return std::dynamic_pointer_cast<IRIntType>(type) != nullptr ||
               std::dynamic_pointer_cast<IRPtrType>(type) != nullptr;
    }

    FieldInfo makeFieldInfo(int index, const std::shared_ptr<IRType> &type) const {
        FieldInfo field;
        field.index = index;
        field.type = type;
        if (auto intType = std::dynamic_pointer_cast<IRIntType>(type)) {
            field.w64tag = intType->bitWidth == 64;
            field.utag = intType->isUnsigned;
        } else if (std::dynamic_pointer_cast<IRPtrType>(type)) {
            field.w64tag = true;
        }
        return field;
    }

    std::shared_ptr<IRVar> makeSlot(const std::shared_ptr<IRVar> &root,
                                    const FieldInfo &field) const {
        auto slot = std::make_shared<IRVar>();
        slot->type = field.type;
        if (root) {
            slot->varName = root->varName + "$sroa" + std::to_string(field.index);
            slot->reName = root->reName + "$sroa" + std::to_string(field.index);
        }
        if (field.w64tag) slot->isW64Stack = true;
        if (std::dynamic_pointer_cast<IRPtrType>(field.type)) slot->isPtrStorage = true;
        return slot;
    }

    void collectFieldAddresses(const std::shared_ptr<IRFunction> &func) {
        auto scan = [&](const std::shared_ptr<IRBlock> &blk) {
            if (!blk) return;
            for (auto &instr : blk->instrList) {
                auto getptr = std::dynamic_pointer_cast<IRGetptr>(instr);
                if (!getptr || !getptr->base || !getptr->res) continue;
                auto it = candidates.find(getptr->base.get());
                if (it == candidates.end()) continue;
                int index = getptrIndex(getptr);
                if (index < 0 || index >= static_cast<int>(it->second.fields.size())) {
                    it->second.escaped = true;
                    continue;
                }
                fieldAddress[getptr->res.get()] = FieldAddress{getptr->base.get(), index};
            }
        };
        scan(func->body);
        for (auto &blk : func->body->blockList) scan(blk);
    }

    int getptrIndex(const std::shared_ptr<IRGetptr> &getptr) const {
        if (!getptr || getptr->index) return -1;
        return getptr->offset >= 0 ? static_cast<int>(getptr->offset) : -1;
    }

    void analyzeUses(const std::shared_ptr<IRFunction> &func) {
        auto scan = [&](const std::shared_ptr<IRBlock> &blk) {
            if (!blk) return;
            for (auto &instr : blk->instrList) analyzeInstr(instr);
        };
        scan(func->body);
        for (auto &blk : func->body->blockList) scan(blk);
    }

    void analyzeInstr(const std::shared_ptr<IRNode> &instr) {
        if (!instr || std::dynamic_pointer_cast<IRAlloca>(instr)) return;

        if (auto getptr = std::dynamic_pointer_cast<IRGetptr>(instr)) {
            analyzeGetptr(getptr);
        } else if (auto load = std::dynamic_pointer_cast<IRLoad>(instr)) {
            analyzeLoad(load);
        } else if (auto store = std::dynamic_pointer_cast<IRStore>(instr)) {
            analyzeStore(store);
        } else if (auto memcpy = std::dynamic_pointer_cast<IRMemcpy>(instr)) {
            analyzeMemcpy(memcpy);
        } else if (auto memset = std::dynamic_pointer_cast<IRMemset>(instr)) {
            analyzeMemset(memset);
        } else if (auto op = std::dynamic_pointer_cast<IRBinaryop>(instr)) {
            markEscapingValue(op->leftValue);
            markEscapingValue(op->rightValue);
        } else if (auto br = std::dynamic_pointer_cast<IRBr>(instr)) {
            markEscapingVar(br->condition);
        } else if (auto ret = std::dynamic_pointer_cast<IRReturn>(instr)) {
            markEscapingVar(ret->returnValue);
        } else if (auto call = std::dynamic_pointer_cast<IRCall>(instr)) {
            analyzeCall(call);
        } else if (auto print = std::dynamic_pointer_cast<IRPrint>(instr)) {
            markEscapingValue(print->printVar);
        } else if (auto exit = std::dynamic_pointer_cast<IRExit>(instr)) {
            markEscapingValue(exit->exitCode);
        } else if (auto sext = std::dynamic_pointer_cast<IRSext>(instr)) {
            markEscapingVar(sext->value);
        } else if (auto zext = std::dynamic_pointer_cast<IRZext>(instr)) {
            markEscapingVar(zext->value);
        } else if (auto trunc = std::dynamic_pointer_cast<IRTrunc>(instr)) {
            markEscapingVar(trunc->value);
        } else if (auto phi = std::dynamic_pointer_cast<IRPhi>(instr)) {
            markEscapingVar(phi->secondState);
        } else if (auto phi = std::dynamic_pointer_cast<IRPHI>(instr)) {
            markEscapingValue(phi->firstState);
            markEscapingValue(phi->secondState);
            for (auto &entry : phi->entries) markEscapingValue(entry.first);
        }
    }

    void analyzeGetptr(const std::shared_ptr<IRGetptr> &getptr) {
        if (!getptr) return;
        auto rootIt = candidates.find(getptr->base.get());
        if (rootIt != candidates.end()) {
            int index = getptrIndex(getptr);
            if (index < 0 || index >= static_cast<int>(rootIt->second.fields.size())) {
                rootIt->second.escaped = true;
            }
            markEscapingVar(getptr->index);
            return;
        }
        markEscapingVar(getptr->base);
        markEscapingVar(getptr->index);
    }

    void analyzeLoad(const std::shared_ptr<IRLoad> &load) {
        if (!load) return;
        auto field = fieldAddress.find(load->addressVar.get());
        if (field != fieldAddress.end()) {
            if (!compatibleAccess(load->type, field->second)) {
                candidates[field->second.root].escaped = true;
            }
            return;
        }
        markEscapingVar(load->addressVar);
    }

    void analyzeStore(const std::shared_ptr<IRStore> &store) {
        if (!store) return;
        auto field = fieldAddress.find(store->address.get());
        if (field != fieldAddress.end()) {
            if (!compatibleAccess(store->valueType, field->second)) {
                candidates[field->second.root].escaped = true;
            } else {
                candidates[field->second.root].writtenFields.insert(field->second.index);
            }
        } else {
            markEscapingVar(store->address);
        }
        markEscapingVar(store->storeValue);
    }

    void analyzeMemcpy(const std::shared_ptr<IRMemcpy> &memcpy) {
        if (!memcpy) return;
        auto destRoot = rootCandidate(memcpy->dest);
        auto valueRoot = rootCandidate(memcpy->value);
        if (destRoot && valueRoot &&
            compatibleCandidates(destRoot, valueRoot)) {
            candidates[destRoot].initSources.insert(valueRoot);
            candidates[destRoot].copyPeers.insert(valueRoot);
            candidates[valueRoot].copyPeers.insert(destRoot);
            return;
        }
        if (destRoot) candidates[destRoot].escaped = true;
        else markEscapingVar(memcpy->dest);
        if (valueRoot) candidates[valueRoot].escaped = true;
        else markEscapingVar(memcpy->value);
    }

    void analyzeMemset(const std::shared_ptr<IRMemset> &memset) {
        if (!memset) return;
        auto destRoot = rootCandidate(memset->dest);
        if (destRoot && memset->value == 0) {
            candidates[destRoot].zeroInit = true;
            return;
        }
        if (destRoot) candidates[destRoot].escaped = true;
        else markEscapingVar(memset->dest);
    }

    void analyzeCall(const std::shared_ptr<IRCall> &call) {
        if (!call || !call->pList) return;
        for (auto &param : call->pList->paramList) {
            markEscapingNode(param);
        }
    }

    bool compatibleAccess(const std::shared_ptr<IRType> &type,
                          const FieldAddress &address) const {
        auto candIt = candidates.find(address.root);
        if (candIt == candidates.end()) return false;
        if (address.index < 0 || address.index >= static_cast<int>(candIt->second.fields.size())) {
            return false;
        }
        return sameTypeShape(type, candIt->second.fields[address.index].type);
    }

    bool compatibleCandidates(IRVar *lhs, IRVar *rhs) const {
        auto lhsIt = candidates.find(lhs);
        auto rhsIt = candidates.find(rhs);
        if (lhsIt == candidates.end() || rhsIt == candidates.end()) return false;
        if (lhsIt->second.fields.size() != rhsIt->second.fields.size()) return false;
        for (size_t i = 0; i < lhsIt->second.fields.size(); i++) {
            if (!sameTypeShape(lhsIt->second.fields[i].type,
                               rhsIt->second.fields[i].type)) {
                return false;
            }
        }
        return true;
    }

    bool sameTypeShape(const std::shared_ptr<IRType> &lhs,
                       const std::shared_ptr<IRType> &rhs) const {
        if (!lhs || !rhs || lhs->type != rhs->type) return false;
        if (auto li = std::dynamic_pointer_cast<IRIntType>(lhs)) {
            auto ri = std::dynamic_pointer_cast<IRIntType>(rhs);
            return ri && li->bitWidth == ri->bitWidth && li->isUnsigned == ri->isUnsigned;
        }
        if (auto lp = std::dynamic_pointer_cast<IRPtrType>(lhs)) {
            auto rp = std::dynamic_pointer_cast<IRPtrType>(rhs);
            return rp && sameTypeShape(lp->baseType, rp->baseType);
        }
        return lhs.get() == rhs.get();
    }

    IRVar *rootCandidate(const std::shared_ptr<IRVar> &var) const {
        if (!var) return nullptr;
        return candidates.count(var.get()) ? var.get() : nullptr;
    }

    void markEscapingNode(const std::shared_ptr<IRNode> &node) {
        markEscapingValue(std::dynamic_pointer_cast<IRValue>(node));
    }

    void markEscapingValue(const std::shared_ptr<IRValue> &value) {
        markEscapingVar(std::dynamic_pointer_cast<IRVar>(value));
    }

    void markEscapingVar(const std::shared_ptr<IRVar> &var) {
        if (!var) return;
        auto candIt = candidates.find(var.get());
        if (candIt != candidates.end()) {
            candIt->second.escaped = true;
            return;
        }
        auto addrIt = fieldAddress.find(var.get());
        if (addrIt != fieldAddress.end()) {
            candidates[addrIt->second.root].escaped = true;
        }
    }

    void chooseApproved() {
        std::set<IRVar*> visited;
        for (auto &[root, candidate] : candidates) {
            if (!visited.insert(root).second) continue;

            std::set<IRVar*> component;
            std::vector<IRVar*> stack{root};
            component.insert(root);
            while (!stack.empty()) {
                auto *cur = stack.back();
                stack.pop_back();
                for (auto *peer : candidates[cur].copyPeers) {
                    if (!peer || !candidates.count(peer)) continue;
                    if (component.insert(peer).second) {
                        visited.insert(peer);
                        stack.push_back(peer);
                    }
                }
            }

            if (componentApproved(component)) {
                approved.insert(component.begin(), component.end());
            }
        }
    }

    bool componentApproved(const std::set<IRVar*> &component) const {
        bool hasSeed = false;
        for (auto *root : component) {
            auto it = candidates.find(root);
            if (it == candidates.end() || it->second.escaped) return false;
            if (directlyInitialized(it->second)) hasSeed = true;
        }
        if (!hasSeed) return false;

        for (auto *root : component) {
            auto it = candidates.find(root);
            if (it == candidates.end()) return false;
            if (directlyInitialized(it->second)) continue;

            bool copiedFromComponent = false;
            for (auto *src : it->second.initSources) {
                if (component.count(src)) {
                    copiedFromComponent = true;
                    break;
                }
            }
            if (!copiedFromComponent) return false;
        }
        return true;
    }

    bool directlyInitialized(const Candidate &candidate) const {
        return candidate.zeroInit ||
               candidate.writtenFields.size() == candidate.fields.size();
    }

    void transformFunction(const std::shared_ptr<IRFunction> &func) {
        transformList(func->body->instrList);
        for (auto &blk : func->body->blockList) transformList(blk->instrList);
    }

    void transformList(std::vector<std::shared_ptr<IRNode>> &instrList) {
        std::vector<std::shared_ptr<IRNode>> out;
        for (auto &instr : instrList) {
            if (auto alloca = std::dynamic_pointer_cast<IRAlloca>(instr)) {
                if (isApprovedRoot(alloca->var)) {
                    appendScalarAllocas(alloca->var.get(), out);
                    continue;
                }
            }

            if (auto getptr = std::dynamic_pointer_cast<IRGetptr>(instr)) {
                if (approvedFieldAddress(getptr->res)) continue;
            }

            if (auto memcpy = std::dynamic_pointer_cast<IRMemcpy>(instr)) {
                auto destRoot = rootCandidate(memcpy->dest);
                auto valueRoot = rootCandidate(memcpy->value);
                if (isApprovedRoot(destRoot) && isApprovedRoot(valueRoot)) {
                    appendFieldCopy(valueRoot, destRoot, out);
                    continue;
                }
            }

            if (auto memset = std::dynamic_pointer_cast<IRMemset>(instr)) {
                auto destRoot = rootCandidate(memset->dest);
                if (isApprovedRoot(destRoot) && memset->value == 0) {
                    appendFieldZero(destRoot, out);
                    continue;
                }
            }

            rewriteScalarAddresses(instr);
            out.push_back(instr);
        }
        instrList = std::move(out);
    }

    bool isApprovedRoot(const std::shared_ptr<IRVar> &var) const {
        return var && approved.count(var.get());
    }

    bool isApprovedRoot(IRVar *var) const {
        return var && approved.count(var);
    }

    bool approvedFieldAddress(const std::shared_ptr<IRVar> &var) const {
        if (!var) return false;
        auto it = fieldAddress.find(var.get());
        return it != fieldAddress.end() && approved.count(it->second.root);
    }

    void appendScalarAllocas(IRVar *root, std::vector<std::shared_ptr<IRNode>> &out) {
        auto it = candidates.find(root);
        if (it == candidates.end()) return;
        for (auto &field : it->second.fields) {
            auto alloca = std::make_shared<IRAlloca>(field.type, field.slot);
            alloca->w64tag = field.w64tag;
            out.push_back(alloca);
        }
    }

    void appendFieldCopy(IRVar *srcRoot, IRVar *dstRoot,
                         std::vector<std::shared_ptr<IRNode>> &out) {
        if (!srcRoot || !dstRoot || srcRoot == dstRoot) return;
        auto &src = candidates[srcRoot];
        auto &dst = candidates[dstRoot];
        for (size_t i = 0; i < src.fields.size(); i++) {
            auto tmp = std::make_shared<IRVar>();
            tmp->type = src.fields[i].type;

            auto load = std::make_shared<IRLoad>(tmp, src.fields[i].slot, src.fields[i].type);
            load->w64tag = src.fields[i].w64tag;
            load->utag = src.fields[i].utag;
            out.push_back(load);

            auto store = std::make_shared<IRStore>();
            store->valueType = dst.fields[i].type;
            store->storeValue = tmp;
            store->address = dst.fields[i].slot;
            store->w64tag = dst.fields[i].w64tag;
            out.push_back(store);
        }
    }

    void appendFieldZero(IRVar *root, std::vector<std::shared_ptr<IRNode>> &out) {
        auto it = candidates.find(root);
        if (it == candidates.end()) return;
        for (auto &field : it->second.fields) {
            auto store = std::make_shared<IRStore>();
            store->valueType = field.type;
            store->storeLiteral = std::make_shared<IRLiteral>(INT_LITERAL, 0, false);
            store->address = field.slot;
            store->w64tag = field.w64tag;
            out.push_back(store);
        }
    }

    void rewriteScalarAddresses(const std::shared_ptr<IRNode> &instr) {
        if (auto load = std::dynamic_pointer_cast<IRLoad>(instr)) {
            rewriteAddress(load->addressVar);
        } else if (auto store = std::dynamic_pointer_cast<IRStore>(instr)) {
            rewriteAddress(store->address);
        }
    }

    void rewriteAddress(std::shared_ptr<IRVar> &address) {
        if (!address) return;
        auto it = fieldAddress.find(address.get());
        if (it == fieldAddress.end() || !approved.count(it->second.root)) return;
        auto candIt = candidates.find(it->second.root);
        if (candIt == candidates.end()) return;
        if (it->second.index < 0 ||
            it->second.index >= static_cast<int>(candIt->second.fields.size())) {
            return;
        }
        address = candIt->second.fields[it->second.index].slot;
    }
};

} // namespace JaneZ
