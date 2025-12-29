# pragma once
#include "../ast/astvisitor.h"
#include "../ast/root.h"
#include "../ast/Expression/ExprConstBlock.h"
#include "../ast/Expression/ExprStruct.h"
#include "../ast/Expression/expression.h"
#include "../ast/Expression/ExprArray.h"
#include "../ast/Expression/ExprBlock.h"
#include "../ast/Expression/ExprBreak.h"
#include "../ast/Expression/ExprCall.h"
#include "../ast/Expression/ExprContinue.h"
#include "../ast/Expression/ExprField.h"
#include "../ast/Expression/ExprGroup.h"
#include "../ast/Expression/ExprIf.h"
#include "../ast/Expression/ExprIndex.h"
#include "../ast/Expression/ExprLiteral.h"
#include "../ast/Expression/ExprLoop.h"
#include "../ast/Expression/ExprMatch.h"
#include "../ast/Expression/ExprMethodcall.h"
#include "../ast/Expression/ExprOpbinary.h"
#include "../ast/Expression/ExprOpunary.h"
#include "../ast/Expression/ExprPath.h"
#include "../ast/Expression/ExprReturn.h"
#include "../ast/Expression/ExprUnderscore.h"
#include "../ast/Item/ItemConst.h"
#include "../ast/Item/ItemEnum.h"
#include "../ast/Item/ItemFn.h"
#include "../ast/Item/ItemImpl.h"
#include "../ast/Item/ItemStruct.h"
#include "../ast/Item/ItemTrait.h"
#include "../ast/Pattern/PatternIdentifier.h"
#include "../ast/Pattern/PatternLiteral.h"
#include "../ast/Pattern/PatternPath.h"
#include "../ast/Pattern/PatternReference.h"
#include "../ast/Pattern/PatternWildcard.h"
#include "../ast/Statement/StmtEmpty.h"
#include "../ast/Statement/StmtExpr.h"
#include "../ast/Statement/StmtItem.h"
#include "../ast/Statement/StmtLet.h"
#include "../ast/Type/type.h"
#include "../ast/Type/TypeArray.h"
#include "../ast/Type/TypePath.h"
#include "../ast/Type/TypeReference.h"
#include "../ast/Type/TypeUnit.h"
#include "IRAlloca.h"
#include "IRFunction.h"
#include "IRImpl.h"
#include "IRLiteral.h"
#include "IRNode.h"
#include "IRPHI.h"
#include "IRParam.h"
#include "IRRoot.h"
#include "IRStore.h"
#include "IRType.h"
#include "IRScope.h"
#include "IRLoad.h"
#include "IRCall.h"
#include "IRBinaryop.h"
#include "IRTrunc.h"
#include "IRBlock.h"
#include "IRBr.h"
#include "IRSext.h"
#include "IRZext.h"
#include "IRGetptr.h"
#include "IRReturn.h"
#include "IRExit.h"
#include "IRBreak.h"
#include "IRContinue.h"
#include "IRPrint.h"
#include "IRGlobalbuilder.h"
#include "IRGetint.h"
#include "IRMem.h"
#include "IRPhi.h"
#include <cstddef>
#include <memory>
#include <map>
#include <string>
#include <vector>

namespace JaneZ {
class IR;
class IRVar;
class IRBuilder {
public:
    std::map<std::string, int> vars_cnt;
    std::map<std::string, int> types_cnt;
    std::map<std::string, int> funcs_cnt;
    std::map<std::string, int> constant_cnt;

    int label_cnt = 0;
    
    std::shared_ptr<IRScope> currentScope;

    std::shared_ptr<IRRoot> irRoot;

    IRGlobalBuilder globalBuilder;

    IRBuilder() = default;

    ~IRBuilder() = default;

    //AST 
    void visit(ASTNode &node){
        if(auto *p = dynamic_cast<ASTRootNode *>(& node)){
            visit(*p);
        }else{
            throw std::runtime_error("IRBuilder visit ASTNode error");
        }
    }

    std::shared_ptr<IRRoot> visit(ASTRootNode &node){
        globalBuilder.visit(node);
        for(auto &varElem: globalBuilder.globalScope->value_table){
            vars_cnt[varElem.first] = 1;
        }
        for(auto &typeElem: globalBuilder.globalScope->type_table){
            types_cnt[typeElem.first] = 1;
        }
        for(auto &funcElem: globalBuilder.globalScope->function_table){
            funcs_cnt[funcElem.first] = 1;
        }
        for(auto &constElem: globalBuilder.globalScope->constant_table){
            constant_cnt[constElem.first] = 1;
        }
        currentScope = globalBuilder.globalScope;
        irRoot = std::make_shared<IRRoot>();
        for(auto & item : node.child){
            //auto 
            auto irItem = visit(*item);
            if(irItem){
                irRoot->children.push_back(irItem);
            }
        }
        return irRoot;
    }

    //Expression
    //现在考虑在visit expr结点时在函数参数列表里添加一个当前函数/当前函数返回值的指针
    std::shared_ptr<IRBlock> visit(Expression &node){
        std::shared_ptr<IRBlock> ret = nullptr;
        if(auto *p = dynamic_cast<ExprArray *>(& node)) {
            ret = visit(*p);
            node.ret = p->ret;
        }else if(auto *p = dynamic_cast<ExprBlock *>(& node)) {
            ret = visit(*p);
            node.ret = p->ret;
        }else if(auto *p = dynamic_cast<ExprBreak *>(& node)) {
            ret = visit(*p);
            node.ret = p->ret;
        }else if(auto *p = dynamic_cast<ExprCall *>(& node)) {
            ret = visit(*p);
            node.ret = p->ret;
        }else if(auto *p = dynamic_cast<ExprConstBlock *>(& node)) {
            ret = visit(*p);
            node.ret = p->ret;
        }else if(auto *p = dynamic_cast<ExprContinue *>(& node)) {
            ret = visit(*p);
            node.ret = p->ret;
        }else if(auto *p = dynamic_cast<ExprField *>(& node)) {
            ret = visit(*p);
            node.ret = p->ret;
        }else if(auto *p = dynamic_cast<ExprGroup *>(& node)) {
            ret = visit(*p);
            node.ret = p->ret;
        }else if(auto *p = dynamic_cast<ExprIf *>(& node)) {
            ret = visit(*p);
            node.ret = p->ret;
        }else if(auto *p = dynamic_cast<ExprIndex *>(& node)) {
            ret = visit(*p);
            node.ret = p->ret;
        }else if(auto *p = dynamic_cast<ExprLiteral *>(& node)) {
            ret = visit(*p);
            node.ret = p->ret;
        }else if(auto *p = dynamic_cast<ExprLoop *>(& node)) {
            ret = visit(*p);
            node.ret = p->ret;
        }else if(auto *p = dynamic_cast<ExprMatch *>(& node)) {
            ret = visit(*p);
            node.ret = p->ret;
        }else if(auto *p = dynamic_cast<ExprMethodcall *>(& node)) {
            ret = visit(*p);
            node.ret = p->ret;
        }else if(auto *p = dynamic_cast<ExprOpbinary *>(& node)) {
            ret = visit(*p);
            node.ret = p->ret;
        }else if(auto *p = dynamic_cast<ExprOpunary *>(& node)) {
            ret = visit(*p);
            node.ret = p->ret;
        }else if(auto *p = dynamic_cast<ExprPath *>(& node)) {
            ret = visit(*p);
            node.ret = p->ret;
        }else if(auto *p = dynamic_cast<ExprReturn *>(& node)) {
            ret = visit(*p);
            node.ret = p->ret;
        }else if(auto *p = dynamic_cast<ExprStruct *>(& node)) {
            ret = visit(*p);
            node.ret = p->ret;
        }else if(auto *p = dynamic_cast<ExprUnderscore *>(& node)) {
            ret = visit(*p);
            node.ret = p->ret;
        }else{
            throw std::runtime_error("IRBuilder visit Expression error");
        }
        if (node.ret != nullptr && node.is_lvalue == false) {
            if(auto var = std::dynamic_pointer_cast<IRVar>(node.ret)){
                if(auto *inttype = dynamic_cast<IRIntType *>(& *var->type)){
                    auto loadInstr = std::make_shared<IRLoad>();
                    auto tmpVar = std::make_shared<IRVar>();
                    tmpVar->type = var->type;
                    loadInstr->tmp = tmpVar;
                    loadInstr->addressVar = var;
                    loadInstr->type = var->type;
                    if(ret->blockList.empty()){
                        ret->instrList.push_back(loadInstr);
                    }else{
                        auto lastBlock = ret->blockList[ret->blockList.size() - 1];
                        lastBlock->instrList.push_back(loadInstr);
                    }
                    node.ret = tmpVar;
                }else{
                    auto memcpyInstr = std::make_shared<IRMemcpy>();
                    auto tmpVar = std::make_shared<IRVar>();
                    tmpVar->type = var->type;
                    memcpyInstr->dest = tmpVar;
                    memcpyInstr->value = var;
                    memcpyInstr->size = var->type->size;
                    if(ret->blockList.empty()){
                        ret->instrList.push_back(std::make_shared<IRAlloca>(tmpVar->type,tmpVar));
                        ret->instrList.push_back(memcpyInstr);
                    }else{
                        auto lastBlock = ret->blockList[ret->blockList.size() - 1];
                        lastBlock->instrList.push_back(std::make_shared<IRAlloca>(tmpVar->type,tmpVar));
                        lastBlock->instrList.push_back(memcpyInstr);
                    }
                    node.ret = tmpVar;
                }
            }
        }
        return ret;
    }
    std::shared_ptr<IRBlock> visit(ExprArray &node){
        std::shared_ptr<IRBlock> block = std::make_shared<IRBlock>();
        int size = 0;
        if(node.arrayExpr.size() == 0){
            auto arrayVar = std::make_shared<IRVar>();
            auto visitInstr = visit(*node.type);
            auto sizeInstr = visit(*node.size);
            if(visitInstr){
                for(auto & instr : visitInstr->instrList){
                    block->instrList.push_back(instr);
                }
                if(visitInstr->blockList.size() > 0){
                    for(auto & b : visitInstr->blockList){
                        block->blockList.push_back(b);
                    }
                }
            }
            if(sizeInstr){
                if(block->blockList.empty()){
                    for(auto & instr : sizeInstr->instrList){
                        block->instrList.push_back(instr);
                    }
                    if(sizeInstr->blockList.size() > 0){
                        for(auto & b : sizeInstr->blockList){
                            block->blockList.push_back(b);
                        }
                    }
                }else{
                    auto lastBlock = block->blockList[block->blockList.size() - 1];
                    for(auto & instr : sizeInstr->instrList){
                        lastBlock->instrList.push_back(instr);
                    }
                    if(sizeInstr->blockList.size() > 0){
                        for(auto & b : sizeInstr->blockList){
                            block->blockList.push_back(b);
                        }
                    }
                }
            }
            if(auto *sizeLiteral = dynamic_cast<IRLiteral *>(& *node.size->ret)){
                size = sizeLiteral->intValue;
            }
            auto condBlock = std::make_shared<IRBlock>();
            auto cnt = std::make_shared<IRVar>();
            if(block->blockList.empty()){
                block->instrList.push_back(std::make_shared<IRAlloca>(currentScope->lookupTypeSymbol("i32"),cnt));
                block->instrList.push_back(std::make_shared<IRStore>(currentScope->lookupTypeSymbol("i32"), nullptr,std::make_shared<IRLiteral>(INT_LITERAL,0),cnt));
                block->instrList.push_back(std::make_shared<IRBr>(condBlock));
            }else{
                auto lastBlock = block->blockList[block->blockList.size() - 1];
                lastBlock->instrList.push_back(std::make_shared<IRAlloca>(currentScope->lookupTypeSymbol("i32"),cnt));
                lastBlock->instrList.push_back(std::make_shared<IRStore>(currentScope->lookupTypeSymbol("i32"), nullptr,std::make_shared<IRLiteral>(INT_LITERAL,0),cnt));
                lastBlock->instrList.push_back(std::make_shared<IRBr>(condBlock));
            }
            auto loadvar = std::make_shared<IRVar>();
            loadvar->type = currentScope->lookupTypeSymbol("i32");
            condBlock->instrList.push_back(std::make_shared<IRLoad>(loadvar, cnt,currentScope->lookupTypeSymbol("i32")));
            auto cmpVar = std::make_shared<IRVar>();
            cmpVar->type = currentScope->lookupTypeSymbol("i1");
            auto ltInstr = std::make_shared<IRBinaryop>();
            ltInstr->leftValue = loadvar;
            ltInstr->rightValue = std::make_shared<IRLiteral>(INT_LITERAL,size);
            ltInstr->op = LT;
            ltInstr->result = cmpVar;
            condBlock->instrList.push_back(ltInstr);
            auto assignBlock = std::make_shared<IRBlock>();
            auto retBlock = std::make_shared<IRBlock>();
            condBlock->instrList.push_back(std::make_shared<IRBr>(cmpVar,assignBlock,retBlock));
            auto index = std::make_shared<IRVar>();
            index->type = currentScope->lookupTypeSymbol("i32");
            assignBlock->instrList.push_back(std::make_shared<IRLoad>(index, cnt,currentScope->lookupTypeSymbol("i32")));
            auto getptrInstr = std::make_shared<IRGetptr>();
            getptrInstr->index = index;
            getptrInstr->offset = -1;
            getptrInstr->base = arrayVar;
            auto resVar = std::make_shared<IRVar>();
            if(auto *literal = dynamic_cast<IRLiteral *>(& *node.type->ret)){
                int init;
                if(literal->literalType == BOOL_LITERAL){
                    arrayVar->type = std::make_shared<IRArrayType>(currentScope->lookupTypeSymbol("bool"), size);
                    if(auto arraytp = std::dynamic_pointer_cast<IRArrayType>(arrayVar->type)){
                        caculateArraySize(arraytp);
                    }
                    if(literal->intValue != 0){
                        init = 1;
                    }else{
                        init = 0;
                    }
                    resVar->type = currentScope->lookupTypeSymbol("bool");
                }else if(literal->literalType == INT_LITERAL){
                    arrayVar->type = std::make_shared<IRArrayType>(currentScope->lookupTypeSymbol("i32"), size);
                    if(auto arraytp = std::dynamic_pointer_cast<IRArrayType>(arrayVar->type)){
                        caculateArraySize(arraytp);
                    }
                    init = literal->intValue;
                    resVar->type = currentScope->lookupTypeSymbol("i32");
                }
                block->instrList.push_back(std::make_shared<IRAlloca>(arrayVar->type,arrayVar)); 
                //resVar->type = currentScope->lookupTypeSymbol("i32");
                getptrInstr->res = resVar;
                getptrInstr->type = arrayVar->type;
                assignBlock->instrList.push_back(getptrInstr);
                auto storeInstr = std::make_shared<IRStore>();
                storeInstr->valueType = resVar->type;
                storeInstr->address = getptrInstr->res;
                storeInstr->storeLiteral = std::make_shared<IRLiteral>(INT_LITERAL, init);
                assignBlock->instrList.push_back(storeInstr);
            }else if(auto var = std::dynamic_pointer_cast<IRVar>(node.type->ret)){
                arrayVar->type = std::make_shared<IRArrayType>(var->type, size);
                if(auto arraytp = std::dynamic_pointer_cast<IRArrayType>(arrayVar->type)){
                    caculateArraySize(arraytp);
                }
                resVar->type = var->type;
                getptrInstr->res = resVar;
                getptrInstr->type = arrayVar->type;
                assignBlock->instrList.push_back(getptrInstr);
                block->instrList.push_back(std::make_shared<IRAlloca>(arrayVar->type,arrayVar));
                auto memcpyInstr = std::make_shared<IRMemcpy>();
                memcpyInstr->dest = getptrInstr->res;
                memcpyInstr->value = var;
                memcpyInstr->size = var->type->size;
                assignBlock->instrList.push_back(memcpyInstr);
            }
            auto loadcnt = std::make_shared<IRVar>();
            loadcnt->type = currentScope->lookupTypeSymbol("i32");
            auto loadcntInstr = std::make_shared<IRLoad>();
            loadcntInstr->tmp = loadcnt;
            loadcntInstr->addressVar = cnt;
            loadcntInstr->type = currentScope->lookupTypeSymbol("i32");
            assignBlock->instrList.push_back(loadcntInstr);
            auto addInstr = std::make_shared<IRBinaryop>();
            auto oneLiteral = std::make_shared<IRLiteral>(INT_LITERAL, 1);
            addInstr->leftValue = loadcnt;
            addInstr->rightValue = oneLiteral;
            auto addRes = std::make_shared<IRVar>();
            addRes->type = currentScope->lookupTypeSymbol("i32");
            addInstr->result = addRes;
            addInstr->op = ADD;
            assignBlock->instrList.push_back(addInstr);
            auto storecntInstr = std::make_shared<IRStore>();
            storecntInstr->valueType = currentScope->lookupTypeSymbol("i32");
            storecntInstr->storeValue = addRes;
            storecntInstr->address = cnt;
            assignBlock->instrList.push_back(storecntInstr);
            assignBlock->instrList.push_back(std::make_shared<IRBr>(condBlock));
            block->blockList.push_back(condBlock);
            block->blockList.push_back(assignBlock);
            block->blockList.push_back(retBlock);
            node.ret = arrayVar;
        } else {
            int size = node.arrayExpr.size();
            std::vector<int> assignList;
            auto arrayType = std::make_shared<IRType>();
            auto exprInstrs = visit(*node.arrayExpr[0]);
            if(auto *literal = dynamic_cast<IRLiteral *>(& *node.arrayExpr[0]->ret)){
                if(literal->literalType == INT_LITERAL){
                    assignList.push_back(literal->intValue);
                    arrayType = currentScope->lookupTypeSymbol("i32");
                }else if(literal->literalType == BOOL_LITERAL){
                    if(literal->intValue != 0){
                        assignList.push_back(1);
                    }else{
                        assignList.push_back(0);
                    }
                    arrayType = currentScope->lookupTypeSymbol("bool");
                }
            }
            auto arrayVar = std::make_shared<IRVar>();
            arrayVar->type = std::make_shared<IRArrayType>(arrayType, size);
            if(auto arraytp = std::dynamic_pointer_cast<IRArrayType>(arrayVar->type)){
                caculateArraySize(arraytp);
            }
            block->instrList.push_back(std::make_shared<IRAlloca>(arrayVar->type,arrayVar));
            for(int i = 0;i < size;i ++) {
                auto exprInstrs = visit(*node.arrayExpr[i]);
                if(exprInstrs){
                    if(block->blockList.empty()){
                        for(auto & instr : exprInstrs->instrList){
                            block->instrList.push_back(instr);
                        }
                        if(exprInstrs->blockList.size() > 0){
                            for(auto & b : exprInstrs->blockList){
                                block->blockList.push_back(b);
                            }
                        }
                    }else{
                        auto lastBlock = block->blockList[block->blockList.size() - 1];
                        for(auto & instr : exprInstrs->instrList){
                            lastBlock->instrList.push_back(instr);
                        }
                        if(exprInstrs->blockList.size() > 0){
                            for(auto & b : exprInstrs->blockList){
                                block->blockList.push_back(b);
                            }
                        }
                    }
                }
                if(auto literal = std::dynamic_pointer_cast<IRLiteral>(node.arrayExpr[i]->ret)){
                    auto getptrInstr = std::make_shared<IRGetptr>();
                    getptrInstr->base = arrayVar;
                    getptrInstr->offset = i;
                    getptrInstr->type = arrayVar->type;
                    auto resVar = std::make_shared<IRVar>();
                    resVar->type = arrayType;
                    getptrInstr->res = resVar;
                    auto storeInstr = std::make_shared<IRStore>();
                    storeInstr->valueType = resVar->type;
                    storeInstr->address = getptrInstr->res;
                    storeInstr->storeLiteral = literal;
                    if(block->blockList.empty()){
                        block->instrList.push_back(getptrInstr);
                        block->instrList.push_back(storeInstr);
                    }else{
                        auto lastBlock = block->blockList[block->blockList.size() - 1];
                        lastBlock->instrList.push_back(getptrInstr);
                        lastBlock->instrList.push_back(storeInstr);
                    }
                }
            }
            node.ret = arrayVar;
        }
        node.is_lvalue = true;
        return block;
    }

    std::shared_ptr<IRBlock> visit(ExprBlock &node){
        return nullptr;
    }

    std::shared_ptr<IRBlock> visit(ExprBreak &node){
        auto block = std::make_shared<IRBlock>();
        block->instrList.push_back(std::make_shared<IRBreak>());
        return block;
    }

    std::shared_ptr<IRBlock> visit(ExprCall &node){
        auto block = std::make_shared<IRBlock>();
        std::string funcName = "";
        if(auto *p = dynamic_cast<ExprPath *>(& *node.expr)){
            if(p->pathFirst->pathSegments.type == IDENTIFIER){
                funcName = p->pathFirst->pathSegments.identifier;
            }
        }
        if(funcName == "exit"){
            auto exitInstr = std::make_shared<IRExit>();
            block->instrList.push_back(exitInstr);
            node.ret = nullptr;
            return block;
        }else if(funcName == "printlnInt"){
            auto printInstr = std::make_shared<IRPrint>();
            for(auto &arg: node.callParams){
                auto argInstrs = visit(*arg);
                if(argInstrs){
                    for(auto & instr : argInstrs->instrList){
                        block->instrList.push_back(instr);
                    }
                    if(argInstrs->blockList.size() > 0){
                        for(auto & b : argInstrs->blockList){
                            block->blockList.push_back(b);
                        }
                    }
                }
                printInstr->printVar = arg->ret;
                if(block->blockList.empty()){
                    block->instrList.push_back(printInstr);
                }else{
                    auto lastBlock = block->blockList[block->blockList.size() - 1];
                    lastBlock->instrList.push_back(printInstr);
                }
                node.ret = nullptr;
                node.is_lvalue = true;
                return block;
            }
        }else if(funcName == "getInt"){
            auto getIntInstr = std::make_shared<IRGetint>();
            auto retVar = std::make_shared<IRVar>();
            retVar->type = currentScope->lookupTypeSymbol("i32");
            getIntInstr->result = retVar;
            block->instrList.push_back(getIntInstr);
            node.ret = retVar;
            node.is_lvalue = true;
            return block;
        }
        node.expr->is_lvalue = true;
        auto funcNameInstrs = visit(*node.expr);
        if(funcNameInstrs){
            for(auto & instr : funcNameInstrs->instrList){
                block->instrList.push_back(instr);
            }
            if(funcNameInstrs->blockList.size() > 0){
                for(auto & b : funcNameInstrs->blockList){
                    block->blockList.push_back(b);
                }
            }
        }
        if(auto func = std::dynamic_pointer_cast<IRFunction>(node.expr->ret)){
            auto currentCallInstr = std::make_shared<IRCall>();
            currentCallInstr->function = func;
            currentCallInstr->pList = std::make_shared<IRParam>();
            for(int i = 0;i < node.callParams.size();i ++){
                auto & arg = node.callParams[i];
                if(auto *ptrtype = dynamic_cast<IRPtrType *>(& *func->typeList[i])){
                    arg->is_lvalue = true;
                    auto argInstrs = visit(*arg);
                    if(argInstrs){
                        if(block->blockList.empty()){
                            for(auto & instr : argInstrs->instrList){
                                block->instrList.push_back(instr);
                            }
                        }else{
                            for(auto & instr : argInstrs->instrList){
                                auto lastBlock = block->blockList[block->blockList.size() - 1];
                                lastBlock->instrList.push_back(instr);
                            }
                            if(argInstrs->blockList.size() > 0){
                                for(auto & b : argInstrs->blockList){
                                    block->blockList.push_back(b);
                                }
                            }
                        }
                    }
                    currentCallInstr->pList->paramList.push_back(arg->ret);
                }else{
                    auto argInstrs = visit(*arg);
                    if(argInstrs){
                        if(block->blockList.empty()){
                            for(auto & instr : argInstrs->instrList){
                                block->instrList.push_back(instr);
                            }
                        }else{
                            for(auto & instr : argInstrs->instrList){
                                auto lastBlock = block->blockList[block->blockList.size() - 1];
                                lastBlock->instrList.push_back(instr);
                            }
                            if(argInstrs->blockList.size() > 0){
                                for(auto & b : argInstrs->blockList){
                                    block->blockList.push_back(b);
                                }
                            }
                        }
                    }
                    currentCallInstr->pList->paramList.push_back(arg->ret);
                }
            }
            if(auto *retType = dynamic_cast<IRStructType *>(& *func->retType)){
                auto structRetVar = std::make_shared<IRVar>();
                structRetVar->type = func->retType;
                currentCallInstr->retVar = structRetVar;
                if(block->blockList.empty()){
                    block->instrList.push_back(std::make_shared<IRAlloca>(structRetVar->type,structRetVar));
                }else{
                    auto lastBlock = block->blockList[block->blockList.size() - 1];
                    lastBlock->instrList.push_back(std::make_shared<IRAlloca>(structRetVar->type,structRetVar));
                }
                node.ret = structRetVar;
                currentCallInstr->pList->paramList.push_back(structRetVar);
            }else if(auto *retType = dynamic_cast<IRVoidType *>(& *func->retType)){
                node.ret = nullptr;
            }else{
                auto retVar = std::make_shared<IRVar>();
                retVar->type = func->retType;
                currentCallInstr->retVar = retVar;
                node.ret = retVar;
            }
            if(block->blockList.empty()){
                block->instrList.push_back(currentCallInstr);
            }else{
                auto lastBlock = block->blockList[block->blockList.size() - 1];
                lastBlock->instrList.push_back(currentCallInstr);
            }
        }
        node.is_lvalue = true;
        return block;
    }

    std::shared_ptr<IRBlock> visit(ExprConstBlock &node){
        return nullptr;
    }

    std::shared_ptr<IRBlock> visit(ExprContinue &node){
        auto block = std::make_shared<IRBlock>();
        block->instrList.push_back(std::make_shared<IRContinue>());
        return block;
    }

    std::shared_ptr<IRBlock> visit(ExprField &node){
        auto block = std::make_shared<IRBlock>();
        auto fieldInstrs = visit(*node.expr);
        if(fieldInstrs){
            for(auto & instr : fieldInstrs->instrList){
                block->instrList.push_back(instr);
            }
            if(fieldInstrs->blockList.size() > 0){
                for(auto & b : fieldInstrs->blockList){
                    block->blockList.push_back(b);
                }
            }
        }
        auto obj = node.expr->ret;
        if(auto var = std::dynamic_pointer_cast<IRVar>(obj)){
            if(auto structType = std::dynamic_pointer_cast<IRStructType>(var->type)){
                for(int i = 0;i < structType->memberTypes.size();i ++){
                    auto & member = structType->memberTypes[i];
                    if(member.first == node.identifier){
                        auto getptrInstr = std::make_shared<IRGetptr>();
                        getptrInstr->base = var;
                        getptrInstr->offset = i;
                        getptrInstr->type = structType;
                        auto resVar = std::make_shared<IRVar>();
                        resVar->type = member.second;
                        getptrInstr->res = resVar;
                        if(block->blockList.empty()){
                            block->instrList.push_back(getptrInstr);
                        }else{
                            auto lastBlock = block->blockList[block->blockList.size() - 1];
                            lastBlock->instrList.push_back(getptrInstr);
                        }
                        node.ret = resVar;
                    }
                }
            }
        }
        return block;
    }

    std::shared_ptr<IRBlock> visit(ExprGroup &node){
        auto block = std::make_shared<IRBlock>();
        auto exprInstrs = visit(*node.expr);
        if(exprInstrs){
            for(auto & instr : exprInstrs->instrList){
                block->instrList.push_back(instr);
            }
            if(exprInstrs->blockList.size() > 0){
                for(auto & b : exprInstrs->blockList){
                    block->blockList.push_back(b);
                }
            }
        }
        node.ret = node.expr->ret;
        node.is_lvalue = true;
        return block;
    }

    std::shared_ptr<IRBlock> visit(ExprIf &node, std::shared_ptr<IRVar> structRetVar = nullptr){
        auto ifBlock = std::make_shared<IRBlock>();
        std::vector<std::shared_ptr<IRBlock>> blocks;
        std::vector<std::shared_ptr<IRNode>> instrs;
        //todo condition
        auto condVar = std::make_shared<IRVar>();
        auto condBlock = std::make_shared<IRBlock>();
        if(node.condition){
            auto condInstrs = visit(*node.condition);
            if(condInstrs){
                for(auto & instr : condInstrs->instrList){
                    condBlock->instrList.push_back(instr);
                }
                if(condInstrs->blockList.size() > 0){
                    for(auto & b : condInstrs->blockList){
                        condBlock->blockList.push_back(b);
                    }
                }
            }
            if(auto var = std::dynamic_pointer_cast<IRVar>(node.condition->ret)){
                if(var->type == currentScope->lookupTypeSymbol("BOOL")){
                    condVar = var;
                }else{
                    auto cmpVar = std::make_shared<IRVar>();
                    cmpVar->type = currentScope->lookupTypeSymbol("BOOL");
                    auto neqInstr = std::make_shared<IRBinaryop>();
                    neqInstr->leftValue = var;
                    neqInstr->rightValue = std::make_shared<IRLiteral>(INT_LITERAL,0);
                    neqInstr->op = NEQ;
                    neqInstr->result = cmpVar;
                    if(var->type == currentScope->lookupTypeSymbol("bool")){
                        neqInstr->i8tag = true;
                    }
                    if(condBlock->blockList.empty()){
                        condBlock->instrList.push_back(neqInstr);
                    }else{
                        auto lastBlock = condBlock->blockList[condBlock->blockList.size() - 1];
                        lastBlock->instrList.push_back(neqInstr);
                    }
                    condVar = cmpVar;
                }
            }
        }
        for(auto & instr : condBlock->instrList){
            instrs.push_back(instr);
        }
        for(auto & b : condBlock->blockList){
            blocks.push_back(b);
        }
        auto ifScope = std::make_shared<IRScope>();
        ifScope->parent = currentScope;
        currentScope->children.push_back(ifScope);
        currentScope = ifScope;
        auto thenBlock = std::make_shared<IRBlock>();
        bool isThenReturn = false;
        if(node.thenBlock){
            for(auto &stmt: node.thenBlock->statements){
                if(auto *exprStmt = dynamic_cast<StmtExpr *>(& *stmt)){
                    if(auto *ifExpr = dynamic_cast<ExprIf *>(& *exprStmt->stmtExpr)){
                        if(thenBlock->blockList.empty()){
                            auto nestedIfBlock = visit(*ifExpr,structRetVar);
                            for(auto & instr : nestedIfBlock->instrList){
                                thenBlock->instrList.push_back(instr);
                            }
                            for(auto & block : nestedIfBlock->blockList){
                                thenBlock->blockList.push_back(block);
                            }
                        }else{
                            auto lastBlock = thenBlock->blockList[thenBlock->blockList.size() - 1];
                            auto nestedIfBlock = visit(*ifExpr);
                            for(auto & instr : nestedIfBlock->instrList){
                                lastBlock->instrList.push_back(instr);
                            }
                            for(auto & block : nestedIfBlock->blockList){
                                thenBlock->blockList.push_back(block);
                            }
                        }
                    }else if(auto *loopExpr = dynamic_cast<ExprLoop *>(& *exprStmt->stmtExpr)){
                        if(thenBlock->blockList.empty()){
                            auto loopBlock = visit(*loopExpr);
                            for(auto & instr : loopBlock->instrList){
                                thenBlock->instrList.push_back(instr);
                            }
                            for(auto & block : loopBlock->blockList){
                                thenBlock->blockList.push_back(block);
                            }
                        }else{
                            auto lastBlock = thenBlock->blockList[thenBlock->blockList.size() - 1];
                            auto loopBlock = visit(*loopExpr);
                            for(auto & instr : loopBlock->instrList){
                                lastBlock->instrList.push_back(instr);
                            }
                            for(auto & block : loopBlock->blockList){
                                thenBlock->blockList.push_back(block);
                            }
                        }
                    }else{
                        auto stmtInstrs = visit(*exprStmt->stmtExpr);
                        if(stmtInstrs){
                            if(thenBlock->blockList.empty()){
                                for(auto & instr : stmtInstrs->instrList){
                                    thenBlock->instrList.push_back(instr);
                                }
                                for(auto & block : stmtInstrs->blockList){
                                    thenBlock->blockList.push_back(block);
                                }
                            }else{
                                auto lastBlock = thenBlock->blockList[thenBlock->blockList.size() - 1];
                                for(auto & instr : stmtInstrs->instrList){
                                    lastBlock->instrList.push_back(instr);
                                }
                                for(auto & block : stmtInstrs->blockList){
                                    thenBlock->blockList.push_back(block);
                                }
                            }
                        }
                        if(auto *returnExpr = dynamic_cast<ExprReturn *>(& *exprStmt->stmtExpr)){
                            isThenReturn = true;
                        }
                    }
                }else if(auto *letStmt = dynamic_cast<StmtLet *>(& *stmt)){
                    auto stmtInstrs = visit(*letStmt);
                    if(stmtInstrs){
                        if(thenBlock->blockList.empty()){
                            for(auto & instr : stmtInstrs->instrList){
                                thenBlock->instrList.push_back(instr);
                            }
                            for(auto & block : stmtInstrs->blockList){
                                thenBlock->blockList.push_back(block);
                            }
                        }else{
                            auto lastBlock = thenBlock->blockList[thenBlock->blockList.size() - 1];
                            for(auto & instr : stmtInstrs->instrList){
                                lastBlock->instrList.push_back(instr);
                            }
                            for(auto & block : stmtInstrs->blockList){
                                thenBlock->blockList.push_back(block);
                            }
                        }
                    }
                }
            }
            if(node.thenBlock->ExpressionWithoutBlock){
                isThenReturn = true;
                if(structRetVar){
                    node.thenBlock->ExpressionWithoutBlock->is_lvalue = true;
                }
                auto retExprInstrs = visit(*node.thenBlock->ExpressionWithoutBlock);
                if(retExprInstrs){
                    if(thenBlock->blockList.empty()){
                        for(auto & instr : retExprInstrs->instrList){
                            thenBlock->instrList.push_back(instr);
                        }
                        for(auto & block : retExprInstrs->blockList){
                            thenBlock->blockList.push_back(block);
                        }
                    }else{
                        auto lastBlock = thenBlock->blockList[thenBlock->blockList.size() - 1];
                        for(auto & instr : retExprInstrs->instrList){
                            lastBlock->instrList.push_back(instr);
                        }
                        for(auto & block : retExprInstrs->blockList){
                            thenBlock->blockList.push_back(block);
                        }
                    }
                }
                if(structRetVar){
                    auto memcpyInstr = std::make_shared<IRMemcpy>();
                    memcpyInstr->dest = structRetVar;
                    if(auto retVar = std::dynamic_pointer_cast<IRVar>(node.thenBlock->ExpressionWithoutBlock->ret)){
                        memcpyInstr->value = retVar;
                    }
                    memcpyInstr->size = structRetVar->type->size;
                    if(thenBlock->blockList.empty()){
                        thenBlock->instrList.push_back(memcpyInstr);
                        thenBlock->instrList.push_back(std::make_shared<IRReturn>(std::make_shared<IRVoidType>(), std::make_shared<IRVar>()));
                    }else{
                        auto lastBlock = thenBlock->blockList[thenBlock->blockList.size() - 1];
                        lastBlock->instrList.push_back(memcpyInstr);
                        lastBlock->instrList.push_back(std::make_shared<IRReturn>(std::make_shared<IRVoidType>(), std::make_shared<IRVar>()));
                    }
                }else{
                    auto returnInstr = std::make_shared<IRReturn>();
                    if(auto var = std::dynamic_pointer_cast<IRVar>(node.thenBlock->ExpressionWithoutBlock->ret)){
                        returnInstr->returnValue = var;
                        returnInstr->returnType = var->type;
                    }else if(auto literal = std::dynamic_pointer_cast<IRLiteral>(node.thenBlock->ExpressionWithoutBlock->ret)){
                        returnInstr->returnLiteral = literal;
                        returnInstr->returnType = currentScope->lookupTypeSymbol("i32");
                    }
                    if(thenBlock->blockList.empty()){
                        thenBlock->instrList.push_back(returnInstr);
                    }else{
                        auto lastBlock = thenBlock->blockList[thenBlock->blockList.size() - 1];
                        lastBlock->instrList.push_back(returnInstr);
                    }
                }
            }           
        }
        blocks.push_back(thenBlock);
        for(auto &blk: thenBlock->blockList){
            blocks.push_back(blk);
        }
        currentScope = currentScope->parent;
        bool isElseBlock = false;
        if(node.elseBlock){
            auto elseScope = std::make_shared<IRScope>();
            elseScope->parent = currentScope;
            currentScope->children.push_back(elseScope);
            currentScope = elseScope;
            if(auto *elseIfExpr = dynamic_cast<ExprIf *>(& *node.elseBlock)){
                auto elseIfBlock = visit(*elseIfExpr, structRetVar);
                blocks.push_back(elseIfBlock);
                for(auto & blk : elseIfBlock->blockList){
                    blocks.push_back(blk);
                }
            }else if(auto *blockExpr = dynamic_cast<ExprBlock *>(& *node.elseBlock)){
                auto elseBlock = std::make_shared<IRBlock>();
                for(auto &stmt: blockExpr->statements){
                    if(auto *exprStmt = dynamic_cast<StmtExpr *>(& *stmt)){
                        if(auto *ifExpr = dynamic_cast<ExprIf *>(& *exprStmt->stmtExpr)){
                            if(elseBlock->blockList.empty()){
                                auto nestedIfBlock = visit(*ifExpr, structRetVar);
                                for(auto & instr : nestedIfBlock->instrList){
                                    elseBlock->instrList.push_back(instr);
                                }
                                for(auto & block : nestedIfBlock->blockList){
                                    elseBlock->blockList.push_back(block);
                                }
                            }else{
                                auto lastBlock = elseBlock->blockList[elseBlock->blockList.size() - 1];
                                auto nestedIfBlock = visit(*ifExpr);
                                for(auto & instr : nestedIfBlock->instrList){
                                    lastBlock->instrList.push_back(instr);
                                }
                                for(auto & block : nestedIfBlock->blockList){
                                    elseBlock->blockList.push_back(block);
                                }
                            }
                        }else if(auto *loopExpr = dynamic_cast<ExprLoop *>(& *exprStmt->stmtExpr)){
                            if(elseBlock->blockList.empty()){
                                auto loopBlock = visit(*loopExpr);
                                for(auto & instr : loopBlock->instrList){
                                    elseBlock->instrList.push_back(instr);
                                }
                                for(auto & block : loopBlock->blockList){
                                    elseBlock->blockList.push_back(block);
                                }
                            }else{
                                auto lastBlock = elseBlock->blockList[elseBlock->blockList.size() - 1];
                                auto loopBlock = visit(*loopExpr);
                                for(auto & instr : loopBlock->instrList){
                                    lastBlock->instrList.push_back(instr);
                                }
                                for(auto & block : loopBlock->blockList){
                                    elseBlock->blockList.push_back(block);
                                }
                            }   
                        }else{
                            auto stmtInstrs = visit(*exprStmt->stmtExpr);
                            if(stmtInstrs){
                                if(elseBlock->blockList.empty()){
                                    for(auto & instr : stmtInstrs->instrList){
                                        elseBlock->instrList.push_back(instr);
                                    }
                                    for(auto & block : stmtInstrs->blockList){
                                        elseBlock->blockList.push_back(block);
                                    }
                                }else{
                                    auto lastBlock = elseBlock->blockList[elseBlock->blockList.size() - 1];
                                    for(auto & instr : stmtInstrs->instrList){
                                        lastBlock->instrList.push_back(instr);
                                    }
                                    for(auto & block : stmtInstrs->blockList){
                                        elseBlock->blockList.push_back(block);
                                    }
                                }
                            }
                            if(auto *returnExpr = dynamic_cast<ExprReturn *>(& *exprStmt->stmtExpr)){
                                isElseBlock = true;
                            }
                        }
                    }else if(auto *letStmt = dynamic_cast<StmtLet *>(& *stmt)){
                        auto stmtInstrs = visit(*letStmt);
                        if(stmtInstrs){
                            if(elseBlock->blockList.empty()){
                                for(auto & instr : stmtInstrs->instrList){
                                    elseBlock->instrList.push_back(instr);
                                }
                                for(auto & block : stmtInstrs->blockList){
                                    elseBlock->blockList.push_back(block);
                                }
                            }else{
                                auto lastBlock = elseBlock->blockList[elseBlock->blockList.size() - 1];
                                for(auto & instr : stmtInstrs->instrList){
                                    lastBlock->instrList.push_back(instr);
                                }
                                for(auto & block : stmtInstrs->blockList){
                                    elseBlock->blockList.push_back(block);
                                }
                            }
                        }
                    }
                }
                // todo exoression without block required here
                if(blockExpr->ExpressionWithoutBlock){
                    isElseBlock = true;
                    if(structRetVar){
                        blockExpr->ExpressionWithoutBlock->is_lvalue = true;
                    }
                    auto retExprInstrs = visit(*blockExpr->ExpressionWithoutBlock);
                    if(retExprInstrs){
                        if(elseBlock->blockList.empty()){
                            for(auto & instr : retExprInstrs->instrList){
                                elseBlock->instrList.push_back(instr);
                            }
                            for(auto & block : retExprInstrs->blockList){
                                elseBlock->blockList.push_back(block);
                            }
                        }else{
                            auto lastBlock = elseBlock->blockList[elseBlock->blockList.size() - 1];
                            for(auto & instr : retExprInstrs->instrList){
                                lastBlock->instrList.push_back(instr);
                            }
                            for(auto & block : retExprInstrs->blockList){
                                elseBlock->blockList.push_back(block);
                            }
                        }
                    }
                    if(structRetVar){
                        auto memcpyInstr = std::make_shared<IRMemcpy>();
                        memcpyInstr->dest = structRetVar;
                        if(auto retVar = std::dynamic_pointer_cast<IRVar>(blockExpr->ExpressionWithoutBlock->ret)){
                            memcpyInstr->value = retVar;
                        }
                        memcpyInstr->size = structRetVar->type->size;
                        if(elseBlock->blockList.empty()){
                            elseBlock->instrList.push_back(memcpyInstr);
                            elseBlock->instrList.push_back(std::make_shared<IRReturn>(std::make_shared<IRVoidType>(), std::make_shared<IRVar>()));
                        }else{
                            auto lastBlock = elseBlock->blockList[elseBlock->blockList.size() - 1];
                            lastBlock->instrList.push_back(memcpyInstr);
                            lastBlock->instrList.push_back(std::make_shared<IRReturn>(std::make_shared<IRVoidType>(), std::make_shared<IRVar>()));
                        }
                    }else{
                        auto returnInstr = std::make_shared<IRReturn>();
                        if(auto var = std::dynamic_pointer_cast<IRVar>(blockExpr->ExpressionWithoutBlock->ret)){
                            returnInstr->returnValue = var;
                            returnInstr->returnType = var->type;
                        }else if(auto literal = std::dynamic_pointer_cast<IRLiteral>(blockExpr->ExpressionWithoutBlock->ret)){
                            returnInstr->returnLiteral = literal;
                            returnInstr->returnType = currentScope->lookupTypeSymbol("i32");
                        }
                        if(elseBlock->blockList.empty()){
                            elseBlock->instrList.push_back(returnInstr);
                        }else{
                            auto lastBlock = elseBlock->blockList[elseBlock->blockList.size() - 1];
                            lastBlock->instrList.push_back(returnInstr);
                        }
                    }
                }
                blocks.push_back(elseBlock);
                for(auto &blk: elseBlock->blockList){
                    blocks.push_back(blk);
                }
            }
            currentScope = currentScope->parent;
        }
        auto returnBlock = std::make_shared<IRBlock>();
        blocks.push_back(returnBlock);
        //processing instrs br
        if(node.elseBlock){
            if(condBlock->blockList.size() == 0){
                instrs.push_back(std::make_shared<IRBr>(condVar, thenBlock, blocks[thenBlock->blockList.size() + 1]));
            }else{
                condBlock->blockList[condBlock->blockList.size() - 1]->instrList.push_back(std::make_shared<IRBr>(condVar, thenBlock, blocks[thenBlock->blockList.size() + condBlock->blockList.size() + 1]));
            }
        }else{
            if(condBlock->blockList.size() == 0){
                instrs.push_back(std::make_shared<IRBr>(condVar, thenBlock, returnBlock));
            }else{
                condBlock->blockList[condBlock->blockList.size() - 1]->instrList.push_back(std::make_shared<IRBr>(condVar, thenBlock, returnBlock));
            }
        }
        if(thenBlock->blockList.size() > 0){
            if(isThenReturn == false){
                auto thenLastBlock = thenBlock->blockList[thenBlock->blockList.size() - 1];
                thenLastBlock->instrList.push_back(std::make_shared<IRBr>(returnBlock));
            }
        }else{
            if(isThenReturn == false){
                thenBlock->instrList.push_back(std::make_shared<IRBr>(returnBlock));
            }
        }
        if(node.elseBlock){
            if(blocks[blocks.size() - 2]->blockList.size() > 0){
                if(isElseBlock == false){
                    auto elseLastBlock = blocks[blocks.size() - 2]->blockList[blocks[blocks.size() - 2]->blockList.size() - 1];
                    elseLastBlock->instrList.push_back(std::make_shared<IRBr>(returnBlock));
                }
            }else{
                if(isElseBlock == false){
                    blocks[blocks.size() - 2]->instrList.push_back(std::make_shared<IRBr>(returnBlock));
                }
            }
        }
        ifBlock->instrList = instrs;
        ifBlock->blockList = blocks;
        return ifBlock;
    }

    std::shared_ptr<IRBlock> normalVisit(ExprIf &node){
        auto block = std::make_shared<IRBlock>();
        auto condBlock = std::make_shared<IRBlock>();
        auto condVar = std::make_shared<IRVar>();
        auto condInstrs = visit(*node.condition);
        if(condInstrs){
            for(auto & instr : condInstrs->instrList){
                condBlock->instrList.push_back(instr);
            }
            if(condInstrs->blockList.size() >0){
                for(auto &blk: condInstrs->blockList){
                    condBlock->blockList.push_back(blk);
                }
            }
            if(auto var = std::dynamic_pointer_cast<IRVar>(node.condition->ret)){
                if(var->type == currentScope->lookupTypeSymbol("BOOL")){
                    condVar = var;
                }else{
                    auto cmpVar = std::make_shared<IRVar>();
                    cmpVar->type = currentScope->lookupTypeSymbol("BOOL");
                    auto neqInstr = std::make_shared<IRBinaryop>();
                    neqInstr->leftValue = var;
                    neqInstr->rightValue = std::make_shared<IRLiteral>(INT_LITERAL,0);
                    neqInstr->op = NEQ;
                    neqInstr->result = cmpVar;
                    if(var->type == currentScope->lookupTypeSymbol("bool")){
                        neqInstr->i8tag = true;
                    }
                    condBlock->instrList.push_back(neqInstr);
                    condVar = cmpVar;
                }
            }
        }
        for(auto & instr : condBlock->instrList){
            block->instrList.push_back(instr);
        }
        for(auto & blk : condBlock->blockList){
            block->blockList.push_back(blk);
        }
        auto thenBlock = std::make_shared<IRBlock>();
        auto firstState = std::make_shared<IRValue>();
        if(node.thenBlock){
            bool origLvalue = node.thenBlock->ExpressionWithoutBlock->is_lvalue;
            auto thenInstrs1 = visit(*node.thenBlock->ExpressionWithoutBlock);
            node.thenBlock->ExpressionWithoutBlock->is_lvalue = origLvalue;
            if(auto var = std::dynamic_pointer_cast<IRVar>(node.thenBlock->ExpressionWithoutBlock->ret)){
                if(auto *tp = dynamic_cast<IRStructType *>(& *var->type)){
                    node.thenBlock->ExpressionWithoutBlock->is_lvalue = true;
                }
            }
            auto thenInstrs = visit(*node.thenBlock->ExpressionWithoutBlock);
            if(thenInstrs){
                for(auto & instr : thenInstrs->instrList){
                    thenBlock->instrList.push_back(instr);
                }
                if(thenInstrs->blockList.size() >0){
                    for(auto &blk: thenInstrs->blockList){
                        thenBlock->blockList.push_back(blk);
                    }
                }
            }
            if(auto var = std::dynamic_pointer_cast<IRVar>(node.thenBlock->ExpressionWithoutBlock->ret)){
                if(auto *intType = dynamic_cast<IRIntType *>(& *var->type)){
                    firstState = var;
                }
            }else if(auto literal = std::dynamic_pointer_cast<IRLiteral>(node.thenBlock->ExpressionWithoutBlock->ret)){
                firstState = literal;
            }
        }
        auto elseBlock = std::make_shared<IRBlock>();
        auto secondState = std::make_shared<IRValue>();
        if(node.elseBlock){
            if(auto *elseblk = dynamic_cast<ExprBlock *>(& *node.elseBlock)){
                bool origLvalue = elseblk->ExpressionWithoutBlock->is_lvalue;
                auto elseInstrs1 = visit(*elseblk->ExpressionWithoutBlock);
                elseblk->ExpressionWithoutBlock->is_lvalue = origLvalue;
                if(auto var = std::dynamic_pointer_cast<IRVar>(elseblk->ExpressionWithoutBlock->ret)){
                    if(auto *tp = dynamic_cast<IRStructType *>(& *var->type)){
                        elseblk->ExpressionWithoutBlock->is_lvalue = true;
                    }
                }
                auto elseInstrs = visit(*elseblk->ExpressionWithoutBlock);
                if(elseInstrs){
                    for(auto & instr : elseInstrs->instrList){
                        elseBlock->instrList.push_back(instr);
                    }
                    if(elseInstrs->blockList.size() >0){
                        for(auto &blk: elseInstrs->blockList){
                            elseBlock->blockList.push_back(blk);
                        }
                    }
                }
                if(auto var = std::dynamic_pointer_cast<IRVar>(elseblk->ExpressionWithoutBlock->ret)){
                    if(auto *intType = dynamic_cast<IRIntType *>(& *var->type)){
                        secondState = var;
                    }
                }else if(auto literal = std::dynamic_pointer_cast<IRLiteral>(elseblk->ExpressionWithoutBlock->ret)){
                    secondState = literal;
                }
            }
        }
        auto mergeBlock = std::make_shared<IRBlock>();
        if(block->blockList.size() ==0){
            block->instrList.push_back(std::make_shared<IRBr>(condVar, thenBlock, elseBlock));
        }else{
            block->blockList[block->blockList.size() -1]->instrList.push_back(std::make_shared<IRBr>(condVar, thenBlock, elseBlock));
        }
        block->blockList.push_back(thenBlock);
        for(auto &blk : thenBlock->blockList){
            block->blockList.push_back(blk);
        }
        if(thenBlock->blockList.size() == 0){
            thenBlock->instrList.push_back(std::make_shared<IRBr>(mergeBlock));
        }else{
            thenBlock->blockList[thenBlock->blockList.size() -1]->instrList.push_back(std::make_shared<IRBr>(mergeBlock));
        }
        block->blockList.push_back(elseBlock);
        for(auto &blk : elseBlock->blockList){
            block->blockList.push_back(blk);
        }
        if(elseBlock->blockList.size() == 0){
            elseBlock->instrList.push_back(std::make_shared<IRBr>(mergeBlock));
        }else{
            elseBlock->blockList[elseBlock->blockList.size() -1]->instrList.push_back(std::make_shared<IRBr>(mergeBlock));
        }
        block->blockList.push_back(mergeBlock);
        auto PHIInstr = std::make_shared<IRPHI>();
        auto resVar = std::make_shared<IRVar>();
        if(auto firstVar = std::dynamic_pointer_cast<IRVar>(firstState)){
            resVar->type = firstVar->type;
        }else if(auto secondVar = std::dynamic_pointer_cast<IRVar>(secondState)){
            resVar->type = secondVar->type;
        }else{
            resVar->type = currentScope->lookupTypeSymbol("i32");
        }
        PHIInstr->result = resVar;
        PHIInstr->firstState = firstState;
        PHIInstr->secondState = secondState;
        if(thenBlock->blockList.size() == 0){
            PHIInstr->firstBlock = thenBlock;
        }else{
            PHIInstr->firstBlock = thenBlock->blockList[thenBlock->blockList.size() -1];
        }
        if(elseBlock->blockList.size() == 0){
            PHIInstr->secondBlock = elseBlock;
        }else{
            PHIInstr->secondBlock = elseBlock->blockList[elseBlock->blockList.size() -1];
        }
        mergeBlock->instrList.push_back(PHIInstr);
        node.ret = resVar;
        return block;
    }

    std::shared_ptr<IRBlock> visit(ExprIndex &node){
        auto block = std::make_shared<IRBlock>();
        auto arrayInstrs = visit(*node.name);
        if(arrayInstrs){
            for(auto & instr : arrayInstrs->instrList){
                block->instrList.push_back(instr);
            }
            if(arrayInstrs->blockList.size() > 0){
                for(auto & b : arrayInstrs->blockList){
                    block->blockList.push_back(b);
                }
            }
        }
        auto indexInstrs = visit(*node.index);
        if(indexInstrs){
            if(block->blockList.empty()){
                for(auto & instr : indexInstrs->instrList){
                    block->instrList.push_back(instr);
                }
            }else{
                for(auto & instr : indexInstrs->instrList){
                    auto lastBlock = block->blockList[block->blockList.size() - 1];
                    lastBlock->instrList.push_back(instr);
                }
            }
        }
        if(auto var = std::dynamic_pointer_cast<IRVar>(node.name->ret)){
            if(auto *arrayType = dynamic_cast<IRArrayType *>(& *var->type)){
                auto getptrInstr = std::make_shared<IRGetptr>();
                getptrInstr->base = var;
                if(auto indexVar = std::dynamic_pointer_cast<IRVar>(node.index->ret)){
                    getptrInstr->index = indexVar;
                }else if(auto *indexLiteral = dynamic_cast<IRLiteral *>(& *node.index->ret)){
                    getptrInstr->offset = indexLiteral->intValue;
                }
                getptrInstr->type = var->type;
                auto resVar = std::make_shared<IRVar>();
                resVar->type = arrayType->elementType;
                getptrInstr->res = resVar;
                if(block->blockList.empty()){
                    block->instrList.push_back(getptrInstr);
                }else{
                    auto lastBlock = block->blockList[block->blockList.size() - 1];
                    lastBlock->instrList.push_back(getptrInstr);
                }
                node.ret = resVar;
            }
        }
        return block;
    }

    std::shared_ptr<IRBlock> visit(ExprLiteral &node){
        if(node.type == TRUE){
            node.ret = std::make_shared<IRLiteral>(BOOL_LITERAL,1);
        }else if(node.type == FALSE){
            node.ret = std::make_shared<IRLiteral>(BOOL_LITERAL,0);
        }else{
            node.ret = std::make_shared<IRLiteral>(INT_LITERAL,node.integer);
        }
        node.is_lvalue = true;
        return nullptr;
    }

    std::shared_ptr<IRBlock> visit(ExprLoop &node){
        auto loopBlock = std::make_shared<IRBlock>();
        std::vector<std::shared_ptr<IRNode>> instrs;
        std::vector<std::shared_ptr<IRBlock>> blocks;
        auto condBlock = std::make_shared<IRBlock>();
        instrs.push_back(std::make_shared<IRBr>(condBlock));
        bool isTrue = false;
        auto condVar = std::make_shared<IRVar>();
        //todo condition
        if(node.condition){
            auto condInstrs = visit(*node.condition);
            if(condInstrs){
                for(auto & instr : condInstrs->instrList){
                    condBlock->instrList.push_back(instr);
                }
                if(condInstrs->blockList.size() > 0){
                    for(auto & b : condInstrs->blockList){
                        condBlock->blockList.push_back(b);
                    }
                }
            }
            if(auto var = std::dynamic_pointer_cast<IRVar>(node.condition->ret)){
                if(var->type == currentScope->lookupTypeSymbol("BOOL")){
                    condVar = var;
                }else{
                    auto cmpVar = std::make_shared<IRVar>();
                    cmpVar->type = currentScope->lookupTypeSymbol("BOOL");
                    auto neqInstr = std::make_shared<IRBinaryop>();
                    neqInstr->leftValue = var;
                    neqInstr->rightValue = std::make_shared<IRLiteral>(INT_LITERAL,0);
                    neqInstr->op = NEQ;
                    neqInstr->result = cmpVar;
                    if(var->type == currentScope->lookupTypeSymbol("bool")){
                        neqInstr->i8tag = true;
                    }
                    if(condBlock->blockList.empty()){
                        condBlock->instrList.push_back(neqInstr);
                    }else{
                        auto lastBlock = condBlock->blockList[condBlock->blockList.size() - 1];
                        lastBlock->instrList.push_back(neqInstr);
                    }
                    condVar = cmpVar;
                }
            }
        }
        auto loopScope = std::make_shared<IRScope>();
        loopScope->parent = currentScope;
        currentScope->children.push_back(loopScope);
        currentScope = loopScope;
        if(node.PredicateLoopExpression){
            auto bodyBlock = std::make_shared<IRBlock>();
            for(auto &stmt: node.PredicateLoopExpression->statements){
                if(auto *exprStmt = dynamic_cast<StmtExpr *>(& *stmt)){
                    if(auto *ifExpr = dynamic_cast<ExprIf *>(& *exprStmt->stmtExpr)){
                        if(bodyBlock->blockList.empty()){
                            auto nestedIfBlock = visit(*ifExpr);
                            for(auto & instr : nestedIfBlock->instrList){
                                bodyBlock->instrList.push_back(instr);
                            }
                            for(auto & block : nestedIfBlock->blockList){
                                bodyBlock->blockList.push_back(block);
                            }
                        }else{
                            auto lastBlock = bodyBlock->blockList[bodyBlock->blockList.size() - 1];
                            auto nestedIfBlock = visit(*ifExpr);
                            for(auto & instr : nestedIfBlock->instrList){
                                lastBlock->instrList.push_back(instr);
                            }
                            for(auto & block : nestedIfBlock->blockList){
                                bodyBlock->blockList.push_back(block);
                            }
                        }
                    }else if(auto *loopExpr = dynamic_cast<ExprLoop *>(& *exprStmt->stmtExpr)){
                        if(bodyBlock->blockList.empty()){
                            auto nestedLoopBlock = visit(*loopExpr);
                            for(auto & instr : nestedLoopBlock->instrList){
                                bodyBlock->instrList.push_back(instr);
                            }
                            for(auto & block : nestedLoopBlock->blockList){
                                bodyBlock->blockList.push_back(block);
                            }
                        }else{
                            auto lastBlock = bodyBlock->blockList[bodyBlock->blockList.size() - 1];
                            auto nestedLoopBlock = visit(*loopExpr);
                            for(auto & instr : nestedLoopBlock->instrList){
                                lastBlock->instrList.push_back(instr);
                            }
                            for(auto & block : nestedLoopBlock->blockList){
                                bodyBlock->blockList.push_back(block);
                            }
                        }
                    }else {
                        auto stmtInstrs = visit(*exprStmt->stmtExpr);
                        if(stmtInstrs){
                            if(bodyBlock->blockList.empty()){
                                for(auto & instr : stmtInstrs->instrList){
                                    bodyBlock->instrList.push_back(instr);
                                }
                                for(auto & block : stmtInstrs->blockList){
                                    bodyBlock->blockList.push_back(block);
                                }
                            }else{
                                auto lastBlock = bodyBlock->blockList[bodyBlock->blockList.size() - 1];
                                for(auto & instr : stmtInstrs->instrList){
                                    lastBlock->instrList.push_back(instr);
                                }
                                for(auto & block : stmtInstrs->blockList){
                                    bodyBlock->blockList.push_back(block);
                                }
                            }
                        }
                    }
                }else if(auto *letStmt = dynamic_cast<StmtLet *>(& *stmt)){
                    auto stmtInstrs = visit(*letStmt);
                    if(stmtInstrs){
                        if(bodyBlock->blockList.empty()){
                            for(auto & instr : stmtInstrs->instrList){
                                bodyBlock->instrList.push_back(instr);
                            }
                            for(auto & block : stmtInstrs->blockList){
                                bodyBlock->blockList.push_back(block);
                            }
                        }else{
                            auto lastBlock = bodyBlock->blockList[bodyBlock->blockList.size() - 1];
                            for(auto & instr : stmtInstrs->instrList){
                                lastBlock->instrList.push_back(instr);
                            }
                            for(auto & block : stmtInstrs->blockList){
                                bodyBlock->blockList.push_back(block);
                            }
                        }
                    }
                }
            }
            // todo exoression without block required here
            if(node.PredicateLoopExpression->ExpressionWithoutBlock){
                //seems no need to process return in loop body
            }
            currentScope = currentScope->parent;
            auto returnBlock = std::make_shared<IRBlock>();
            if(condBlock->blockList.size() > 0){
                auto condLastBlock = condBlock->blockList[condBlock->blockList.size() - 1];
                condLastBlock->instrList.push_back(std::make_shared<IRBr>(condVar, bodyBlock, returnBlock));
            }else{
                condBlock->instrList.push_back(std::make_shared<IRBr>(condVar, bodyBlock, returnBlock));
            }
            blocks.push_back(condBlock);
            for(auto &blk: condBlock->blockList){
                blocks.push_back(blk);
            }
            blocks.push_back(bodyBlock);
            for(auto &blk: bodyBlock->blockList){
                for(int i = 0; i < blk->instrList.size(); i++){
                    if(auto *breakInstr = dynamic_cast<IRBreak *>(& *blk->instrList[i])){
                        //replace break with br to returnBlock
                        blk->instrList[i] = std::make_shared<IRBr>(returnBlock);
                        for(int j = i + 1; j < blk->instrList.size(); j++){
                            //remove instructions after break
                            blk->instrList.erase(blk->instrList.begin() + j);
                            j--;
                        }
                    }
                }
                for(int i = 0;i < blk->instrList.size(); i++){
                    if(auto *continueInstr = dynamic_cast<IRContinue *>(& *blk->instrList[i])){
                        //replace continue with br to condBlock
                        blk->instrList[i] = std::make_shared<IRBr>(condBlock);
                        for(int j = i + 1; j < blk->instrList.size(); j++){
                            //remove instructions after continue
                            blk->instrList.erase(blk->instrList.begin() + j);
                            j--;
                        }
                    }
                }
                blocks.push_back(blk);
            }
            blocks.push_back(returnBlock);
            if(bodyBlock->blockList.size() > 0){
                auto bodyLastBlock = bodyBlock->blockList[bodyBlock->blockList.size() - 1];
                bodyLastBlock->instrList.push_back(std::make_shared<IRBr>(condBlock));
            }else{
                bodyBlock->instrList.push_back(std::make_shared<IRBr>(condBlock));
            }
        }
        loopBlock->instrList = instrs;
        loopBlock->blockList = blocks;
        return loopBlock;
    }

    std::shared_ptr<IRBlock> visit(ExprMethodcall &node){
        auto block = std::make_shared<IRBlock>();
        node.expr->is_lvalue = true;
        auto objInstrs = visit(*node.expr);
        if(objInstrs){
            for(auto & instr : objInstrs->instrList){
                block->instrList.push_back(instr);
            }
            if(objInstrs->blockList.size()){
                for(auto & blk : objInstrs->blockList){
                    block->blockList.push_back(blk);
                }
            }
        }
        auto funcname = node.PathExprSegment->pathSegments.identifier;
        if(auto objvar = std::dynamic_pointer_cast<IRVar>(node.expr->ret)){
            if(auto structtype = std::dynamic_pointer_cast<IRStructType>(objvar->type)){
                for(int i = 0;i < structtype->memberFunctions.size();i ++){
                    if(structtype->memberFunctions[i]->name == funcname){
                        auto currentIRFunc = structtype->memberFunctions[i];
                        auto currentCallInstr = std::make_shared<IRCall>();
                        currentCallInstr->function = currentIRFunc;
                        currentCallInstr->pList = std::make_shared<IRParam>();
                        //first param is self
                        if(auto *currentPtrType = dynamic_cast<IRPtrType *>(& *currentIRFunc->typeList[0])){
                            currentCallInstr->pList->paramList.push_back(objvar);
                        }else{
                            auto memcpyInstr = std::make_shared<IRMemcpy>();
                            auto selfVar = std::make_shared<IRVar>();
                            selfVar->type = currentIRFunc->typeList[0];
                            if(block->blockList.size() == 0){
                                block->instrList.push_back(std::make_shared<IRAlloca>(selfVar->type, selfVar));
                            }else{  
                                block->blockList[block->blockList.size() - 1]->instrList.push_back(std::make_shared<IRAlloca>(selfVar->type, selfVar));
                            }
                            memcpyInstr->dest = selfVar;
                            memcpyInstr->value = objvar;
                            memcpyInstr->size = selfVar->type->size;
                            if(block->blockList.size() == 0){
                                block->instrList.push_back(memcpyInstr);
                            }else{
                                block->blockList[block->blockList.size() - 1]->instrList.push_back(memcpyInstr);
                            }
                            currentCallInstr->pList->paramList.push_back(selfVar);
                        }
                        for(int i = 0;i < node.callParams.size();i ++){
                            auto &arg = node.callParams[i];
                            if(auto *ptrType = dynamic_cast<IRPtrType *>(& *currentIRFunc->typeList[i + 1])){
                                arg->is_lvalue = true;
                                auto argInstrs = visit(*arg);
                                if(argInstrs){
                                    if(block->blockList.size() == 0){
                                        for(auto & instr : argInstrs->instrList){
                                            block->instrList.push_back(instr);
                                        }
                                        for(auto & blk : argInstrs->blockList){
                                            block->blockList.push_back(blk);
                                        }
                                    }else{
                                        for(auto & instr : argInstrs->instrList){
                                            block->blockList[block->blockList.size() - 1]->instrList.push_back(instr);
                                        }
                                        for(auto & blk : argInstrs->blockList){
                                            block->blockList.push_back(blk);
                                        }
                                    }
                                }
                                currentCallInstr->pList->paramList.push_back(arg->ret);
                            }else{
                                auto argInstrs = visit(*arg);
                                if(argInstrs){
                                    if(block->blockList.size() == 0){
                                        for(auto & instr : argInstrs->instrList){
                                            block->instrList.push_back(instr);
                                        }
                                        for(auto & blk : argInstrs->blockList){
                                            block->blockList.push_back(blk);
                                        }
                                    }else{
                                        for(auto & instr : argInstrs->instrList){
                                            block->blockList[block->blockList.size() - 1]->instrList.push_back(instr);
                                        }
                                        for(auto & blk : argInstrs->blockList){
                                            block->blockList.push_back(blk);
                                        }
                                    }
                                }
                                currentCallInstr->pList->paramList.push_back(arg->ret);
                            }
                        }
                        if(auto *structType = dynamic_cast<IRStructType *>(& *currentIRFunc->retType)){
                            auto structVar = std::make_shared<IRVar>();
                            structVar->type = currentIRFunc->retType;
                            if(block->blockList.size() == 0){
                                block->instrList.push_back(std::make_shared<IRAlloca>(structVar->type, structVar));
                            }else{
                                block->blockList[block->blockList.size() - 1]->instrList.push_back(std::make_shared<IRAlloca>(structVar->type, structVar));
                            }
                            currentCallInstr->retVar = structVar;
                            currentCallInstr->pList->paramList.push_back(structVar);
                            node.ret = structVar;
                        }else if(auto *voidtype = dynamic_cast<IRVoidType *>(& *currentIRFunc->retType)){
                            node.ret = nullptr;
                        }else{
                            auto retvar = std::make_shared<IRVar>();
                            retvar->type = currentIRFunc->retType;
                            currentCallInstr->retVar = retvar;
                            node.ret = retvar;
                        }
                        if(block->blockList.size() == 0){
                            block->instrList.push_back(currentCallInstr);
                        }else{
                            block->blockList[block->blockList.size() - 1]->instrList.push_back(currentCallInstr);
                        }
                        break;
                    }
                }
            }
        }
        node.is_lvalue = true;
        return block;
    }

    IROp turnBinaryOp(binaryOp op){
        if(op == PLUS){
            return ADD;
        }else if(op == MINUS){
            return SUB;
        }else if(op == MULTIPLY){
            return MUL;
        }else if(op == DIVIDE){
            return DIV;
        }else if(op == MODULO){
            return MOD;
        }else if(op == PLUS_EQUAL){
            return ADD_EQ;
        }else if(op == MINUS_EQUAL){
            return SUB_EQ;
        }else if(op == MULTIPLY_EQUAL){
            return MUL_EQ;
        }else if(op == DIVIDE_EQUAL){
            return DIV_EQ;
        }else if(op == MODULO_EQUAL){
            return MOD_EQ;
        }else if(op == EQUAL){
            return EQ;
        }else if(op == NOT_EQUAL){
            return NEQ;
        }else if(op == LESS_THAN){
            return LT;
        }else if(op == LESS_THAN_OR_EQUAL){
            return LEQ;
        }else if(op == GREATER_THAN){
            return GT;
        }else if(op == GREATER_THAN_OR_EQUAL){
            return GEQ;
        }else if(op == LOGICAL_AND){
            return LOGICALAND;
        }else if(op == LOGICAL_OR){
            return LOGICALOR;
        }else if(op == ASSIGN){
            return ASSIGNEQ;
        }else if(op == AS_CAST){
            return ASCAST;
        }else if(op == XOR){
            return XOROP;
        }else if(op == XOR_EQUAL){
            return XOROPEQ;
        }else if(op == OR){
            return OROP;
        }else if(op == AND){
            return ANDOP;
        }else if(op == LEFT_SHIFT){
            return LEFTSHIFTOP;
        }else if(op == RIGHT_SHIFT){
            return RIGHTSHIFTOP;
        }else if(op == LEFT_SHIFT_EQUAL){
            return LEFTSHIFTOPEQ;
        }else if(op == RIGHT_SHIFT_EQUAL){
            return RIGHTSHIFTOPEQ;
        }
        throw std::runtime_error("IRBuilder turnBinaryOp error: unknown binary op");
    }

    std::shared_ptr<IRBlock> phiProcess(ExprOpbinary & node){
        auto block = std::make_shared<IRBlock>();
        auto firstBlock = std::make_shared<IRBlock>();
        block->instrList.push_back(std::make_shared<IRBr>(firstBlock));
        // auto secondBlock = std::make_shared<IRBlock>();
        // auto endBlock = std::make_shared<IRBlock>();
        auto leftInstrs = visit(*node.left);
        if(leftInstrs){
            for(auto & instr : leftInstrs->instrList){
                firstBlock->instrList.push_back(instr);
            }
            if(leftInstrs->blockList.size()){
                for(auto & blk : leftInstrs->blockList){
                    firstBlock->blockList.push_back(blk);
                }
            }
        }
        auto condVar = std::make_shared<IRVar>();
        if(auto leftVar = std::dynamic_pointer_cast<IRVar>(node.left->ret)){
            if(leftVar->type == currentScope->lookupTypeSymbol("BOOL")){
                condVar = leftVar;    
            }else{
                auto cmpVar = std::make_shared<IRVar>();
                cmpVar->type = currentScope->lookupTypeSymbol("BOOL");
                auto cmpInstr = std::make_shared<IRBinaryop>();
                cmpInstr->leftValue = leftVar;
                cmpInstr->rightValue = std::make_shared<IRLiteral>(INT_LITERAL, 0);
                cmpInstr->result = cmpVar;
                cmpInstr->op = NEQ;
                if(leftVar->type == currentScope->lookupTypeSymbol("bool")){
                    cmpInstr->i8tag = true;
                }
                if(firstBlock->blockList.size() == 0){
                    firstBlock->instrList.push_back(cmpInstr);                   
                }else{
                    firstBlock->blockList[firstBlock->blockList.size() - 1]->instrList.push_back(cmpInstr);
                }
                condVar = cmpVar;
            }
        }
        auto secondBlock = std::make_shared<IRBlock>();
        auto rightInstrs = visit(*node.right);
        if(rightInstrs){
            for(auto & instr : rightInstrs->instrList){
                secondBlock->instrList.push_back(instr);
            }
            if(rightInstrs->blockList.size()){
                for(auto & blk : rightInstrs->blockList){
                    secondBlock->blockList.push_back(blk);
                }
            }
        }
        auto secondRes = std::make_shared<IRVar>();
        if(auto rightVar = std::dynamic_pointer_cast<IRVar>(node.right->ret)){
            if(rightVar->type == currentScope->lookupTypeSymbol("BOOL")){
                secondRes = rightVar;
            }else{
                secondRes->type = currentScope->lookupTypeSymbol("BOOL");
                auto cmpInstr = std::make_shared<IRBinaryop>();
                cmpInstr->leftValue = rightVar;
                cmpInstr->rightValue = std::make_shared<IRLiteral>(INT_LITERAL, 0);
                cmpInstr->result = secondRes;
                cmpInstr->op = NEQ;
                if(rightVar->type == currentScope->lookupTypeSymbol("bool")){
                    cmpInstr->i8tag = true;
                }
                if(secondBlock->blockList.size() == 0){
                    secondBlock->instrList.push_back(cmpInstr);
                }else{
                    secondBlock->blockList[secondBlock->blockList.size() - 1]->instrList.push_back(cmpInstr);
                }
            }
        }
        auto endBlock = std::make_shared<IRBlock>();
        auto firstLastblock = std::make_shared<IRBlock>();
        if(firstBlock->blockList.size() == 0){
            firstLastblock = firstBlock;
        }else{
            firstLastblock = firstBlock->blockList[firstBlock->blockList.size() - 1];
        }
        auto secondLastblock = std::make_shared<IRBlock>();
        if(secondBlock->blockList.size() == 0){
            secondLastblock = secondBlock;
        }else{
            secondLastblock = secondBlock->blockList[secondBlock->blockList.size() - 1];
        }
        if(firstBlock->blockList.size() == 0){
            if(node.op == LOGICAL_AND){
                firstBlock->instrList.push_back(std::make_shared<IRBr>(condVar, secondBlock, endBlock));
            }else if(node.op == LOGICAL_OR){
                firstBlock->instrList.push_back(std::make_shared<IRBr>(condVar, endBlock, secondBlock));
            }
        }else{
            if(node.op == LOGICAL_AND){
                firstBlock->blockList[firstBlock->blockList.size() - 1]->instrList.push_back(std::make_shared<IRBr>(condVar, secondBlock, endBlock));
            }else if(node.op == LOGICAL_OR){
                firstBlock->blockList[firstBlock->blockList.size() - 1]->instrList.push_back(std::make_shared<IRBr>(condVar, endBlock, secondBlock));
            }
        }
        if(secondBlock->blockList.size() == 0){
            secondBlock->instrList.push_back(std::make_shared<IRBr>(endBlock));
        }else{
            secondBlock->blockList[secondBlock->blockList.size() - 1]->instrList.push_back(std::make_shared<IRBr>(endBlock));
        }
        auto phiVar = std::make_shared<IRVar>();
        phiVar->type = currentScope->lookupTypeSymbol("BOOL");
        auto phiInstr = std::make_shared<IRPhi>();
        phiInstr->result = phiVar;
        if(node.op == LOGICAL_AND){
            phiInstr->firstState = false;
            phiInstr->firstBlock = firstLastblock;   
            phiInstr->secondState = secondRes;
            phiInstr->secondBlock = secondLastblock;
        }else if(node.op == LOGICAL_OR){
            phiInstr->firstState = true;
            phiInstr->firstBlock = firstLastblock;   
            phiInstr->secondState = secondRes;
            phiInstr->secondBlock = secondLastblock;
        }
        endBlock->instrList.push_back(phiInstr);
        node.ret = phiVar;
        block->blockList.push_back(firstBlock);
        for(auto & blk : firstBlock->blockList){
            block->blockList.push_back(blk);
        }
        block->blockList.push_back(secondBlock);
        for(auto & blk : secondBlock->blockList){
            block->blockList.push_back(blk);
        }
        block->blockList.push_back(endBlock);
        node.is_lvalue = true;
        return block;
    }

    std::shared_ptr<IRBlock> ifRightProcess(ExprOpbinary &node){
        auto block = std::make_shared<IRBlock>();
        auto leftInstrs = visit(*node.left);
        if(leftInstrs){
            for(auto & instr : leftInstrs->instrList){
                block->instrList.push_back(instr);
            }
            if(leftInstrs->blockList.size()){
                for(auto & blk : leftInstrs->blockList){
                    block->blockList.push_back(blk);
                }
            }
        }
        auto leftExpr = node.left->ret;
        auto leftvar = std::dynamic_pointer_cast<IRVar>(leftExpr);
        if(auto *rightIf = dynamic_cast<ExprIf *>(& *node.right)){
            auto condVar = std::make_shared<IRVar>();
            if(rightIf->condition){
                auto condInstrs = visit(*rightIf->condition);
                if(condInstrs){
                    if(block->blockList.size() == 0){
                        for(auto & instr : condInstrs->instrList){
                            block->instrList.push_back(instr);
                        }
                        for(auto & blk : condInstrs->blockList){
                            block->blockList.push_back(blk);
                        }
                    }else{
                        for(auto & instr : condInstrs->instrList){
                            block->blockList[block->blockList.size() - 1]->instrList.push_back(instr);
                        }
                        for(auto & blk : condInstrs->blockList){
                            block->blockList.push_back(blk);
                        }
                    }
                }
                condVar = std::dynamic_pointer_cast<IRVar>(rightIf->condition->ret);
            }
            auto thenBlock = std::make_shared<IRBlock>();
            auto elseBlock = std::make_shared<IRBlock>();
            auto endBlock = std::make_shared<IRBlock>();
            if(block->blockList.size() == 0){
                block->instrList.push_back(std::make_shared<IRBr>(condVar, thenBlock, elseBlock));
            }else{
                block->blockList[block->blockList.size() - 1]->instrList.push_back(std::make_shared<IRBr>(condVar, thenBlock, elseBlock));
            }
            auto thenInstrs = visit(*rightIf->thenBlock->ExpressionWithoutBlock);
            if(thenInstrs){
                if(thenBlock->blockList.size() == 0){
                    for(auto & instr : thenInstrs->instrList){
                        thenBlock->instrList.push_back(instr);
                    }
                    for(auto & blk : thenInstrs->blockList){
                        thenBlock->blockList.push_back(blk);
                    }
                }else{
                    for(auto & instr : thenInstrs->instrList){
                        thenBlock->blockList[thenBlock->blockList.size() - 1]->instrList.push_back(instr);
                    }
                    for(auto & blk : thenInstrs->blockList){
                        thenBlock->blockList.push_back(blk);
                    }
                }
            }
            if(auto var = std::dynamic_pointer_cast<IRVar>(rightIf->thenBlock->ExpressionWithoutBlock->ret)){
                if(auto *inttype = dynamic_cast<IRIntType *>(& *var->type)){
                    auto storeInstr = std::make_shared<IRStore>();
                    storeInstr->storeValue = var;
                    storeInstr->address = leftvar;
                    storeInstr->valueType = leftvar->type;
                    if(thenBlock->blockList.size() == 0){
                        thenBlock->instrList.push_back(storeInstr);
                    }else{
                        thenBlock->blockList[thenBlock->blockList.size() - 1]->instrList.push_back(storeInstr);
                    }
                }else if(auto *structtype = dynamic_cast<IRStructType *>(& *var->type)){
                    auto memcpyInstr = std::make_shared<IRMemcpy>();
                    memcpyInstr->dest = leftvar;
                    memcpyInstr->value = var;
                    memcpyInstr->size = leftvar->type->size;
                    if(thenBlock->blockList.size() == 0){
                        thenBlock->instrList.push_back(memcpyInstr);
                    }else{
                        thenBlock->blockList[thenBlock->blockList.size() - 1]->instrList.push_back(memcpyInstr);
                    }
                }
            }else if(auto *literal = dynamic_cast<IRLiteral *>(& *rightIf->thenBlock->ExpressionWithoutBlock->ret)){
                auto storeInstr = std::make_shared<IRStore>();
                storeInstr->storeLiteral = std::make_shared<IRLiteral>(INT_LITERAL, literal->intValue);
                storeInstr->address = leftvar;
                storeInstr->valueType = leftvar->type;
                if(thenBlock->blockList.size() == 0){
                    thenBlock->instrList.push_back(storeInstr);
                }else{
                    thenBlock->blockList[thenBlock->blockList.size() - 1]->instrList.push_back(storeInstr);
                }
            }
            if(thenBlock->blockList.size() == 0){
                thenBlock->instrList.push_back(std::make_shared<IRBr>(endBlock));
            }else{
                thenBlock->blockList[thenBlock->blockList.size() - 1]->instrList.push_back(std::make_shared<IRBr>(endBlock));
            }
            if(rightIf->elseBlock){
                if(auto *rightblock = dynamic_cast<ExprBlock *>(& *rightIf->elseBlock)){
                    auto elseInstrs = visit(*rightblock->ExpressionWithoutBlock);
                    if(elseInstrs){
                        if(elseBlock->blockList.size() == 0){
                            for(auto & instr : elseInstrs->instrList){
                                elseBlock->instrList.push_back(instr);
                            }
                            for(auto & blk : elseInstrs->blockList){
                                elseBlock->blockList.push_back(blk);
                            }
                        }else{
                            for(auto & instr : elseInstrs->instrList){
                                elseBlock->blockList[elseBlock->blockList.size() - 1]->instrList.push_back(instr);
                            }
                            for(auto & blk : elseInstrs->blockList){
                                elseBlock->blockList.push_back(blk);
                            }
                        }
                        if(auto var = std::dynamic_pointer_cast<IRVar>(rightblock->ExpressionWithoutBlock->ret)){
                            if(auto *inttype = dynamic_cast<IRIntType *>(& *var->type)){
                                auto storeInstr = std::make_shared<IRStore>();
                                storeInstr->storeValue = var;
                                storeInstr->address = leftvar;
                                storeInstr->valueType = leftvar->type;
                                if(elseBlock->blockList.size() == 0){
                                    elseBlock->instrList.push_back(storeInstr);
                                }else{
                                    elseBlock->blockList[elseBlock->blockList.size() - 1]->instrList.push_back(storeInstr);
                                }
                            }else if(auto *structtype = dynamic_cast<IRStructType *>(& *var->type)){
                                auto memcpyInstr = std::make_shared<IRMemcpy>();
                                memcpyInstr->dest = leftvar;
                                memcpyInstr->value = var;
                                memcpyInstr->size = leftvar->type->size;
                                if(elseBlock->blockList.size() == 0){
                                    elseBlock->instrList.push_back(memcpyInstr);
                                }else{
                                    elseBlock->blockList[elseBlock->blockList.size() - 1]->instrList.push_back(memcpyInstr);
                                }
                            }
                        }
                        if(elseBlock->blockList.size() == 0){
                            elseBlock->instrList.push_back(std::make_shared<IRBr>(endBlock));
                        }else{
                            elseBlock->blockList[elseBlock->blockList.size() - 1]->instrList.push_back(std::make_shared<IRBr>(endBlock));
                        }
                    }
                }
            }
            block->blockList.push_back(thenBlock);
            for(auto & blk : thenBlock->blockList){
                block->blockList.push_back(blk);
            }
            block->blockList.push_back(elseBlock);
            for(auto & blk : elseBlock->blockList){
                block->blockList.push_back(blk);
            }
            block->blockList.push_back(endBlock);
        }
        return block;
    }

    std::shared_ptr<IRBlock> visit(ExprOpbinary &node){
        if(auto *left = dynamic_cast<ExprPath *>(& *node.left)){
            auto leftname = left->pathFirst->pathSegments.identifier;
            auto res = currentScope->lookupConstantSymbol(leftname);
            int leftnum = 0;
            int rightnum = 0;
            if(res.type != "null"){
                leftnum = res.value;
                if(auto *right = dynamic_cast<ExprLiteral *>(& *node.right)){
                    rightnum = right->integer;
                    if(node.op == PLUS){
                        node.ret = std::make_shared<IRLiteral>(INT_LITERAL, leftnum + rightnum);
                        node.is_lvalue = true;
                        return nullptr;
                    }else if(node.op == MINUS){
                        node.ret = std::make_shared<IRLiteral>(INT_LITERAL, leftnum - rightnum);
                        node.is_lvalue = true;
                        return nullptr;
                    }
                }
            }
        }
        if(auto *ifexpr = dynamic_cast<ExprIf *>(& *node.right)){
            if(node.op == ASSIGN){
                return ifRightProcess(node);
            }
        }
        auto block = std::make_shared<IRBlock>();
        if(node.op == LOGICAL_AND || node.op == LOGICAL_OR){
            return phiProcess(node);
        }
        auto leftInstrs = std::make_shared<IRBlock>();
        if(auto *ifExpr = dynamic_cast<ExprIf *>(& *node.left)){
            leftInstrs = normalVisit(*ifExpr);    
        }else {
            leftInstrs = visit(*node.left);
        }
        if(leftInstrs){
            for(auto & instr : leftInstrs->instrList){
                block->instrList.push_back(instr);
            }
            if(leftInstrs->blockList.size()){
                for(auto & blk : leftInstrs->blockList){
                    block->blockList.push_back(blk);
                }
            }
        }
        auto leftExpr = node.left->ret;
        if(auto *rightCast = dynamic_cast<ExprPath *>(& *node.right)){
            if(rightCast->pathFirst->pathSegments.identifier == "usize" ){
                node.ret = leftExpr;
                node.is_lvalue = true;
                return block;
            }else if(rightCast->pathFirst->pathSegments.identifier == "i32" || rightCast->pathFirst->pathSegments.identifier == "u32"){
                if(auto leftvar = std::dynamic_pointer_cast<IRVar>(leftExpr)){
                    if(leftvar->type == currentScope->lookupTypeSymbol("i32") || leftvar->type == currentScope->lookupTypeSymbol("usize") || leftvar->type == currentScope->lookupTypeSymbol("u32")){
                        node.ret = leftExpr;
                        node.is_lvalue = true;
                        return block;
                    }else{
                        auto castVar = std::make_shared<IRVar>();
                        castVar->type = currentScope->lookupTypeSymbol("i32");
                        auto castInstr = std::make_shared<IRZext>();
                        castInstr->originalType = leftvar->type;
                        castInstr->targetType = currentScope->lookupTypeSymbol("i32");
                        castInstr->value = leftvar;
                        castInstr->result = castVar;
                        if(block->blockList.size() == 0){
                            block->instrList.push_back(castInstr);
                        }else{
                            block->blockList[block->blockList.size() - 1]->instrList.push_back(castInstr);
                        }
                        node.ret = castVar;
                        node.is_lvalue = true;
                        return block;
                    }
                }
            }
        }
        auto rightInstrs = std::make_shared<IRBlock>();
        if(auto *ifExpr = dynamic_cast<ExprIf *>(& *node.right)){
            rightInstrs = normalVisit(*ifExpr);    
        }else {
            rightInstrs = visit(*node.right);
        }
        if(rightInstrs){
            if(block->blockList.size() == 0){
                for(auto & instr : rightInstrs->instrList){
                    block->instrList.push_back(instr);
                }
                for(auto & blk : rightInstrs->blockList){
                    block->blockList.push_back(blk);
                }
            }else{
                for(auto & instr : rightInstrs->instrList){
                    block->blockList[block->blockList.size() - 1]->instrList.push_back(instr);
                }
                for(auto & blk : rightInstrs->blockList){
                    block->blockList.push_back(blk);
                }
            }
        }
        auto rightExpr = node.right->ret;
        IROp op = turnBinaryOp(node.op);
        if(op == ADD_EQ || op == SUB_EQ || op == MUL_EQ || op == DIV_EQ || op == MOD_EQ || op == XOROPEQ || op == LEFTSHIFTOPEQ || op == RIGHTSHIFTOPEQ){
            if(auto leftvar = std::dynamic_pointer_cast<IRVar>(leftExpr)){
                auto loadvar = std::make_shared<IRVar>();
                loadvar->type = leftvar->type;
                auto loadInstr = std::make_shared<IRLoad>();
                loadInstr->addressVar = leftvar;
                loadInstr->tmp = loadvar;
                loadInstr->type = leftvar->type;
                auto binaryInstr = std::make_shared<IRBinaryop>();
                if(op == ADD_EQ){
                    binaryInstr->op = ADD;
                }else if(op == SUB_EQ){
                    binaryInstr->op = SUB;
                }else if(op == MUL_EQ){
                    binaryInstr->op = MUL;
                }else if(op == DIV_EQ){
                    binaryInstr->op = DIV;
                }else if(op == MOD_EQ){
                    binaryInstr->op = MOD;
                }else if(op == XOROPEQ){
                    binaryInstr->op = XOROP;
                }else if(op == LEFTSHIFTOPEQ){
                    binaryInstr->op = LEFTSHIFTOP;
                }else if(op == RIGHTSHIFTOPEQ){
                    binaryInstr->op = RIGHTSHIFTOP;
                }
                binaryInstr->leftValue = loadvar;
                binaryInstr->rightValue = rightExpr;
                auto resultVar = std::make_shared<IRVar>();
                resultVar->type = leftvar->type;
                binaryInstr->result = resultVar;
                auto binaryStoreInstr = std::make_shared<IRStore>();
                binaryStoreInstr->storeValue = resultVar;
                binaryStoreInstr->address = leftvar;
                binaryStoreInstr->valueType = leftvar->type;
                if(block->blockList.size() == 0){
                    block->instrList.push_back(loadInstr);
                    block->instrList.push_back(binaryInstr);
                    block->instrList.push_back(binaryStoreInstr);
                }else{
                    block->blockList[block->blockList.size() - 1]->instrList.push_back(loadInstr);
                    block->blockList[block->blockList.size() - 1]->instrList.push_back(binaryInstr);
                    block->blockList[block->blockList.size() - 1]->instrList.push_back(binaryStoreInstr);
                }
                node.ret = resultVar;
            }
        }else if(op == ASSIGNEQ){
            if(auto leftvar = std::dynamic_pointer_cast<IRVar>(leftExpr)){
                if(auto *intType = dynamic_cast<IRIntType *>(& *leftvar->type)){
                    auto storeInstr = std::make_shared<IRStore>();
                    auto zextvar = std::make_shared<IRVar>();
                    if(auto rightBOOL = std::dynamic_pointer_cast<IRVar>(rightExpr)){
                        if(rightBOOL->type == currentScope->lookupTypeSymbol("BOOL")){
                            auto zextInstr = std::make_shared<IRZext>();
                            zextInstr->originalType = rightBOOL->type;
                            zextInstr->targetType = leftvar->type;
                            zextInstr->value = rightBOOL;
                            zextvar->type = leftvar->type;
                            zextInstr->result = zextvar;
                            if(block->blockList.size() == 0){
                                block->instrList.push_back(zextInstr);
                            }else{
                                block->blockList[block->blockList.size() - 1]->instrList.push_back(zextInstr);
                            }
                        }else{
                            zextvar = rightBOOL;
                        }
                    }
                    if(auto rightLiteral = std::dynamic_pointer_cast<IRLiteral>(rightExpr)){
                        storeInstr->storeLiteral = rightLiteral;
                    }else if(auto rightVar = std::dynamic_pointer_cast<IRVar>(rightExpr)){
                        storeInstr->storeValue = zextvar;
                    }
                    storeInstr->address = leftvar;
                    storeInstr->valueType = leftvar->type;
                    /*if(leftvar->type  == currentScope->lookupTypeSymbol("BOOL")){
                        storeInstr->valueType = currentScope->lookupTypeSymbol("bool");
                    }*/
                    if(block->blockList.size() == 0){
                        block->instrList.push_back(storeInstr);
                    }else{
                        block->blockList[block->blockList.size() - 1]->instrList.push_back(storeInstr);
                    }
                }else{
                    auto memcpyInstr = std::make_shared<IRMemcpy>();
                    memcpyInstr->dest = leftvar;
                    if(auto rightVar = std::dynamic_pointer_cast<IRVar>(rightExpr)){
                        memcpyInstr->value = rightVar;
                    }
                    memcpyInstr->size = leftvar->type->size;
                    if(block->blockList.size() == 0){
                        block->instrList.push_back(memcpyInstr);
                    }else{
                        block->blockList[block->blockList.size() - 1]->instrList.push_back(memcpyInstr);
                    }
                }
                node.ret = leftvar;
            }
        }else{
            auto binaryInstr = std::make_shared<IRBinaryop>();
            binaryInstr->op = op;
            binaryInstr->leftValue = leftExpr;
            binaryInstr->rightValue = rightExpr;
            auto resultVar = std::make_shared<IRVar>();
            if(auto *leftVar = dynamic_cast<IRVar *>(& *leftExpr)){
                resultVar->type = leftVar->type;
                if(leftVar->type  == currentScope->lookupTypeSymbol("u32")){
                    binaryInstr->utag = true;
                }
            }else if(auto *rightVar = dynamic_cast<IRVar *>(& *rightExpr)){
                resultVar->type = rightVar->type;
            }else{
                resultVar->type = currentScope->lookupTypeSymbol("i32");
            }
            if(op == EQ || op == NEQ || op == LT || op == LEQ || op == GT || op == GEQ){
                resultVar->type = currentScope->lookupTypeSymbol("BOOL");
            }
            binaryInstr->result = resultVar;
            if(block->blockList.size() == 0){
                block->instrList.push_back(binaryInstr);
            }else{
                block->blockList[block->blockList.size() - 1]->instrList.push_back(binaryInstr);
            }
            node.ret = resultVar;
        }
        node.is_lvalue = true;
        return block;
    }

    std::shared_ptr<IRBlock> visit(ExprOpunary &node){
        auto block = std::make_shared<IRBlock>();
        if(node.op == DEREFERENCE){
            node.right->is_lvalue = true;
            auto rightInstrs = visit(*node.right);
            if(rightInstrs){
                if(rightInstrs->blockList.empty()){
                    for(auto & instr : rightInstrs->instrList){
                        block->instrList.push_back(instr);
                    }
                }else{
                    for(auto &instr : rightInstrs->instrList){
                        block->instrList.push_back(instr);
                    }
                    for(auto &blk: rightInstrs->blockList){
                        block->blockList.push_back(blk);
                    }
                }
            }
            node.ret = node.right->ret;
        }else if(node.op == NOT){
            auto rightInstrs = visit(*node.right);
            if(rightInstrs){
                for(auto & instr : rightInstrs->instrList){
                    block->instrList.push_back(instr);
                }
                if(rightInstrs->blockList.size()){
                    for(auto &blk: rightInstrs->blockList){
                        block->blockList.push_back(blk);
                    }
                }
            }
            auto right = node.right->ret;
            if(auto rightRet = std::dynamic_pointer_cast<IRVar>(right)){
                auto res = std::make_shared<IRVar>();
                res->type = currentScope->lookupTypeSymbol("BOOL");
                auto eqInstr = std::make_shared<IRBinaryop>();
                eqInstr->leftValue = rightRet;
                eqInstr->rightValue = std::make_shared<IRLiteral>(INT_LITERAL, 0);
                eqInstr->result = res;
                eqInstr->op = EQ;
                if(rightRet->type == currentScope->lookupTypeSymbol("bool")){
                    eqInstr->i8tag = true;
                }
                if(block->blockList.empty()){
                    block->instrList.push_back(eqInstr);
                }else{
                    block->blockList[block->blockList.size() - 1]->instrList.push_back(eqInstr);
                }
                node.ret = res;
                node.is_lvalue = true;
            }
        }else if(node.op == NEGATE){
            auto rightInstrs = visit(*node.right);
            if(rightInstrs){
                if(rightInstrs->blockList.empty()){
                    for(auto & instr : rightInstrs->instrList){
                        block->instrList.push_back(instr);
                    }
                }else{
                    for(auto &instr : rightInstrs->instrList){
                        block->instrList.push_back(instr);
                    }
                    for(auto &blk: rightInstrs->blockList){
                        block->blockList.push_back(blk);
                    }
                }
            }
            auto right = node.right->ret;
            if(auto *rightLiteral = dynamic_cast<IRLiteral *>(& *right)){
                auto res = std::make_shared<IRLiteral>(INT_LITERAL, - rightLiteral->intValue);
                node.ret = res;
                node.is_lvalue = true;
            }else{
                if(auto rightRet = std::dynamic_pointer_cast<IRVar>(right)){ 
                    auto subInstr = std::make_shared<IRBinaryop>();
                    subInstr->leftValue = std::make_shared<IRLiteral>(INT_LITERAL, 0);
                    subInstr->rightValue = rightRet;
                    subInstr->op = SUB;
                    auto resultVar = std::make_shared<IRVar>();
                    resultVar->type = rightRet->type;
                    subInstr->result = resultVar;
                    if(block->blockList.empty()){
                        block->instrList.push_back(subInstr);
                    }else{
                        block->blockList[block->blockList.size() - 1]->instrList.push_back(subInstr);
                    }
                    node.ret = resultVar;
                    node.is_lvalue = true;
                }
            }
        }else if(node.op == BORROW){
            node.right->is_lvalue = true;
            auto rightInstrs = visit(*node.right);
            if(rightInstrs){
                if(rightInstrs->blockList.empty()){
                    for(auto & instr : rightInstrs->instrList){
                        block->instrList.push_back(instr);
                    }
                }else{
                    for(auto &instr : rightInstrs->instrList){
                        block->instrList.push_back(instr);
                    }
                    for(auto &blk: rightInstrs->blockList){
                        block->blockList.push_back(blk);
                    }
                }
            }
            node.ret = node.right->ret;
        }
        return block;
    }

    std::shared_ptr<IRBlock> visit(ExprPath &node){
        std::shared_ptr<IRBlock> block = std::make_shared<IRBlock>();
        if(node.pathFirst->pathSegments.type == IDENTIFIER && node.pathSecond == nullptr){
            std::string varName = node.pathFirst->pathSegments.identifier;
            auto varSymbol = currentScope->lookupValueSymbol(varName);
            if(varSymbol){
                node.ret = varSymbol;
            }
            auto constSymbol = currentScope->lookupConstantSymbol(varName);
            if(constSymbol.type != "null"){
                node.ret = std::make_shared<IRLiteral>(INT_LITERAL, constSymbol.value);
            }
            auto funcSymbol = currentScope->lookupFunctionSymbol(varName);
            if(funcSymbol){
                node.ret = funcSymbol;
            }
            auto typeSymbol = currentScope->lookupTypeSymbol(varName);
            if(typeSymbol){
                node.ret = typeSymbol;
            }
        }else if(node.pathSecond){
            std::string structName = node.pathFirst->pathSegments.identifier;
            if(auto *structTypeSymbol = currentScope->lookupTypeSymbol(structName).get()){
                if(auto *structType = dynamic_cast<IRStructType *>(& *structTypeSymbol)){
                    for(int i = 0;i < structType->memberFunctions.size();i ++){
                        if(structType->memberFunctions[i]->name == node.pathSecond->pathSegments.identifier){
                            node.ret = structType->memberFunctions[i];
                            break;
                        }
                    }
                }
            }
        }else if(node.pathFirst->pathSegments.type == SELF){
            auto selfVar = currentScope->lookupValueSymbol("self");
            node.ret = selfVar;
        }
        return block;
    }

    std::shared_ptr<IRBlock> visit(ExprReturn &node){
        //need special judge
        auto block = std::make_shared<IRBlock>();
        if(node.expr){
            bool origin = node.expr->is_lvalue;
            auto rightInstr1 = visit(*node.expr);
            node.expr->is_lvalue = origin;
            if(auto var = std::dynamic_pointer_cast<IRVar>(node.expr->ret)){
                if(auto *structType = dynamic_cast<IRStructType *>(& *var->type)){
                    node.expr->is_lvalue = true;
                }
            }
            auto rightInstr = visit(*node.expr);
            if(rightInstr){
                for(auto & instr : rightInstr->instrList){
                    block->instrList.push_back(instr);
                }
                if(rightInstr->blockList.size()){
                    for(auto & blk : rightInstr->blockList){
                        block->blockList.push_back(blk);
                    }
                }
            }
            auto res = node.expr->ret;
            bool isReturn = true;
            if(auto *irVar = dynamic_cast<IRVar *>(& *node.expr->ret)){
                if(auto *structTP = dynamic_cast<IRStructType *>(& *irVar->type)){
                    isReturn = false;
                }
            }
            if(isReturn){
                auto returnInstr = std::make_shared<IRReturn>();
                if(auto irVar = std::dynamic_pointer_cast<IRVar>(res)){
                    if(irVar->type == currentScope->lookupTypeSymbol("BOOL")){
                        //need zext
                        auto zextVar = std::make_shared<IRVar>();
                        zextVar->type = currentScope->lookupTypeSymbol("bool");
                        auto zextInstr = std::make_shared<IRZext>();
                        zextInstr->originalType = irVar->type;
                        zextInstr->targetType = currentScope->lookupTypeSymbol("bool");
                        zextInstr->value = irVar;
                        zextInstr->result = zextVar;
                        if(block->blockList.empty()){
                            block->instrList.push_back(zextInstr);
                        }else{
                            block->blockList[block->blockList.size() - 1]->instrList.push_back(zextInstr);
                        }
                        returnInstr->returnType = currentScope->lookupTypeSymbol("bool");
                        returnInstr->returnValue = zextVar;
                    }else{
                        returnInstr->returnType = irVar->type;
                        returnInstr->returnValue = irVar;
                    }
                }else if(auto irLiteral = std::dynamic_pointer_cast<IRLiteral>(res)){
                    if(irLiteral->literalType == BOOL_LITERAL){
                        returnInstr->returnType = currentScope->lookupTypeSymbol("bool");
                    }else{
                        returnInstr->returnType = currentScope->lookupTypeSymbol("i32");
                    }
                    returnInstr->returnLiteral = irLiteral;
                }
                if(block->blockList.empty()){
                    block->instrList.push_back(returnInstr);
                }else{
                    block->blockList[block->blockList.size() - 1]->instrList.push_back(returnInstr);
                }
            }
            node.ret = res;
        }else{
            auto returnInstr = std::make_shared<IRReturn>();
            returnInstr->returnType = std::make_shared<IRVoidType>();
            returnInstr->returnValue = std::make_shared<IRVar>();
            block->instrList.push_back(returnInstr);
            node.ret = nullptr;
        }
        node.is_lvalue = true;
        return block;
    }

    std::shared_ptr<IRBlock> visit(ExprStruct &node){
        auto block = std::make_shared<IRBlock>();
        node.pathInExpr->is_lvalue = true;
        auto structPath = visit(*node.pathInExpr);
        if(structPath){
            for(auto & instr : structPath->instrList){
                block->instrList.push_back(instr);
            }
            if(structPath->blockList.size()){
                for(auto & blk : structPath->blockList){
                    block->blockList.push_back(blk);
                }
            }
        }
        auto structType = node.pathInExpr->ret;
        if(auto p = std::dynamic_pointer_cast<IRType>(structType)){
            auto structVar = std::make_shared<IRVar>();
            structVar->type = p;
            auto memsetInstr = std::make_shared<IRMemset>();
            memsetInstr->dest = structVar;
            memsetInstr->value = 0;
            memsetInstr->size = p->size;
            if(block->blockList.empty()){
                block->instrList.push_back(std::make_shared<IRAlloca>(p, structVar));
                block->instrList.push_back(memsetInstr);
            }else{
                block->blockList[block->blockList.size() - 1]->instrList.push_back(std::make_shared<IRAlloca>(p, structVar));
                block->blockList[block->blockList.size() - 1]->instrList.push_back(memsetInstr);
            }
            if(auto *q = dynamic_cast<IRStructType *>(& *p)){
                for(auto & fieldInit : node.structExprFields){
                    std::string fieldName = fieldInit.identifier;
                    for(int i = 0;i < q->memberTypes.size();i ++){
                        if(fieldName == q->memberTypes[i].first){
                            if(auto *cuttenrType = dynamic_cast<IRStructType *>(& *q->memberTypes[i].second)){
                                fieldInit.expr->is_lvalue = true;
                            }
                            auto initInstrs = visit(*fieldInit.expr);
                            if(initInstrs){
                                if(block->blockList.empty()){
                                    for(auto & instr : initInstrs->instrList){
                                        block->instrList.push_back(instr);
                                    }
                                    for(auto & blk : initInstrs->blockList){
                                        block->blockList.push_back(blk);
                                    }
                                }else{
                                    for(auto & instr : initInstrs->instrList){
                                        block->blockList[block->blockList.size() - 1]->instrList.push_back(instr);
                                    }
                                    for(auto & blk : initInstrs->blockList){
                                        block->blockList.push_back(blk);
                                    }
                                }
                            }
                            auto getptrInstr = std::make_shared<IRGetptr>();
                            getptrInstr->type = p;
                            getptrInstr->offset = i;
                            getptrInstr->base = structVar;
                            auto ptrres = std::make_shared<IRVar>();
                            ptrres->type = q->memberTypes[i].second;
                            getptrInstr->res = ptrres;
                            if(auto initLiteral = std::dynamic_pointer_cast<IRLiteral>(fieldInit.expr->ret)){
                                auto storeInstr = std::make_shared<IRStore>();
                                storeInstr->storeLiteral = initLiteral;
                                storeInstr->valueType = q->memberTypes[i].second;
                                storeInstr->address = ptrres;
                                if(block->blockList.empty()){
                                    block->instrList.push_back(getptrInstr);
                                    block->instrList.push_back(storeInstr);
                                }else{
                                    block->blockList[block->blockList.size() - 1]->instrList.push_back(getptrInstr);
                                    block->blockList[block->blockList.size() - 1]->instrList.push_back(storeInstr);
                                }
                            }else if(auto initVar = std::dynamic_pointer_cast<IRVar>(fieldInit.expr->ret)){
                                if(auto *intType = dynamic_cast<IRIntType *>(& *q->memberTypes[i].second)){
                                    auto storeInstr = std::make_shared<IRStore>();
                                    storeInstr->valueType = q->memberTypes[i].second;
                                    storeInstr->storeValue = initVar;
                                    storeInstr->address = ptrres;
                                    if(block->blockList.empty()){
                                        block->instrList.push_back(getptrInstr);
                                        block->instrList.push_back(storeInstr);
                                    }else{
                                        block->blockList[block->blockList.size() - 1]->instrList.push_back(getptrInstr);
                                        block->blockList[block->blockList.size() - 1]->instrList.push_back(storeInstr);
                                    }
                                }else{
                                    auto memcpyInstr = std::make_shared<IRMemcpy>();
                                    memcpyInstr->dest = ptrres;
                                    memcpyInstr->value = initVar;
                                    memcpyInstr->size = q->memberTypes[i].second->size;
                                    if(block->blockList.empty()){
                                        block->instrList.push_back(getptrInstr);
                                        block->instrList.push_back(memcpyInstr);
                                    }else{
                                        block->blockList[block->blockList.size() - 1]->instrList.push_back(getptrInstr);
                                        block->blockList[block->blockList.size() - 1]->instrList.push_back(memcpyInstr);
                                    }
                                }
                            }
                            break;
                        }
                    }
                }
            }
            node.ret = structVar;
        }
        node.is_lvalue = true;
        return block;
    }

    std::shared_ptr<IRBlock> visit(ExprUnderscore &node){
        return nullptr;
    }
    
    //Item 
    std::shared_ptr<IRNode> visit(Item &node){
        if(auto *p = dynamic_cast<ItemConstDecl *>(& node)) {
            return visit(*p);
        }else if(auto *p = dynamic_cast<ItemEnumDecl *>(& node)) {
            return visit(*p);
        }else if(auto *p = dynamic_cast<ItemFnDecl *>(& node)) {
            return visit(*p);
        }else if(auto *p = dynamic_cast<ItemImplDecl *>(& node)) {
            return visit(*p);
        }else if(auto *p = dynamic_cast<ItemStructDecl *>(& node)) {    
            return visit(*p);
        }else if(auto *p = dynamic_cast<ItemTraitDecl *>(& node)) {
            return visit(*p);
        }else{
            throw std::runtime_error("IRBuilder visit Item error");
        }
    }

    std::shared_ptr<IRNode> visit(ItemConstDecl &node){
        return nullptr;
    }

    std::shared_ptr<IRNode> visit(ItemEnumDecl &node){
        return nullptr;
    }

    void caculateStructSize(std::shared_ptr<IRStructType> structType){
        int totalSize = 0;
        for(auto & member : structType->memberTypes){
            totalSize += member.second->size;
        }
        structType->size = totalSize;
    }

    // function param not adding to func irscope here
    std::shared_ptr<IRFunction> visit(ItemFnDecl &node,std::shared_ptr<IRType> structSelfType = nullptr){
        auto currentIRFunc = currentScope->lookupFunctionSymbol(node.identifier);
        auto funcScope = std::make_shared<IRScope>();
        funcScope->parent = currentScope;
        currentScope->children.push_back(funcScope);
        currentScope = funcScope;
        if(!currentIRFunc){
            if(auto *p = dynamic_cast<IRStructType *>(& *structSelfType)){
                for(int i = 0;i < p->memberFunctions.size();i++){
                    if(p->memberFunctions[i]->name == node.identifier){
                        currentIRFunc = p->memberFunctions[i];
                        break;
                    }
                }
            }
        }
        for(int i = 0;i < currentIRFunc->paramList->paramList.size();i++){
            auto param = currentIRFunc->paramList->paramList[i];
            if(auto p = std::dynamic_pointer_cast<IRVar>(param)){
                auto bodyVar = std::make_shared<IRVar>();
                bodyVar->varName = p->varName;
                bodyVar->reName = p->reName;
                bodyVar->type = p->type;
                if(auto *structType = dynamic_cast<IRStructType *>(& *p->type)){
                    currentIRFunc->body->instrList.push_back(std::make_shared<IRAlloca>(std::make_shared<IRPtrType>(p->type), bodyVar));
                    currentIRFunc->body->instrList.push_back(std::make_shared<IRStore>(std::make_shared<IRPtrType>(p->type), p, nullptr, bodyVar));
                    currentScope->addValueSymbol(p->varName, p);
                }else if(auto *arrayType = dynamic_cast<IRArrayType *>(& *p->type)){
                    currentIRFunc->body->instrList.push_back(std::make_shared<IRAlloca>(std::make_shared<IRPtrType>(p->type), bodyVar));
                    currentIRFunc->body->instrList.push_back(std::make_shared<IRStore>(std::make_shared<IRPtrType>(p->type), p, nullptr, bodyVar));
                    currentScope->addValueSymbol(p->varName, p);
                }else if(auto *ptrType = dynamic_cast<IRPtrType *>(& *p->type)){
                    currentIRFunc->body->instrList.push_back(std::make_shared<IRAlloca>(p->type, bodyVar));
                    currentIRFunc->body->instrList.push_back(std::make_shared<IRStore>(p->type, p, nullptr, bodyVar));
                    p->type = ptrType->baseType;
                    currentScope->addValueSymbol(p->varName, p);
                }else{
                    currentIRFunc->body->instrList.push_back(std::make_shared<IRAlloca>(p->type, bodyVar));
                    currentIRFunc->body->instrList.push_back(std::make_shared<IRStore>(p->type, p, nullptr, bodyVar));
                    currentScope->addValueSymbol(p->varName, bodyVar);
                }
            }
        }
        if(node.fnBody){
            for(auto & stmt : node.fnBody->statements){
                if(auto *itemStmt = dynamic_cast<StmtItem *>(& *stmt)){
                    if(auto *p = dynamic_cast<ItemConstDecl *>(& *itemStmt->stmt_item)){
                        constInfo info;
                        if(auto *tp = dynamic_cast<Type *>(& *p->type)){
                            if(tp->type == U32){
                                info.type = "u32";
                            }else if(tp->type == I32){
                                info.type = "i32";
                            }else if(tp->type == USIZE){
                                info.type = "usize";
                            }else if(tp->type == ISIZE){
                                info.type = "isize";
                            }
                        }
                        info.value = p->value;
                        currentScope->addConstantSymbol(p->identifier, info);
                    }else if(auto *p = dynamic_cast<ItemEnumDecl *>(& *itemStmt->stmt_item)){
                    }else if(auto *p = dynamic_cast<ItemFnDecl *>(& *itemStmt->stmt_item)){
                        std::shared_ptr<IRType> returnType = nullptr;
                        if(p->returnType){
                            returnType = resolveType(*p->returnType);
                        }else{
                            returnType = std::make_shared<IRVoidType>();
                        }
                        std::string funcName = p->identifier;
                        std::shared_ptr<IRParam> irParam =  std::make_shared<IRParam>();
                        std::vector<std::shared_ptr<IRType>> typeList;
                        if(node.fnParameters.SelfParam.isShortSelf){
                            if(node.fnParameters.SelfParam.short_self.is_and){
                                auto selfParam = std::make_shared<IRVar>();
                                selfParam->varName = "self";
                                selfParam->reName  = "self";
                                selfParam->type = std::make_shared<IRPtrType>(structSelfType);
                                typeList.push_back(selfParam->type);
                                irParam->paramList.push_back(selfParam);
                            }else{
                                auto selfParam = std::make_shared<IRVar>();
                                selfParam->varName = "self";
                                selfParam->reName  = "self";
                                selfParam->type = structSelfType;
                                typeList.push_back(selfParam->type);
                                irParam->paramList.push_back(selfParam);
                            }
                        }
                        if(!p->fnParameters.FunctionParam.empty()){
                            for(auto & param : p->fnParameters.FunctionParam){
                                auto currentVar = std::make_shared<IRVar>();
                                if(auto *q = dynamic_cast<PatternIdentifier *>(& *param.pattern)){
                                    currentVar->varName = q->identifier;
                                }else if(auto *q = dynamic_cast<PatternReference *>(& *param.pattern)){
                                    if(auto *r = dynamic_cast<PatternIdentifier *>(& *q->patternWithoutRange)){
                                        currentVar->varName = r->identifier;
                                    }
                                }
                                if(vars_cnt.find(currentVar->varName) != vars_cnt.end()){
                                    vars_cnt[currentVar->varName] += 1;
                                    currentVar->reName = currentVar->varName + "_" + std::to_string(vars_cnt[currentVar->varName]);
                                }else{
                                    vars_cnt[currentVar->varName] = 1;
                                    currentVar->reName = currentVar->varName;
                                }
                                if(param.type){
                                    currentVar->type = resolveType(*param.type);
                                    typeList.push_back(currentVar->type);
                                }
                                irParam->paramList.push_back(currentVar);
                            }
                        }
                        if(!returnType){
                            returnType = currentScope->lookupTypeSymbol("void");
                        }else{
                            if(auto *p = dynamic_cast<IRStructType *>(& *returnType)){
                                auto ptrVar = std::make_shared<IRVar>();
                                ptrVar->varName = "ret_ptr";
                                ptrVar->reName = "ret_ptr";
                                ptrVar->type = std::make_shared<IRPtrType>(returnType);
                                irParam->paramList.push_back(ptrVar);
                            }
                        }
                        auto currentFunction = std::make_shared<IRFunction>();
                        currentFunction->name = funcName;
                        currentFunction->retType = returnType;
                        currentFunction->paramList = irParam;
                        currentFunction->typeList = typeList;
                        currentScope->addFunctionSymbol(funcName, currentFunction);
                    }else if(auto *p = dynamic_cast<ItemImplDecl *>(& *itemStmt->stmt_item)){
                    }else if(auto *p = dynamic_cast<ItemStructDecl *>(& *itemStmt->stmt_item)){
                        std::vector<std::pair<std::string,std::shared_ptr<IRType>>> fieldTypes;
                        std::string structName = p->identifier;
                        for(auto & field : p->item_struct){
                            if(field.structElem){
                                fieldTypes.push_back({field.identifier, resolveType(*field.structElem)});
                            }
                        }
                        auto currentStruct = std::make_shared<IRStructType>();
                        currentStruct->name = structName;
                        currentStruct->true_name = structName;
                        currentStruct->memberTypes = fieldTypes;
                        caculateStructSize(currentStruct);
                        currentScope->addTypeSymbol(structName, currentStruct);
                    }else if(auto *p = dynamic_cast<ItemTraitDecl *>(& *itemStmt)){
                    }
                }
            }
        }
        if(node.fnBody){
            for(int i = 0;i < node.fnBody->statements.size();i++){
                auto & stmt = node.fnBody->statements[i];
                if(auto *p = dynamic_cast<StmtExpr *>(& *stmt)){
                    if(auto *q = dynamic_cast<ExprIf *>(& *p->stmtExpr)){
                        auto IfBlocks = std::make_shared<IRBlock>();
                        if(auto *rettp = dynamic_cast<IRStructType *>(& *currentIRFunc->retType)){
                            if(auto retvar = std::dynamic_pointer_cast<IRVar>(currentIRFunc->paramList->paramList[currentIRFunc->paramList->paramList.size() -1])){
                                IfBlocks = visit(*q, retvar);
                            }
                        }else{
                            IfBlocks = visit(*q);
                        }
                        if(IfBlocks->blockList.size() > 0){
                            auto lastIfBlock = IfBlocks->blockList[IfBlocks->blockList.size() - 1];
                            if(lastIfBlock->instrList.empty()){
                                if(!node.fnBody->ExpressionWithoutBlock && i == node.fnBody->statements.size() -1){
                                    if(auto *tp = dynamic_cast<IRIntType *>(& *currentIRFunc->retType)){
                                        lastIfBlock->instrList.push_back(std::make_shared<IRReturn>(currentIRFunc->retType, std::make_shared<IRLiteral>(INT_LITERAL, 0)));
                                    }
                                }
                            }
                        }
                        if(currentIRFunc->body->blockList.size() == 0){
                            for(auto &instr: IfBlocks->instrList){
                                currentIRFunc->body->instrList.push_back(instr);
                            }
                            for(auto & block : IfBlocks->blockList){
                                currentIRFunc->body->blockList.push_back(block);
                            }
                        }else{
                            auto lastBlock = currentIRFunc->body->blockList[currentIRFunc->body->blockList.size() - 1];
                            for(auto & instr : IfBlocks->instrList){
                                lastBlock->instrList.push_back(instr);
                            }
                            for(auto & block : IfBlocks->blockList){
                                currentIRFunc->body->blockList.push_back(block);
                            }
                        }
                    }else if(auto *q = dynamic_cast<ExprLoop *>(& *p->stmtExpr)){
                        auto LoopBlocks = visit(*q);
                        if(currentIRFunc->body->blockList.size() == 0){
                            for(auto &instr: LoopBlocks->instrList){
                                currentIRFunc->body->instrList.push_back(instr);
                            }
                            for(auto & block : LoopBlocks->blockList){
                                currentIRFunc->body->blockList.push_back(block);
                            }
                        }else{
                            auto lastBlock = currentIRFunc->body->blockList[currentIRFunc->body->blockList.size() - 1];
                            for(auto & instr : LoopBlocks->instrList){
                                lastBlock->instrList.push_back(instr);
                            }
                            for(auto & block : LoopBlocks->blockList){
                                currentIRFunc->body->blockList.push_back(block);
                            }
                        }
                    }else if(auto *retStruct = dynamic_cast<ExprStruct *>(& *p->stmtExpr)){
                        auto structInstrs = visit(*retStruct);
                        if(structInstrs){
                            if(currentIRFunc->body->blockList.size() == 0){
                                for(auto & instr : structInstrs->instrList){
                                    currentIRFunc->body->instrList.push_back(instr);
                                }
                                for(auto & blk : structInstrs->blockList){
                                    currentIRFunc->body->blockList.push_back(blk);
                                }
                            }else{
                                for(auto & instr : structInstrs->instrList){
                                    currentIRFunc->body->blockList[currentIRFunc->body->blockList.size() - 1]->instrList.push_back(instr);
                                }
                                for(auto & blk : structInstrs->blockList){
                                    currentIRFunc->body->blockList.push_back(blk);
                                }
                            }
                        }
                        auto memcpyInstr = std::make_shared<IRMemcpy>();
                        memcpyInstr->size = currentIRFunc->retType->size;
                        if(auto retVar = std::dynamic_pointer_cast<IRVar>(retStruct->ret)){
                            memcpyInstr->value = retVar;
                        }
                        memcpyInstr->dest = std::dynamic_pointer_cast<IRVar>(currentIRFunc->paramList->paramList[currentIRFunc->paramList->paramList.size() -1]);
                        if(currentIRFunc->body->blockList.size() == 0){
                            currentIRFunc->body->instrList.push_back(memcpyInstr);
                            currentIRFunc->body->instrList.push_back(std::make_shared<IRReturn>(std::make_shared<IRVoidType>(),std::make_shared<IRVar>()));
                        }else{
                            currentIRFunc->body->blockList[currentIRFunc->body->blockList.size() - 1]->instrList.push_back(memcpyInstr);
                            currentIRFunc->body->blockList[currentIRFunc->body->blockList.size() - 1]->instrList.push_back(std::make_shared<IRReturn>(std::make_shared<IRVoidType>(),std::make_shared<IRVar>()));
                        }
                    }else{
                        if(auto *retStmt = dynamic_cast<ExprReturn *>(& *p->stmtExpr)){
                            auto returnInstrs = visit(*retStmt);
                            if(returnInstrs){
                                if(currentIRFunc->body->blockList.size() == 0){
                                    for(auto & instr : returnInstrs->instrList){
                                        currentIRFunc->body->instrList.push_back(instr);
                                    }
                                    for(auto & blk : returnInstrs->blockList){
                                        currentIRFunc->body->blockList.push_back(blk);
                                    }
                                }else{
                                    for(auto & instr : returnInstrs->instrList){
                                        currentIRFunc->body->blockList[currentIRFunc->body->blockList.size() - 1]->instrList.push_back(instr);
                                    }
                                    for(auto & blk : returnInstrs->blockList){
                                        currentIRFunc->body->blockList.push_back(blk);
                                    }
                                }
                            }
                            if(auto *retType = dynamic_cast<IRStructType *>(& *currentIRFunc->retType)){
                                auto memcpyInstr = std::make_shared<IRMemcpy>();
                                memcpyInstr->size = currentIRFunc->retType->size;
                                if(auto retVar = std::dynamic_pointer_cast<IRVar>(retStmt->expr->ret)){
                                    memcpyInstr->value = retVar;
                                }
                                memcpyInstr->dest = std::dynamic_pointer_cast<IRVar>(currentIRFunc->paramList->paramList[currentIRFunc->paramList->paramList.size() -1]);
                                if(currentIRFunc->body->blockList.size() == 0){
                                    currentIRFunc->body->instrList.push_back(memcpyInstr);
                                    currentIRFunc->body->instrList.push_back(std::make_shared<IRReturn>(std::make_shared<IRVoidType>(),std::make_shared<IRVar>()));
                                }else{
                                    currentIRFunc->body->blockList[currentIRFunc->body->blockList.size() - 1]->instrList.push_back(memcpyInstr);
                                    currentIRFunc->body->blockList[currentIRFunc->body->blockList.size() - 1]->instrList.push_back(std::make_shared<IRReturn>(std::make_shared<IRVoidType>(),std::make_shared<IRVar>()));
                                }
                            }
                        }else{
                            auto exprInstrs = visit(*p->stmtExpr);
                            if(exprInstrs){
                                if(currentIRFunc->body->blockList.size() == 0){
                                    for(auto & instr : exprInstrs->instrList){
                                        currentIRFunc->body->instrList.push_back(instr);
                                    }
                                    for(auto & blk : exprInstrs->blockList){
                                        currentIRFunc->body->blockList.push_back(blk);
                                    }
                                }else{
                                    for(auto & instr : exprInstrs->instrList){
                                        currentIRFunc->body->blockList[currentIRFunc->body->blockList.size() - 1]->instrList.push_back(instr);
                                    }
                                    for(auto & blk : exprInstrs->blockList){
                                        currentIRFunc->body->blockList.push_back(blk);
                                    }
                                }
                            }
                        }
                    }
                }else if(auto *p = dynamic_cast<StmtLet *>(& *stmt)){
                    auto letInstrs = visit(*p);
                    if(letInstrs){
                        if(currentIRFunc->body->blockList.size() == 0){
                            for(auto & instr : letInstrs->instrList){
                                currentIRFunc->body->instrList.push_back(instr);
                            }
                            for(auto & blk : letInstrs->blockList){
                                currentIRFunc->body->blockList.push_back(blk);
                            }
                        }else{
                            for(auto & instr : letInstrs->instrList){
                                currentIRFunc->body->blockList[currentIRFunc->body->blockList.size() - 1]->instrList.push_back(instr);
                            }
                            for(auto & blk : letInstrs->blockList){
                                currentIRFunc->body->blockList.push_back(blk);
                            }
                        }
                    }
                }else if(auto *p = dynamic_cast<StmtItem *>(& *stmt)){
                    if(auto *q = dynamic_cast<ItemFnDecl *>(& *p->stmt_item)){
                        auto funcDecl = visit(*q);
                        currentIRFunc->funcList.push_back(std::dynamic_pointer_cast<IRFunction>(funcDecl));
                    }else if(auto *q = dynamic_cast<ItemStructDecl *>(& *p->stmt_item)){
                        auto structDecl = visit(*q);
                        currentIRFunc->typeList.push_back(std::dynamic_pointer_cast<IRStructType>(structDecl));
                    }
                }
            }
            if(node.fnBody->ExpressionWithoutBlock){
                if(auto *structTP = dynamic_cast<IRStructType *>(& *currentIRFunc->retType)){
                    node.fnBody->ExpressionWithoutBlock->is_lvalue = true;
                }
                auto exprInstrs = visit(*node.fnBody->ExpressionWithoutBlock);
                if(exprInstrs){
                    if(currentIRFunc->body->blockList.size() == 0){
                        for(auto & instr : exprInstrs->instrList){
                            currentIRFunc->body->instrList.push_back(instr);
                        }
                        for(auto & blk : exprInstrs->blockList){
                            currentIRFunc->body->blockList.push_back(blk);
                        }
                    }else{
                        for(auto & instr : exprInstrs->instrList){
                            currentIRFunc->body->blockList[currentIRFunc->body->blockList.size() - 1]->instrList.push_back(instr);
                        }
                        for(auto & blk : exprInstrs->blockList){
                            currentIRFunc->body->blockList.push_back(blk);
                        }
                    }
                }
                if(auto *retType = dynamic_cast<IRIntType *>(& *currentIRFunc->retType)){
                    auto returnInstr = std::make_shared<IRReturn>();
                    returnInstr->returnType = currentIRFunc->retType;
                    if(auto retVar = std::dynamic_pointer_cast<IRVar>(node.fnBody->ExpressionWithoutBlock->ret)){
                        returnInstr->returnValue = retVar;
                    }else if(auto retLiteral = std::dynamic_pointer_cast<IRLiteral>(node.fnBody->ExpressionWithoutBlock->ret)){
                        returnInstr->returnLiteral = retLiteral;
                    }
                    if(currentIRFunc->body->blockList.size() == 0){
                        currentIRFunc->body->instrList.push_back(returnInstr);
                    }else{
                        currentIRFunc->body->blockList[currentIRFunc->body->blockList.size() - 1]->instrList.push_back(returnInstr);
                    }
                }else{
                    auto memcpyInstr = std::make_shared<IRMemcpy>();
                    memcpyInstr->size = currentIRFunc->retType->size;
                    if(auto retVar = std::dynamic_pointer_cast<IRVar>(node.fnBody->ExpressionWithoutBlock->ret)){
                        memcpyInstr->value = retVar;
                    }
                    memcpyInstr->dest = std::dynamic_pointer_cast<IRVar>(currentIRFunc->paramList->paramList[currentIRFunc->paramList->paramList.size() -1]);
                    if(currentIRFunc->body->blockList.size() == 0){
                        currentIRFunc->body->instrList.push_back(memcpyInstr);
                        currentIRFunc->body->instrList.push_back(std::make_shared<IRReturn>(std::make_shared<IRVoidType>(),std::make_shared<IRVar>()));
                    }else{
                        currentIRFunc->body->blockList[currentIRFunc->body->blockList.size() - 1]->instrList.push_back(memcpyInstr);
                        currentIRFunc->body->blockList[currentIRFunc->body->blockList.size() - 1]->instrList.push_back(std::make_shared<IRReturn>(std::make_shared<IRVoidType>(),std::make_shared<IRVar>()));
                    }
                }
            }else if(currentIRFunc->name != "main"){
                if(auto *voidtp = dynamic_cast<IRVoidType *>(& *currentIRFunc->retType)){
                    if(auto *retInstr = dynamic_cast<ExprReturn *>(& *node.fnBody->statements[node.fnBody->statements.size() - 1])){
                        //
                    }else{
                        if(currentIRFunc->body->blockList.size() == 0){
                            currentIRFunc->body->instrList.push_back(std::make_shared<IRReturn>(std::make_shared<IRVoidType>(),std::make_shared<IRVar>()));
                        }else{
                            currentIRFunc->body->blockList[currentIRFunc->body->blockList.size() - 1]->instrList.push_back(std::make_shared<IRReturn>(std::make_shared<IRVoidType>(),std::make_shared<IRVar>()));
                        }
                    }
                }
            }
        }
        currentScope = currentScope->parent;
        if(currentIRFunc->name == "main"){
            if(currentIRFunc->body->blockList.size() == 0){
                currentIRFunc->body->instrList.push_back(std::make_shared<IRReturn>(currentScope->lookupTypeSymbol("i32"), std::make_shared<IRLiteral>(INT_LITERAL, 0)));
            }else{
                currentIRFunc->body->blockList[currentIRFunc->body->blockList.size() - 1]->instrList.push_back(std::make_shared<IRReturn>(currentScope->lookupTypeSymbol("i32"), std::make_shared<IRLiteral>(INT_LITERAL, 0)));
            }
        }else if(currentIRFunc->body->blockList.size() > 0){
            auto lastBlock = currentIRFunc->body->blockList[currentIRFunc->body->blockList.size() - 1];
            if(lastBlock->instrList.size() == 0){
                if(auto *rettype = dynamic_cast<IRIntType *>(& *currentIRFunc->retType)){
                    lastBlock->instrList.push_back(std::make_shared<IRReturn>(currentIRFunc->retType, std::make_shared<IRLiteral>(INT_LITERAL, 0)));
                }else{
                    lastBlock->instrList.push_back(std::make_shared<IRReturn>(std::make_shared<IRVoidType>(), std::make_shared<IRLiteral>(INT_LITERAL, 0)));
                }
            }
        }
        
        return currentIRFunc;
    }


    std::shared_ptr<IRImpl> visit(ItemImplDecl &node){
        std::shared_ptr<IRImpl> implNode = std::make_shared<IRImpl>();
        if(auto *p = dynamic_cast<Path *>(& *node.targetType)){
            if(p->pathSegments.type == IDENTIFIER){
                std::string structName = p->pathSegments.identifier;
                auto Type = currentScope->lookupTypeSymbol(structName);
                if(Type){
                    int j = 0;
                    if(auto *structType = dynamic_cast<IRStructType *>(& *Type)){
                        implNode->mainStructType = Type;
                        for(int i = 0;i < structType->memberFunctions.size();i ++){
                            if(node.item_trait_fn[j]->identifier == structType->memberFunctions[i]->name){
                                structType->memberFunctions[i] = visit(*node.item_trait_fn[j], Type);
                                implNode->functions.push_back(structType->memberFunctions[i]);
                                j ++;
                            }
                        }
                    }
                }
            }
        }
        return implNode;
    }

    std::shared_ptr<IRNode> visit(ItemStructDecl &node){
        auto currentStruct = currentScope->lookupTypeSymbol(node.identifier);
        return currentStruct;
    }

    std::shared_ptr<IRNode> visit(ItemTraitDecl &node){
        // no need to do anything
        return nullptr;
    }

    //Pattern
    void visit(Pattern &node){
        if(auto *p = dynamic_cast<PatternIdentifier *>(& node)) {
            visit(*p);
        }else if(auto *p = dynamic_cast<PatternLiteral *>(& node)) {
            visit(*p);
        }else if(auto *p = dynamic_cast<PatternPath *>(& node)) {
            visit(*p);
        }else if(auto *p = dynamic_cast<PatternReference *>(& node)) {
            visit(*p);
        }else if(auto *p = dynamic_cast<PatternWildCard *>(& node)) {   
            visit(*p);
        }else{
            throw std::runtime_error("IRBuilder visit Pattern error");
        }
    }
    void visit(PatternIdentifier &node);
    void visit(PatternLiteral &node);
    void visit(PatternPath &node);
    void visit(PatternReference &node);
    void visit(PatternWildCard &node);

    //Statement
    std::shared_ptr<IRBlock> visit(Statement &node){
        if(auto *p = dynamic_cast<StmtEmpty *>(& node)) {
            return visit(*p);
        }else if(auto *p = dynamic_cast<StmtExpr *>(& node)) {
            return visit(*p);
        }else if(auto *p = dynamic_cast<StmtItem *>(& node)) {
            return visit(*p);
        }else if(auto *p = dynamic_cast<StmtLet *>(& node)) {
            return visit(*p);
        }else{
            throw std::runtime_error("IRBuilder visit Statement error");
        }
    }

    std::shared_ptr<IRBlock> visit(StmtEmpty &node){
        return nullptr;
    }

    std::shared_ptr<IRBlock> visit(StmtExpr &node){
        return nullptr;
    }

    std::shared_ptr<IRBlock> visit(StmtItem &node){
        return nullptr;
    }

    std::shared_ptr<IRBlock> visit(StmtLet &node){
        auto block = std::make_shared<IRBlock>();
        std::string varName;
        std::string reName;
        if(auto *p = dynamic_cast<PatternIdentifier *>(& *node.PatternNoTopAlt)){
            varName = p->identifier;
        }else if(auto *p = dynamic_cast<PatternReference *>(& *node.PatternNoTopAlt)){
            if(auto *q = dynamic_cast<PatternIdentifier *>(& *p->patternWithoutRange)){
                varName = q->identifier;
            }
        }
        if(vars_cnt.find(varName) != vars_cnt.end()){
            vars_cnt[varName] += 1;
            reName = varName + "_" + std::to_string(vars_cnt[varName]);
        }else{
            vars_cnt[varName] = 1;
            reName = varName;
        }
        std::shared_ptr<IRType> varType = resolveType(*node.type);
        auto currentVar = std::make_shared<IRVar>(varType,varName, reName);
        //currentScope->addValueSymbol(varName, currentVar);
        block->instrList.push_back(std::make_shared<IRAlloca>(varType,currentVar));
        //todo init expr
        if(node.expression){
            if(auto *ifExpr = dynamic_cast<ExprIf *>(& *node.expression)){
                return processLetIf(node);
            }else{
                if(auto *tp = dynamic_cast<IRStructType *>(& *varType)){
                    node.expression->is_lvalue = true;
                }
                auto exprInstrs = visit(*node.expression);
                if(exprInstrs){
                    for(auto & instr : exprInstrs->instrList){
                        block->instrList.push_back(instr);
                    }
                    if(exprInstrs->blockList.size() >0){
                        for(auto &blk: exprInstrs->blockList){
                            block->blockList.push_back(blk);
                        }
                    }
                }
                if(auto *intType = dynamic_cast<IRIntType *>(& *varType)){
                    auto storeInstr = std::make_shared<IRStore>();
                    storeInstr->valueType = varType;
                    if(auto literal = std::dynamic_pointer_cast<IRLiteral>(node.expression->ret)){
                        storeInstr->storeLiteral = literal;
                    }else if(auto var = std::dynamic_pointer_cast<IRVar>(node.expression->ret)){
                        if(var->type == currentScope->lookupTypeSymbol("BOOL")){
                            auto zextInstr = std::make_shared<IRZext>();
                            zextInstr->originalType = currentScope->lookupTypeSymbol("BOOL");
                            zextInstr->targetType = currentVar->type;
                            zextInstr->value = var;
                            auto zextVar = std::make_shared<IRVar>();
                            zextVar->type = currentVar->type;
                            zextInstr->result = zextVar;
                            if(block->blockList.size() ==0){
                                block->instrList.push_back(zextInstr);
                            }else{
                                block->blockList[block->blockList.size() -1]->instrList.push_back(zextInstr);
                            }
                            storeInstr->storeValue = zextVar;
                        }else{
                            storeInstr->storeValue = var;
                        }
                    }
                    storeInstr->address = currentVar;
                    if(block->blockList.size() ==0){
                        block->instrList.push_back(storeInstr);
                    }else{
                        block->blockList[block->blockList.size() -1]->instrList.push_back(storeInstr);
                    }
                }else{
                    auto memcpyInstr = std::make_shared<IRMemcpy>();
                    memcpyInstr->dest = currentVar;
                    if(auto var = std::dynamic_pointer_cast<IRVar>(node.expression->ret)){
                        memcpyInstr->value = var;
                    }
                    memcpyInstr->size = varType->size;
                    if(block->blockList.size() ==0){
                        block->instrList.push_back(memcpyInstr);
                    }else{
                        block->blockList[block->blockList.size() -1]->instrList.push_back(memcpyInstr);
                    }
                }
            }
        }
        currentScope->addValueSymbol(varName, currentVar);
        return block;
    }

    std::shared_ptr<IRBlock> processLetIf(StmtLet &node){
        auto block = std::make_shared<IRBlock>();
        std::string varName;
        std::string reName;
        if(auto *p = dynamic_cast<PatternIdentifier *>(& *node.PatternNoTopAlt)){
            varName = p->identifier;
        }else if(auto *p = dynamic_cast<PatternReference *>(& *node.PatternNoTopAlt)){
            if(auto *q = dynamic_cast<PatternIdentifier *>(& *p->patternWithoutRange)){
                varName = q->identifier;
            }
        }
        if(vars_cnt.find(varName) != vars_cnt.end()){
            vars_cnt[varName] += 1;
            reName = varName + "_" + std::to_string(vars_cnt[varName]);
        }else{
            vars_cnt[varName] = 1;
            reName = varName;
        }
        std::shared_ptr<IRType> varType = resolveType(*node.type);
        auto currentVar = std::make_shared<IRVar>(varType,varName, reName);
        currentScope->addValueSymbol(varName, currentVar);
        block->instrList.push_back(std::make_shared<IRAlloca>(varType,currentVar));
        if(auto *ifExpr = dynamic_cast<ExprIf *>(& *node.expression)){
            auto ifBlocks = letIf(*ifExpr, currentVar);
            for(auto & instr : ifBlocks->instrList){
                block->instrList.push_back(instr);
            }
            if(ifBlocks->blockList.size() >0){
                for(auto &blk: ifBlocks->blockList){
                    block->blockList.push_back(blk);
                }
            }
        }
        return block;
    }

    std::shared_ptr<IRBlock> letIf(ExprIf &node, std::shared_ptr<IRVar> currentVar){
        auto block = std::make_shared<IRBlock>();
        auto condBlock = std::make_shared<IRBlock>();
        auto condVar = std::make_shared<IRVar>();
        auto condInstrs = visit(*node.condition);
        if(condInstrs){
            for(auto & instr : condInstrs->instrList){
                condBlock->instrList.push_back(instr);
            }
            if(condInstrs->blockList.size() >0){
                for(auto &blk: condInstrs->blockList){
                    condBlock->blockList.push_back(blk);
                }
            }
            if(auto var = std::dynamic_pointer_cast<IRVar>(node.condition->ret)){
                if(var->type == currentScope->lookupTypeSymbol("BOOL")){
                    condVar = var;
                }else{
                    auto cmpInstr = std::make_shared<IRBinaryop>();
                    cmpInstr->op = NEQ;
                    cmpInstr->leftValue = var;
                    cmpInstr->rightValue = std::make_shared<IRLiteral>(INT_LITERAL, 0);
                    auto cmpvar = std::make_shared<IRVar>();
                    cmpvar->type = currentScope->lookupTypeSymbol("BOOL");
                    cmpInstr->result = cmpvar;
                    if(var->type == currentScope->lookupTypeSymbol("bool")){
                        cmpInstr->i8tag = true;
                    }
                    condBlock->instrList.push_back(cmpInstr);
                    condVar = cmpvar;
                }
            }
        }
        for(auto & instr : condBlock->instrList){
            block->instrList.push_back(instr);
        }
        for(auto & blk : condBlock->blockList){
            block->blockList.push_back(blk);
        }
        auto thenBlock = std::make_shared<IRBlock>();
        if(node.thenBlock){
            if(auto *tp = dynamic_cast<IRStructType *>(& *currentVar->type)){
                node.thenBlock->ExpressionWithoutBlock->is_lvalue = true;
            }
            auto thenInstrs = visit(*node.thenBlock->ExpressionWithoutBlock);
            if(thenInstrs){
                for(auto & instr : thenInstrs->instrList){
                    thenBlock->instrList.push_back(instr);
                }
                if(thenInstrs->blockList.size() >0){
                    for(auto &blk: thenInstrs->blockList){
                        thenBlock->blockList.push_back(blk);
                    }
                }
            }
            if(auto *intType = dynamic_cast<IRIntType *>(& *currentVar->type)){
                auto storeInstr = std::make_shared<IRStore>();
                storeInstr->valueType = currentVar->type;
                if(auto literal = std::dynamic_pointer_cast<IRLiteral>(node.thenBlock->ExpressionWithoutBlock->ret)){
                    storeInstr->storeLiteral = literal;
                }else if(auto var = std::dynamic_pointer_cast<IRVar>(node.thenBlock->ExpressionWithoutBlock->ret)){
                    storeInstr->storeValue = var;
                }
                storeInstr->address = currentVar;
                thenBlock->instrList.push_back(storeInstr);
            }else{
                auto memcpyInstr = std::make_shared<IRMemcpy>();
                memcpyInstr->dest = currentVar;
                if(auto var = std::dynamic_pointer_cast<IRVar>(node.thenBlock->ExpressionWithoutBlock->ret)){
                    memcpyInstr->value = var;   
                }
                memcpyInstr->size = currentVar->type->size;
                thenBlock->instrList.push_back(memcpyInstr);
            }
        }
        auto elseBlock = std::make_shared<IRBlock>();
        if(node.elseBlock){
            if(auto *elseblk = dynamic_cast<ExprBlock *>(& *node.elseBlock)){
                if(auto *tp = dynamic_cast<IRStructType *>(& *currentVar->type)){
                    elseblk->ExpressionWithoutBlock->is_lvalue = true;
                }
                auto elseInstrs = visit(*elseblk->ExpressionWithoutBlock);
                if(elseInstrs){
                    for(auto & instr : elseInstrs->instrList){
                        elseBlock->instrList.push_back(instr);
                    }
                    if(elseInstrs->blockList.size() >0){
                        for(auto &blk: elseInstrs->blockList){
                            elseBlock->blockList.push_back(blk);
                        }
                    }
                }
                if(auto *intType = dynamic_cast<IRIntType *>(& *currentVar->type)){
                    auto storeInstr = std::make_shared<IRStore>();
                    storeInstr->valueType = currentVar->type;
                    if(auto literal = std::dynamic_pointer_cast<IRLiteral>(elseblk->ExpressionWithoutBlock->ret)){
                        storeInstr->storeLiteral = literal;
                    }else if(auto var = std::dynamic_pointer_cast<IRVar>(elseblk->ExpressionWithoutBlock->ret)){
                        storeInstr->storeValue = var;
                    }
                    storeInstr->address = currentVar;
                    elseBlock->instrList.push_back(storeInstr);
                }else{
                    auto memcpyInstr = std::make_shared<IRMemcpy>();
                    memcpyInstr->dest = currentVar;
                    if(auto var = std::dynamic_pointer_cast<IRVar>(elseblk->ExpressionWithoutBlock->ret)){
                        memcpyInstr->value = var;   
                    }
                    memcpyInstr->size = currentVar->type->size;
                    elseBlock->instrList.push_back(memcpyInstr);
                }
            }else if(auto *ifelse = dynamic_cast<ExprIf *>(& *node.elseBlock)){
                auto blk = letIf(*ifelse, currentVar);
                for(auto & instr : blk->instrList){
                    elseBlock->instrList.push_back(instr);
                }
                if(blk->blockList.size() >0){
                    for(auto &blk2: blk->blockList){
                        elseBlock->blockList.push_back(blk2);
                    }
                }
            }
        }
        auto mergeBlock = std::make_shared<IRBlock>();
        if(block->blockList.size() ==0){
            block->instrList.push_back(std::make_shared<IRBr>(condVar, thenBlock, elseBlock));
        }else{
            block->blockList[block->blockList.size() -1]->instrList.push_back(std::make_shared<IRBr>(condVar, thenBlock, elseBlock));
        }
        block->blockList.push_back(thenBlock);
        for(auto &blk : thenBlock->blockList){
            block->blockList.push_back(blk);
        }
        if(thenBlock->blockList.size() == 0){
            thenBlock->instrList.push_back(std::make_shared<IRBr>(mergeBlock));
        }else{
            thenBlock->blockList[thenBlock->blockList.size() -1]->instrList.push_back(std::make_shared<IRBr>(mergeBlock));
        }
        block->blockList.push_back(elseBlock);
        for(auto &blk : elseBlock->blockList){
            block->blockList.push_back(blk);
        }
        if(elseBlock->blockList.size() == 0){
            elseBlock->instrList.push_back(std::make_shared<IRBr>(mergeBlock));
        }else{
            elseBlock->blockList[elseBlock->blockList.size() -1]->instrList.push_back(std::make_shared<IRBr>(mergeBlock));
        }
        block->blockList.push_back(mergeBlock);
        return block;
    }

    //Type
    std::shared_ptr<IRType> resolveType(ASTNode &node){
        if(auto *p = dynamic_cast<Type *>(& node)){
            return visit(*p);
        }else if(auto *p = dynamic_cast<TypeArray *>(& node)){
            return visit(*p);
        }else if(auto *p = dynamic_cast<Path *>(& node)){
            return visit(*p);
        }else if(auto *p = dynamic_cast<TypeReference *>(& node)){
            return visit(*p);
        }else if(auto *p = dynamic_cast<TypeUnit *>(& node)){
            return visit(*p);
        }
        throw std::runtime_error("IRBuilder resolveType error");
    }

    std::shared_ptr<IRIntType> visit(Type &node){
        if(node.type == I32){
            return std::dynamic_pointer_cast<IRIntType>(currentScope->lookupTypeSymbol("i32"));
        }else if(node.type == U32){
            return std::dynamic_pointer_cast<IRIntType>(currentScope->lookupTypeSymbol("u32"));
        }else if(node.type == ISIZE){
            return std::dynamic_pointer_cast<IRIntType>(currentScope->lookupTypeSymbol("isize"));
        }else if(node.type == USIZE){
            return std::dynamic_pointer_cast<IRIntType>(currentScope->lookupTypeSymbol("usize"));
        }else if(node.type == BOOL){
            return std::dynamic_pointer_cast<IRIntType>(currentScope->lookupTypeSymbol("bool"));
        }
        throw std::runtime_error("IRBuilder visit Type error: unknown primitive type");
    }

    void caculateArraySize(std::shared_ptr<IRArrayType> arrayType){
        if(auto *innerArray = dynamic_cast<IRArrayType *>(& *arrayType->elementType)){
            caculateArraySize(std::dynamic_pointer_cast<IRArrayType>(arrayType->elementType));
            arrayType->size = innerArray->size * arrayType->length;
        }else{
            arrayType->size = arrayType->elementType->size * arrayType->length;
        }
    }
    
    std::shared_ptr<IRArrayType> visit(TypeArray &node){
        auto currentType = std::make_shared<IRType>();
        int size = 0;
        if(node.type){
            currentType = resolveType(*node.type);
        }
        if(node.expr){
            if(auto *literal = dynamic_cast<ExprLiteral *>(& *node.expr)){
                size = literal->integer;
            }else if(auto *path = dynamic_cast<ExprPath *>(& *node.expr)){
                if(path->pathFirst->pathSegments.type == IDENTIFIER){
                    std::string constName = path->pathFirst->pathSegments.identifier;
                    constInfo res = currentScope->lookupConstantSymbol(constName);
                    size = res.value;
                }
            }else if(auto *opbinary = dynamic_cast<ExprOpbinary *>(& *node.expr)){
                if(opbinary->op == PLUS){
                    if(auto *left = dynamic_cast<ExprPath *>(& *opbinary->left)){
                        if(left->pathFirst->pathSegments.type == IDENTIFIER){
                            std::string constName = left->pathFirst->pathSegments.identifier;
                            constInfo res = currentScope->lookupConstantSymbol(constName);
                            size += res.value;
                        }
                    }else if(auto *leftLiteral = dynamic_cast<ExprLiteral *>(& *opbinary->left)){
                        size += leftLiteral->integer;
                    }
                    if(auto *right = dynamic_cast<ExprPath *>(& *opbinary->right)){
                        if(right->pathFirst->pathSegments.type == IDENTIFIER){
                            std::string constName = right->pathFirst->pathSegments.identifier;
                            constInfo res = currentScope->lookupConstantSymbol(constName);
                            size += res.value;
                        }
                    }else if(auto *rightLiteral = dynamic_cast<ExprLiteral *>(& *opbinary->right)){
                        size += rightLiteral->integer;
                    }
                }else if(opbinary->op == MINUS){
                    if(auto *left = dynamic_cast<ExprPath *>(& *opbinary->left)){
                        if(left->pathFirst->pathSegments.type == IDENTIFIER){
                            std::string constName = left->pathFirst->pathSegments.identifier;
                            constInfo res = currentScope->lookupConstantSymbol(constName);
                            size += res.value;
                        }
                    }else if(auto *leftLiteral = dynamic_cast<ExprLiteral *>(& *opbinary->left)){
                        size += leftLiteral->integer;
                    }
                    if(auto *right = dynamic_cast<ExprPath *>(& *opbinary->right)){
                        if(right->pathFirst->pathSegments.type == IDENTIFIER){
                            std::string constName = right->pathFirst->pathSegments.identifier;
                            constInfo res = currentScope->lookupConstantSymbol(constName);
                            size -= res.value;
                        }
                    }else if(auto *rightLiteral = dynamic_cast<ExprLiteral *>(& *opbinary->right)){
                        size -= rightLiteral->integer;
                    }
                }
            }
        }
        auto arrayType = std::make_shared<IRArrayType>(currentType,size);
        caculateArraySize(arrayType);
        return arrayType;
    }

    std::shared_ptr<IRStructType> visit(Path &node){
        if(node.pathSegments.type == IDENTIFIER){
            std::string typeName = node.pathSegments.identifier;
            auto Type = currentScope->lookupTypeSymbol(typeName);
            if(Type){
                return std::dynamic_pointer_cast<IRStructType>(Type);
            }
        }
        throw std::runtime_error("IRBuilder visit Path error: unknown type path");
    }

    std::shared_ptr<IRPtrType> visit(TypeReference &node){
        auto refType = std::make_shared<IRPtrType>();
        if(node.typeNoBounds){
            refType->baseType = resolveType(*node.typeNoBounds);
        }
        return refType;
    }

    std::shared_ptr<IRVoidType> visit(TypeUnit &node){
        return std::dynamic_pointer_cast<IRVoidType>(currentScope->lookupTypeSymbol("void"));
    }
};

}