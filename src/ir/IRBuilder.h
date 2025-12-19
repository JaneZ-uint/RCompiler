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
#include "IRParam.h"
#include "IRRoot.h"
#include "IRStore.h"
#include "IRType.h"
#include "IRSelf.h"
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
#include "IRGlobalbuilder.h"
#include <memory>
#include <map>
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
        //may left with some special functions like print exit...
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
    std::vector<std::shared_ptr<IRNode>> visit(Expression &node){
        if(auto *p = dynamic_cast<ExprArray *>(& node)) {
            return visit(*p);
        }else if(auto *p = dynamic_cast<ExprBlock *>(& node)) {
            return visit(*p);
        }else if(auto *p = dynamic_cast<ExprBreak *>(& node)) {
            return visit(*p);
        }else if(auto *p = dynamic_cast<ExprCall *>(& node)) {
            return visit(*p);
        }else if(auto *p = dynamic_cast<ExprConstBlock *>(& node)) {
            return visit(*p);
        }else if(auto *p = dynamic_cast<ExprContinue *>(& node)) {
            return visit(*p);
        }else if(auto *p = dynamic_cast<ExprField *>(& node)) {
            return visit(*p);
        }else if(auto *p = dynamic_cast<ExprGroup *>(& node)) {
            return visit(*p);
        // }else if(auto *p = dynamic_cast<ExprIf *>(& node)) {
        //     return visit(*p);
        // 
        }else if(auto *p = dynamic_cast<ExprIndex *>(& node)) {
            return visit(*p);
        }else if(auto *p = dynamic_cast<ExprLiteral *>(& node)) {
            return visit(*p);
        // }else if(auto *p = dynamic_cast<ExprLoop *>(& node)) {
        //     return visit(*p);
        // 
        }else if(auto *p = dynamic_cast<ExprMatch *>(& node)) {
            return visit(*p);
        }else if(auto *p = dynamic_cast<ExprMethodcall *>(& node)) {
            return visit(*p);
        }else if(auto *p = dynamic_cast<ExprOpbinary *>(& node)) {
            return visit(*p);
        }else if(auto *p = dynamic_cast<ExprOpunary *>(& node)) {
            return visit(*p);
        }else if(auto *p = dynamic_cast<ExprPath *>(& node)) {
            return visit(*p);
        }else if(auto *p = dynamic_cast<ExprReturn *>(& node)) {
            return visit(*p);
        }else if(auto *p = dynamic_cast<ExprStruct *>(& node)) {
            return visit(*p);
        }else if(auto *p = dynamic_cast<ExprUnderscore *>(& node)) {
            return visit(*p);
        }else{
            throw std::runtime_error("IRBuilder visit Expression error");
        }
    }
    std::vector<std::shared_ptr<IRNode>> visit(ExprArray &node){
        return {};
    }

    std::vector<std::shared_ptr<IRNode>> visit(ExprBlock &node){
        return {};
    }

    std::vector<std::shared_ptr<IRNode>> visit(ExprBreak &node){
        std::vector<std::shared_ptr<IRNode>> instrs;
        instrs.push_back(std::make_shared<IRBreak>());
        return instrs;
    }

    std::vector<std::shared_ptr<IRNode>> visit(ExprCall &node){
        std::vector<std::shared_ptr<IRNode>> instrs;
        std::string funcName = "";
        if(auto *p = dynamic_cast<ExprPath *>(& *node.expr)){
            if(p->pathFirst->pathSegments.type == IDENTIFIER){
                funcName = p->pathFirst->pathSegments.identifier;
            }
        }
        if(funcName == "exit"){
            //todo exit special handling
            auto exitInstr = std::make_shared<IRExit>();
            instrs.push_back(exitInstr);
            return instrs;
        }
        if(funcName == "printlnInt"){
            for(auto &arg :node.callParams){
                //todo
            }
        }
        if(funcName == ""){
            std::string structName = "";
            if(auto *p = dynamic_cast<ExprPath *>(& *node.expr)){
                if(p->pathSecond->pathSegments.type == IDENTIFIER){
                    funcName = p->pathSecond->pathSegments.identifier;
                }
                if(p->pathFirst->pathSegments.type == IDENTIFIER){
                    structName = p->pathFirst->pathSegments.identifier;
                }
                auto currentStruct = currentScope->lookupTypeSymbol(structName);
                if(auto *implType = dynamic_cast<IRStructType *>(& *currentStruct)){
                    //find impl
                    
                }
            }
        }
        auto currentIRFunc = currentScope->lookupFunctionSymbol(funcName);
        auto currentCallInstr = std::make_shared<IRCall>();
        currentCallInstr->function = currentIRFunc;
        auto callRet = std::make_shared<IRVar>();
        callRet->type = currentIRFunc->retType;
        currentCallInstr->retVar = callRet;
        currentCallInstr->pList =  std::make_shared<IRParam>();
        for(auto & arg : node.callParams){
            //TODO process arguments
            if(auto *p = dynamic_cast<ExprPath *>(& *arg)){
                if(p->pathFirst->pathSegments.type == IDENTIFIER){
                    std::string varName = p->pathFirst->pathSegments.identifier;
                    auto varSymbol = currentScope->lookupValueSymbol(varName);
                    //TODO load instruction
                    if(varSymbol == nullptr){
                        //constant
                        constInfo res = currentScope->lookupConstantSymbol(varName);
                        currentCallInstr->pList->paramList.push_back(std::make_shared<IRLiteral>(INT_LITERAL, res.value));
                        continue;
                    }
                    auto currentParamVar = std::make_shared<IRVar>();
                    currentParamVar->varName = varSymbol->varName;
                    if(vars_cnt.find(currentParamVar->varName) != vars_cnt.end()){
                        vars_cnt[currentParamVar->varName] += 1;
                        currentParamVar->reName = currentParamVar->varName + "_" + std::to_string(vars_cnt[currentParamVar->varName]);
                    }else{
                        vars_cnt[currentParamVar->varName] = 1;
                        currentParamVar->reName = currentParamVar->varName;
                    }
                    currentParamVar->type = varSymbol->type;
                    instrs.push_back(std::make_shared<IRLoad>(currentParamVar, varSymbol,varSymbol->type));
                    currentCallInstr->pList->paramList.push_back(currentParamVar);
                }
            }else if(auto *p = dynamic_cast<ExprLiteral *>(& *arg)){
                if(p->type == INTEGER_LITERAL){
                    currentCallInstr->pList->paramList.push_back(std::make_shared<IRLiteral>(INT_LITERAL, p->integer));
                }
            }else if(auto *p = dynamic_cast<ExprOpbinary *>(& *arg)){
                //todo
            }
        }
        instrs.push_back(currentCallInstr);
        return instrs;
    }

    std::vector<std::shared_ptr<IRNode>> visit(ExprConstBlock &node){
        return {};
    }

    std::vector<std::shared_ptr<IRNode>> visit(ExprContinue &node){
        std::vector<std::shared_ptr<IRNode>> instrs;
        instrs.push_back(std::make_shared<IRContinue>());
        return instrs;
    }

    std::vector<std::shared_ptr<IRNode>> visit(ExprField &node){
        std::vector<std::shared_ptr<IRNode>> instrs;
        if(auto *p = dynamic_cast<ExprPath *>(& *node.expr)){
            if(p->pathFirst->pathSegments.type == IDENTIFIER){
                std::string varName = p->pathFirst->pathSegments.identifier;
                auto currentVar = currentScope->lookupValueSymbol(varName);
                //todo load and getfield
                if(auto *structType = dynamic_cast<IRStructType *>(& *currentVar->type)){
                    std::string fieldName = node.identifier;
                    for(int i = 0; i < structType->memberTypes.size(); i++){
                        if(structType->memberTypes[i].first == fieldName){
                            if(auto *type = dynamic_cast<IRIntType *>(& *structType->memberTypes[i].second)){     
                                auto loadedVar = std::make_shared<IRVar>();
                                loadedVar->type = structType->memberTypes[i].second;
                                instrs.push_back(std::make_shared<IRGetptr>(currentVar->type, currentVar,loadedVar,i));
                            }else if(auto *type = dynamic_cast<IRArrayType *>(& *structType->memberTypes[i].second)){
                                // a.b[0] 结构体成员是数组
                                auto loadedVar = std::make_shared<IRVar>();
                                loadedVar->type = structType->memberTypes[i].second;
                                instrs.push_back(std::make_shared<IRGetptr>(currentVar->type, currentVar,loadedVar,i));
                                auto indexVar = std::make_shared<IRVar>();

                            }
                        }
                    }
                }
            }
        }
        return instrs;
    }

    std::vector<std::shared_ptr<IRNode>> visit(ExprGroup &node){
        return {};
    }

    std::shared_ptr<IRBlock> visit(ExprIf &node){
        auto ifBlock = std::make_shared<IRBlock>();
        std::vector<std::shared_ptr<IRBlock>> blocks;
        std::vector<std::shared_ptr<IRNode>> instrs;
        //todo condition
        auto condVar = std::make_shared<IRVar>();
        if(node.condition){
            if(auto *p = dynamic_cast<ExprOpbinary *>(& *node.condition)){
                auto condInstrs = visit(*p);
                for(auto & instr : condInstrs){
                    instrs.push_back(instr);
                }
                auto lastInstr = condInstrs[condInstrs.size() - 1];
                if(auto *q = dynamic_cast<IRBinaryop *>(& *lastInstr)){
                    condVar = q->result;
                }
            }else if(auto *p = dynamic_cast<ExprPath *>(& *node.condition)){
                if(p->pathFirst->pathSegments.type == IDENTIFIER){
                    std::string varName = p->pathFirst->pathSegments.identifier;
                    auto currentVar = currentScope->lookupValueSymbol(varName);
                    //todo trunc
                    auto tmp = std::make_shared<IRVar>();
                    instrs.push_back(std::make_shared<IRLoad>(tmp, currentVar, currentVar->type));
                    instrs.push_back(std::make_shared<IRTrunc>(currentVar->type, tmp, currentScope->lookupTypeSymbol("BOOL"), condVar));
                }
            }else if(auto *p = dynamic_cast<ExprCall *>(& *node.condition)){
                auto condInstrs = visit(*p);
                for(auto & instr : condInstrs){
                    instrs.push_back(instr);
                }
                auto lastInstr = condInstrs[condInstrs.size() - 1];
                if(auto *q = dynamic_cast<IRCall *>(& *lastInstr)){
                    condVar = q->retVar;
                }
            }
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
                            auto nestedIfBlock = visit(*ifExpr);
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
                        if(thenBlock->blockList.empty()){
                            for(auto & instr : stmtInstrs){
                                thenBlock->instrList.push_back(instr);
                            }
                        }else{
                            auto lastBlock = thenBlock->blockList[thenBlock->blockList.size() - 1];
                            for(auto & instr : stmtInstrs){
                                lastBlock->instrList.push_back(instr);
                            }
                        }
                        if(auto *returnExpr = dynamic_cast<ExprReturn *>(& *exprStmt->stmtExpr)){
                            isThenReturn = true;
                        }
                    }
                }else if(auto *letStmt = dynamic_cast<StmtLet *>(& *stmt)){
                    auto stmtInstrs = visit(*letStmt);
                    if(thenBlock->blockList.empty()){
                        for(auto & instr : stmtInstrs){
                            thenBlock->instrList.push_back(instr);
                        }
                    }else{
                        auto lastBlock = thenBlock->blockList[thenBlock->blockList.size() - 1];
                        for(auto & instr : stmtInstrs){
                            lastBlock->instrList.push_back(instr);
                        }
                    }
                }
            }
            if(node.thenBlock->ExpressionWithoutBlock){
                isThenReturn = true;
                if(auto *returnExpr = dynamic_cast<ExprPath *>(& *node.thenBlock->ExpressionWithoutBlock)){
                    if(returnExpr->pathFirst->pathSegments.type == IDENTIFIER){
                        std::string varName = returnExpr->pathFirst->pathSegments.identifier;
                        auto currentVar = currentScope->lookupValueSymbol(varName);
                        auto retVar = std::make_shared<IRVar>();
                        retVar->type = currentVar->type;
                        if(thenBlock->blockList.empty()){
                            thenBlock->instrList.push_back(std::make_shared<IRLoad>(retVar, currentVar, currentVar->type));
                            thenBlock->instrList.push_back(std::make_shared<IRReturn>(retVar->type,retVar));
                        }else{
                            auto lastBlock = thenBlock->blockList[thenBlock->blockList.size() - 1];
                            lastBlock->instrList.push_back(std::make_shared<IRLoad>(retVar, currentVar, currentVar->type));
                            lastBlock->instrList.push_back(std::make_shared<IRReturn>(retVar->type,retVar));
                        }
                    }
                }else if(auto *returnExpr = dynamic_cast<ExprLiteral *>(& *node.thenBlock->ExpressionWithoutBlock)){
                    if(returnExpr->type == INTEGER_LITERAL){
                        auto retVar = std::make_shared<IRVar>();
                        retVar->type = currentScope->lookupTypeSymbol("i32");
                        if(thenBlock->blockList.empty()){
                            thenBlock->instrList.push_back(std::make_shared<IRReturn>(retVar->type,std::make_shared<IRLiteral>(INT_LITERAL, returnExpr->integer)));
                        }else{
                            auto lastBlock = thenBlock->blockList[thenBlock->blockList.size() - 1];
                            lastBlock->instrList.push_back(std::make_shared<IRReturn>(retVar->type,std::make_shared<IRLiteral>(INT_LITERAL, returnExpr->integer)));
                        }
                    }
                }else if(auto *returnExpr = dynamic_cast<ExprOpbinary *>(& *node.thenBlock->ExpressionWithoutBlock)){
                    auto stmtInstrs = visit(*returnExpr);
                    if(thenBlock->blockList.empty()){
                        for(auto & instr : stmtInstrs){
                            thenBlock->instrList.push_back(instr);
                        }
                        auto lastInstr = stmtInstrs[stmtInstrs.size() - 1];
                        if(auto *q = dynamic_cast<IRBinaryop *>(& *lastInstr)){
                            thenBlock->instrList.push_back(std::make_shared<IRReturn>(q->result->type,q->result));
                        }
                    }else{
                        auto lastBlock = thenBlock->blockList[thenBlock->blockList.size() - 1];
                        for(auto & instr : stmtInstrs){
                            lastBlock->instrList.push_back(instr);
                        }
                        auto lastInstr = stmtInstrs[stmtInstrs.size() - 1];
                        if(auto *q = dynamic_cast<IRBinaryop *>(& *lastInstr)){
                            lastBlock->instrList.push_back(std::make_shared<IRReturn>(q->result->type,q->result));
                        }
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
                auto elseIfBlock = visit(*elseIfExpr);
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
                                auto nestedIfBlock = visit(*ifExpr);
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
                            if(elseBlock->blockList.empty()){
                                for(auto & instr : stmtInstrs){
                                    elseBlock->instrList.push_back(instr);
                                }
                            }else{
                                auto lastBlock = elseBlock->blockList[elseBlock->blockList.size() - 1];
                                for(auto & instr : stmtInstrs){
                                    lastBlock->instrList.push_back(instr);
                                }
                            }
                            if(auto *returnExpr = dynamic_cast<ExprReturn *>(& *exprStmt->stmtExpr)){
                                isElseBlock = true;
                            }
                        }
                    }else if(auto *letStmt = dynamic_cast<StmtLet *>(& *stmt)){
                        auto stmtInstrs = visit(*letStmt);
                        if(elseBlock->blockList.empty()){
                            for(auto & instr : stmtInstrs){
                                elseBlock->instrList.push_back(instr);
                            }
                        }else{
                            auto lastBlock = elseBlock->blockList[elseBlock->blockList.size() - 1];
                            for(auto & instr : stmtInstrs){
                                lastBlock->instrList.push_back(instr);
                            }
                        }
                    }
                }
                // todo exoression without block required here
                if(blockExpr->ExpressionWithoutBlock){
                    isElseBlock = true;
                    if(auto *returnExpr = dynamic_cast<ExprPath *>(& *blockExpr->ExpressionWithoutBlock)){
                        if(returnExpr->pathFirst->pathSegments.type == IDENTIFIER){
                            std::string varName = returnExpr->pathFirst->pathSegments.identifier;
                            auto currentVar = currentScope->lookupValueSymbol(varName);
                            auto retVar = std::make_shared<IRVar>();
                            retVar->type = currentVar->type;
                            if(elseBlock->blockList.empty()){
                                elseBlock->instrList.push_back(std::make_shared<IRLoad>(retVar, currentVar, currentVar->type));
                                elseBlock->instrList.push_back(std::make_shared<IRReturn>(retVar->type,retVar));
                            }else{
                                auto lastBlock = elseBlock->blockList[elseBlock->blockList.size() - 1];
                                lastBlock->instrList.push_back(std::make_shared<IRLoad>(retVar, currentVar, currentVar->type));
                                lastBlock->instrList.push_back(std::make_shared<IRReturn>(retVar->type,retVar));
                            }
                        }
                    }else if(auto *returnExpr = dynamic_cast<ExprLiteral *>(& *blockExpr->ExpressionWithoutBlock)){
                        if(returnExpr->type == INTEGER_LITERAL){
                            auto retVar = std::make_shared<IRVar>();
                            retVar->type = currentScope->lookupTypeSymbol("i32");
                            if(elseBlock->blockList.empty()){
                                elseBlock->instrList.push_back(std::make_shared<IRReturn>(retVar->type,std::make_shared<IRLiteral>(INT_LITERAL, returnExpr->integer)));
                            }else{
                                auto lastBlock = elseBlock->blockList[elseBlock->blockList.size() - 1];
                                lastBlock->instrList.push_back(std::make_shared<IRReturn>(retVar->type,std::make_shared<IRLiteral>(INT_LITERAL, returnExpr->integer)));
                            }
                        }
                    }else if(auto *returnExpr = dynamic_cast<ExprOpbinary *>(& *blockExpr->ExpressionWithoutBlock)){
                        auto stmtInstrs = visit(*returnExpr);
                        if(elseBlock->blockList.empty()){
                            for(auto & instr : stmtInstrs){
                                elseBlock->instrList.push_back(instr);
                            }
                            auto lastInstr = stmtInstrs[stmtInstrs.size() - 1];
                            if(auto *q = dynamic_cast<IRBinaryop *>(& *lastInstr)){
                                elseBlock->instrList.push_back(std::make_shared<IRReturn>(q->result->type,q->result));
                            }
                        }else{
                            auto lastBlock = elseBlock->blockList[elseBlock->blockList.size() - 1];
                            for(auto & instr : stmtInstrs){
                                lastBlock->instrList.push_back(instr);
                            }
                            auto lastInstr = stmtInstrs[stmtInstrs.size() - 1];
                            if(auto *q = dynamic_cast<IRBinaryop *>(& *lastInstr)){
                                lastBlock->instrList.push_back(std::make_shared<IRReturn>(q->result->type,q->result));
                            }
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
            instrs.push_back(std::make_shared<IRBr>(condVar, thenBlock, blocks[thenBlock->blockList.size() + 1]));
        }else{
            instrs.push_back(std::make_shared<IRBr>(condVar, thenBlock, returnBlock));
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

    std::vector<std::shared_ptr<IRNode>> visit(ExprIndex &node){
        std::vector<std::shared_ptr<IRNode>> instrs;
        if(auto *p = dynamic_cast<ExprPath *>(& *node.name)){
            if(p->pathFirst->pathSegments.type == IDENTIFIER){
                std::string varName = p->pathFirst->pathSegments.identifier;
                auto currentVar = currentScope->lookupValueSymbol(varName);
                //todo load and getindex
                if(auto *type = dynamic_cast<IRArrayType *>(& *currentVar->type)){
                    //getindex
                    if(auto *indexExpr = dynamic_cast<ExprLiteral *>(& *node.index)){
                        if(indexExpr->type == INTEGER_LITERAL){
                            auto res = std::make_shared<IRVar>();
                            res->type = type->elementType;
                            instrs.push_back(std::make_shared<IRGetptr>(currentVar->type, currentVar,res,indexExpr->integer));
                        }
                    }else{
                        if(auto *indexExpr = dynamic_cast<ExprOpbinary *>(& *node.index)){
                            auto indexInstrs = visit(*indexExpr);
                            for(auto & instr : indexInstrs){
                                instrs.push_back(instr);
                            }
                            auto lastInstr = indexInstrs[indexInstrs.size() - 1];
                            if(auto *q = dynamic_cast<IRBinaryop *>(& *lastInstr)){
                                auto indexVar = q->result;
                                auto res = std::make_shared<IRVar>();
                                res->type = type->elementType;
                                instrs.push_back(std::make_shared<IRGetptr>(currentVar->type, currentVar,res,-1,indexVar));
                            }
                        }else if(auto *indexExpr = dynamic_cast<ExprPath *>(& *node.index)){
                            if(indexExpr->pathFirst->pathSegments.type == IDENTIFIER){
                                std::string indexVarName = indexExpr->pathFirst->pathSegments.identifier;
                                auto indexVarSymbol = currentScope->lookupValueSymbol(indexVarName);
                                if(indexVarSymbol){
                                    auto indexLoadedVar = std::make_shared<IRVar>();
                                    indexLoadedVar->type = indexVarSymbol->type;
                                    instrs.push_back(std::make_shared<IRLoad>(indexLoadedVar, indexVarSymbol,indexVarSymbol->type));
                                    auto res = std::make_shared<IRVar>();
                                    res->type = type->elementType;
                                    instrs.push_back(std::make_shared<IRGetptr>(currentVar->type, currentVar,res,-1,indexLoadedVar));
                                }else{
                                    //constant
                                    constInfo res = currentScope->lookupConstantSymbol(indexVarName);
                                    auto result = std::make_shared<IRVar>();
                                    result->type = type->elementType;
                                    instrs.push_back(std::make_shared<IRGetptr>(currentVar->type, currentVar,result,res.value));
                                }
                            }
                        }
                    }
                }
            }
        }else if(auto *p = dynamic_cast<ExprField *>(& *node.name)){
            //a.b[0] 结构体成员是数组
            if(auto *structName = dynamic_cast<ExprPath *>(& *p->expr)){
                if(structName->pathFirst->pathSegments.type == IDENTIFIER){
                    std::string varName = structName->pathFirst->pathSegments.identifier;
                    auto currentVar = currentScope->lookupValueSymbol(varName);
                    //todo load and getfield then getindex
                    if(auto *structType = dynamic_cast<IRStructType *>(& *currentVar->type)){
                        std::string fieldName = p->identifier;
                        for(int i = 0; i < structType->memberTypes.size(); i++){
                            if(structType->memberTypes[i].first == fieldName){
                                if(auto *type = dynamic_cast<IRArrayType *>(& *structType->memberTypes[i].second)){
                                    auto loadedVar = std::make_shared<IRVar>();
                                    loadedVar->type = structType->memberTypes[i].second;
                                    instrs.push_back(std::make_shared<IRGetptr>(currentVar->type, currentVar,loadedVar,i));
                                    //getindex
                                    if(auto *indexExpr = dynamic_cast<ExprLiteral *>(& *node.index)){
                                        if(indexExpr->type == INTEGER_LITERAL){
                                            auto res = std::make_shared<IRVar>();
                                            res->type = type->elementType;
                                            instrs.push_back(std::make_shared<IRGetptr>(loadedVar->type, loadedVar,res,i));
                                        }
                                    }else{
                                        if(auto *indexExpr = dynamic_cast<ExprOpbinary *>(& *node.index)){
                                            auto indexInstrs = visit(*indexExpr);
                                            for(auto & instr : indexInstrs){
                                                instrs.push_back(instr);
                                            }
                                            auto lastInstr = indexInstrs[indexInstrs.size() - 1];
                                            if(auto *q = dynamic_cast<IRBinaryop *>(& *lastInstr)){
                                                auto indexVar = q->result;
                                                auto res = std::make_shared<IRVar>();
                                                res->type = type->elementType;
                                                instrs.push_back(std::make_shared<IRGetptr>(loadedVar->type, loadedVar,res,-1,indexVar));
                                            }
                                        }else if(auto *indexExpr = dynamic_cast<ExprPath *>(& *node.index)){
                                            if(indexExpr->pathFirst->pathSegments.type == IDENTIFIER){
                                                std::string indexVarName = indexExpr->pathFirst->pathSegments.identifier;
                                                auto indexVarSymbol = currentScope->lookupValueSymbol(indexVarName);
                                                if(indexVarSymbol){
                                                    auto indexLoadedVar = std::make_shared<IRVar>();
                                                    indexLoadedVar->type = indexVarSymbol->type;
                                                    instrs.push_back(std::make_shared<IRLoad>(indexLoadedVar, indexVarSymbol,indexVarSymbol->type));
                                                    auto res = std::make_shared<IRVar>();
                                                    res->type = type->elementType;
                                                    instrs.push_back(std::make_shared<IRGetptr>(loadedVar->type, loadedVar,res,-1,indexLoadedVar));
                                                }else{
                                                    //constant
                                                    constInfo res = currentScope->lookupConstantSymbol(indexVarName);
                                                    auto result = std::make_shared<IRVar>();
                                                    result->type = type->elementType;
                                                    instrs.push_back(std::make_shared<IRGetptr>(loadedVar->type, loadedVar,result,res.value,nullptr));
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
        return instrs;
    }

    std::vector<std::shared_ptr<IRNode>> visit(ExprLiteral &node){
        return {};
    }

    std::shared_ptr<IRBlock> visit(ExprLoop &node){
        auto loopBlock = std::make_shared<IRBlock>();
        std::vector<std::shared_ptr<IRNode>> instrs;
        std::vector<std::shared_ptr<IRBlock>> blocks;
        auto condBlock = std::make_shared<IRBlock>();
        instrs.push_back(std::make_shared<IRBr>(condBlock));
        bool isTrue = false;
        auto condVar = std::make_shared<IRVar>();
        if(auto *p = dynamic_cast<ExprOpbinary *>(& *node.condition)){
            auto condInstrs = visit(*p);
            for(auto & instr : condInstrs){
                condBlock->instrList.push_back(instr);
            }
            auto lastInstr = condInstrs[condInstrs.size() - 1];
            if(auto *q = dynamic_cast<IRBinaryop *>(& *lastInstr)){
                condVar = q->result;
            }
        }else if(auto *p = dynamic_cast<ExprPath *>(& *node.condition)){
            if(p->pathFirst->pathSegments.type == IDENTIFIER){
                std::string varName = p->pathFirst->pathSegments.identifier;
                auto currentVar = currentScope->lookupValueSymbol(varName);
                //todo trunc
                if(varName == "true"){
                    isTrue = true;
                }else{
                    auto tmp = std::make_shared<IRVar>();
                    condBlock->instrList.push_back(std::make_shared<IRLoad>(tmp, currentVar, currentVar->type));
                    condBlock->instrList.push_back(std::make_shared<IRTrunc>(currentVar->type, tmp, currentScope->lookupTypeSymbol("BOOL"), condVar));
                }
            }
        }
        // br required here
        //special judge for while(true)
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
                        if(bodyBlock->blockList.empty()){
                            for(auto & instr : stmtInstrs){
                                bodyBlock->instrList.push_back(instr);
                            }
                        }else{
                            auto lastBlock = bodyBlock->blockList[bodyBlock->blockList.size() - 1];
                            for(auto & instr : stmtInstrs){
                                lastBlock->instrList.push_back(instr);
                            }
                        }
                    }
                }else if(auto *letStmt = dynamic_cast<StmtLet *>(& *stmt)){
                    auto stmtInstrs = visit(*letStmt);
                    if(bodyBlock->blockList.empty()){
                        for(auto & instr : stmtInstrs){
                            bodyBlock->instrList.push_back(instr);
                        }
                    }else{
                        auto lastBlock = bodyBlock->blockList[bodyBlock->blockList.size() - 1];
                        for(auto & instr : stmtInstrs){
                            lastBlock->instrList.push_back(instr);
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
            condBlock->instrList.push_back(std::make_shared<IRBr>(condVar, bodyBlock, returnBlock));
            blocks.push_back(condBlock);
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

    std::vector<std::shared_ptr<IRNode>> visit(ExprMethodcall &node){
        std::vector<std::shared_ptr<IRNode>> instrs;
        if(auto *p = dynamic_cast<ExprPath *>(& *node.expr)){
            if(p->pathFirst->pathSegments.type == IDENTIFIER){
                std::string varName = p->pathFirst->pathSegments.identifier;
                auto currentVar = currentScope->lookupValueSymbol(varName);
                //todo load and methodcall
                if(auto *structType = dynamic_cast<IRStructType *>(& *currentVar->type)){
                    std::string methodName = node.PathExprSegment->pathSegments.identifier;
                    for(int i = 0;i < structType->memberFunctions.size();i ++){
                        if(structType->memberFunctions[i]->name == methodName){
                            auto currentIRFunc = structType->memberFunctions[i];
                            auto currentCallInstr = std::make_shared<IRCall>();
                            currentCallInstr->function = currentIRFunc;
                            auto callRet = std::make_shared<IRVar>();
                            callRet->type = currentIRFunc->retType;
                            currentCallInstr->retVar = callRet;
                            //first param is self
                            //todo self processing
                            for(auto & arg : node.callParams){
                                //TODO process arguments
                                if(auto *p = dynamic_cast<ExprPath *>(& *arg)){
                                    if(p->pathFirst->pathSegments.type == IDENTIFIER){
                                        std::string varName = p->pathFirst->pathSegments.identifier;
                                        auto varSymbol = currentScope->lookupValueSymbol(varName);
                                        if(varSymbol == nullptr){
                                            //constant
                                            constInfo res = currentScope->lookupConstantSymbol(varName);
                                            currentCallInstr->pList->paramList.push_back(std::make_shared<IRLiteral>(INT_LITERAL, res.value));
                                            continue;
                                        }
                                        auto currentParamVar = std::make_shared<IRVar>();
                                        currentParamVar->varName = varSymbol->varName;
                                        if(vars_cnt.find(currentParamVar->varName) != vars_cnt.end()){
                                            vars_cnt[currentParamVar->varName] += 1;
                                            currentParamVar->reName = currentParamVar->varName + "_" + std::to_string(vars_cnt[currentParamVar->varName]);
                                        }else{
                                            vars_cnt[currentParamVar->varName] = 1;
                                            currentParamVar->reName = currentParamVar->varName;
                                        }
                                        currentParamVar->type = varSymbol->type;
                                        instrs.push_back(std::make_shared<IRLoad>(currentParamVar, varSymbol,varSymbol->type));
                                        currentCallInstr->pList->paramList.push_back(currentParamVar);
                                    }
                                }else if(auto *lit = dynamic_cast<ExprLiteral *>(& *arg)){
                                    auto literalVar = std::make_shared<IRLiteral>(INT_LITERAL, lit->integer);
                                    currentCallInstr->pList->paramList.push_back(literalVar);
                                }
                            }
                            instrs.push_back(currentCallInstr);
                            break;
                        }
                    }
                }
            }
        }
        return instrs;
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
        }
        throw std::runtime_error("IRBuilder turnBinaryOp error: unknown binary op");
    }

    void bothLoad(std::vector<std::shared_ptr<IRNode>> &instrs,std::shared_ptr<IRVar> leftVarSymbol, std::shared_ptr<IRVar> rightVarSymbol,binaryOp op){
        auto leftLoadedVar = std::make_shared<IRVar>();
        auto rightLoadedVar = std::make_shared<IRVar>();
        leftLoadedVar->type = leftVarSymbol->type;
        rightLoadedVar->type = rightVarSymbol->type;
        instrs.push_back(std::make_shared<IRLoad>(leftLoadedVar, leftVarSymbol, leftVarSymbol->type));
        instrs.push_back(std::make_shared<IRLoad>(rightLoadedVar, rightVarSymbol, rightVarSymbol->type));
        auto resultVar = std::make_shared<IRVar>();
        //todo get binary op
        IROp irOp = turnBinaryOp(op);
        if(irOp == ADD){
            resultVar->type = leftVarSymbol->type;
            instrs.push_back(std::make_shared<IRAdd>(leftLoadedVar,nullptr, rightLoadedVar, nullptr, resultVar));
        }else if(irOp == SUB){
            resultVar->type = leftVarSymbol->type;
            instrs.push_back(std::make_shared<IRSub>(leftLoadedVar,nullptr, rightLoadedVar, nullptr, resultVar));   
        }else if(irOp == MUL){
            resultVar->type = leftVarSymbol->type;
            instrs.push_back(std::make_shared<IRMul>(leftLoadedVar,nullptr, rightLoadedVar, nullptr, resultVar));
        }else if(irOp == DIV){
            resultVar->type = leftVarSymbol->type;
            instrs.push_back(std::make_shared<IRDiv>(leftLoadedVar,nullptr, rightLoadedVar, nullptr, resultVar));   
        }else if(irOp == MOD){
            resultVar->type = leftVarSymbol->type;
            instrs.push_back(std::make_shared<IRMod>(leftLoadedVar,nullptr, rightLoadedVar, nullptr, resultVar));
        }else if(irOp == EQ){
            resultVar->type = currentScope->lookupTypeSymbol("BOOL");
            instrs.push_back(std::make_shared<IREq>(leftLoadedVar,nullptr, rightLoadedVar, nullptr, resultVar));    
        }else if(irOp == NEQ){
            resultVar->type = currentScope->lookupTypeSymbol("BOOL");
            instrs.push_back(std::make_shared<IRNeq>(leftLoadedVar,nullptr, rightLoadedVar, nullptr, resultVar));    
        }else if(irOp == LT){
            resultVar->type = currentScope->lookupTypeSymbol("BOOL");
            instrs.push_back(std::make_shared<IRLt>(leftLoadedVar,nullptr, rightLoadedVar, nullptr, resultVar));    
        }else if(irOp == LEQ){  
            resultVar->type = currentScope->lookupTypeSymbol("BOOL");
            instrs.push_back(std::make_shared<IRLeq>(leftLoadedVar,nullptr, rightLoadedVar, nullptr, resultVar));    
        }else if(irOp == GT){
            resultVar->type = currentScope->lookupTypeSymbol("BOOL");
            instrs.push_back(std::make_shared<IRGt>(leftLoadedVar,nullptr, rightLoadedVar, nullptr, resultVar));    
        }else if(irOp == GEQ){
            resultVar->type = currentScope->lookupTypeSymbol("BOOL");
            instrs.push_back(std::make_shared<IRGeq>(leftLoadedVar,nullptr, rightLoadedVar, nullptr, resultVar));
        }else if(irOp == LOGICALAND){
            resultVar->type = currentScope->lookupTypeSymbol("BOOL");
            instrs.push_back(std::make_shared<IRLogicalAnd>(leftLoadedVar,nullptr, rightLoadedVar, nullptr, resultVar));    
        }else if(irOp == LOGICALOR){
            resultVar->type = currentScope->lookupTypeSymbol("BOOL");
            instrs.push_back(std::make_shared<IRLogicalOr>(leftLoadedVar,nullptr, rightLoadedVar, nullptr, resultVar));
        }else if(irOp == ADD_EQ){
            instrs.push_back(std::make_shared<IRAdd>(leftLoadedVar,nullptr, rightLoadedVar, nullptr, resultVar));
            instrs.push_back(std::make_shared<IRStore>(leftVarSymbol->type,resultVar,nullptr,leftVarSymbol));
        }else if(irOp == SUB_EQ){
            instrs.push_back(std::make_shared<IRSub>(leftLoadedVar,nullptr, rightLoadedVar, nullptr, resultVar));
            instrs.push_back(std::make_shared<IRStore>(leftVarSymbol->type,resultVar,nullptr,leftVarSymbol));
        }else if(irOp == MUL_EQ){
            instrs.push_back(std::make_shared<IRMul>(leftLoadedVar,nullptr, rightLoadedVar, nullptr, resultVar));
            instrs.push_back(std::make_shared<IRStore>(leftVarSymbol->type,resultVar,nullptr,leftVarSymbol));
        }else if(irOp == DIV_EQ){
            instrs.push_back(std::make_shared<IRDiv>(leftLoadedVar,nullptr, rightLoadedVar, nullptr, resultVar));
            instrs.push_back(std::make_shared<IRStore>(leftVarSymbol->type,resultVar,nullptr,leftVarSymbol));
        }else if(irOp == MOD_EQ){
            instrs.push_back(std::make_shared<IRMod>(leftLoadedVar,nullptr, rightLoadedVar, nullptr, resultVar));
            instrs.push_back(std::make_shared<IRStore>(leftVarSymbol->type,resultVar,nullptr,leftVarSymbol));
        }else if(irOp == ASSIGNEQ){
            instrs.push_back(std::make_shared<IRStore>(leftVarSymbol->type,rightLoadedVar,nullptr,leftVarSymbol));
        }else {
            throw std::runtime_error("IRBuilder visit ExprOpbinary error: unknown binary op");
        }
    }

    void bothLoadForCall(std::vector<std::shared_ptr<IRNode>> &instrs,std::shared_ptr<IRVar> leftVarSymbol,std::shared_ptr<IRVar> leftLoadedVar, std::shared_ptr<IRVar> rightCallRetVar,binaryOp op){
        auto resultVar = std::make_shared<IRVar>();
        IROp irOp = turnBinaryOp(op);
        if(irOp == ADD){
            resultVar->type = leftVarSymbol->type;
            instrs.push_back(std::make_shared<IRAdd>(leftLoadedVar,nullptr, rightCallRetVar, nullptr, resultVar));
        }else if(irOp == SUB){
            resultVar->type = leftVarSymbol->type;
            instrs.push_back(std::make_shared<IRSub>(leftLoadedVar,nullptr, rightCallRetVar, nullptr, resultVar));   
        }else if(irOp == MUL){
            resultVar->type = leftVarSymbol->type;
            instrs.push_back(std::make_shared<IRMul>(leftLoadedVar,nullptr, rightCallRetVar, nullptr, resultVar));
        }else if(irOp == DIV){
            resultVar->type = leftVarSymbol->type;
            instrs.push_back(std::make_shared<IRDiv>(leftLoadedVar,nullptr, rightCallRetVar, nullptr, resultVar));   
        }else if(irOp == MOD){
            resultVar->type = leftVarSymbol->type;
            instrs.push_back(std::make_shared<IRMod>(leftLoadedVar,nullptr, rightCallRetVar, nullptr, resultVar));
        }else if(irOp == EQ){
            resultVar->type = currentScope->lookupTypeSymbol("BOOL");
            instrs.push_back(std::make_shared<IREq>(leftLoadedVar,nullptr, rightCallRetVar, nullptr, resultVar));    
        }else if(irOp == NEQ){
            resultVar->type = currentScope->lookupTypeSymbol("BOOL");
            instrs.push_back(std::make_shared<IRNeq>(leftLoadedVar,nullptr, rightCallRetVar, nullptr, resultVar));    
        }else if(irOp == LT){
            resultVar->type = currentScope->lookupTypeSymbol("BOOL");
            instrs.push_back(std::make_shared<IRLt>(leftLoadedVar,nullptr, rightCallRetVar, nullptr, resultVar));    
        }else if(irOp == LEQ){
            resultVar->type = currentScope->lookupTypeSymbol("BOOL");
            instrs.push_back(std::make_shared<IRLeq>(leftLoadedVar,nullptr, rightCallRetVar, nullptr, resultVar));
        }else if(irOp == GT){
            resultVar->type = currentScope->lookupTypeSymbol("BOOL");
            instrs.push_back(std::make_shared<IRGt>(leftLoadedVar,nullptr, rightCallRetVar, nullptr, resultVar));
        }else if(irOp == GEQ){
            resultVar->type = currentScope->lookupTypeSymbol("BOOL");
            instrs.push_back(std::make_shared<IRGeq>(leftLoadedVar,nullptr, rightCallRetVar, nullptr, resultVar));
        }else if(irOp == LOGICALAND){
            resultVar->type = currentScope->lookupTypeSymbol("BOOL");
            instrs.push_back(std::make_shared<IRLogicalAnd>(leftLoadedVar,nullptr, rightCallRetVar, nullptr, resultVar));
        }else if(irOp == LOGICALOR){
            resultVar->type = currentScope->lookupTypeSymbol("BOOL");
            instrs.push_back(std::make_shared<IRLogicalOr>(leftLoadedVar,nullptr, rightCallRetVar, nullptr, resultVar));
        }else if(irOp == ADD_EQ){
            instrs.push_back(std::make_shared<IRAdd>(leftLoadedVar,nullptr, rightCallRetVar, nullptr, resultVar));
            instrs.push_back(std::make_shared<IRStore>(leftVarSymbol->type,resultVar,nullptr,leftVarSymbol));
        }else if(irOp == SUB_EQ){
            instrs.push_back(std::make_shared<IRSub>(leftLoadedVar,nullptr, rightCallRetVar, nullptr, resultVar));
            instrs.push_back(std::make_shared<IRStore>(leftVarSymbol->type,resultVar,nullptr,leftVarSymbol));
        }else if(irOp == MUL_EQ){
            instrs.push_back(std::make_shared<IRMul>(leftLoadedVar,nullptr, rightCallRetVar, nullptr, resultVar));
            instrs.push_back(std::make_shared<IRStore>(leftVarSymbol->type,resultVar,nullptr,leftVarSymbol));
        }else if(irOp == DIV_EQ){
            instrs.push_back(std::make_shared<IRDiv>(leftLoadedVar,nullptr, rightCallRetVar, nullptr, resultVar));
            instrs.push_back(std::make_shared<IRStore>(leftVarSymbol->type,resultVar,nullptr,leftVarSymbol));
        }else if(irOp == MOD_EQ){
            instrs.push_back(std::make_shared<IRMod>(leftLoadedVar,nullptr, rightCallRetVar, nullptr, resultVar));
            instrs.push_back(std::make_shared<IRStore>(leftVarSymbol->type,resultVar,nullptr,leftVarSymbol));
        }else if(irOp == ASSIGNEQ){
            instrs.push_back(std::make_shared<IRStore>(leftVarSymbol->type,rightCallRetVar,nullptr,leftVarSymbol));
        }else {
            throw std::runtime_error("IRBuilder visit ExprOpbinary error: unknown binary op");
        }
    }

    void leftLoadRightLiteral(std::vector<std::shared_ptr<IRNode>> &instrs,std::shared_ptr<IRVar> leftVarSymbol, std::shared_ptr<IRVar> rightVarSymbol,binaryOp op, constInfo res,bool isleftCall ){
        auto leftLoadedVar = std::make_shared<IRVar>();
        if(isleftCall){
            leftLoadedVar = leftVarSymbol;
        }else{
            leftLoadedVar->type = leftVarSymbol->type;
            instrs.push_back(std::make_shared<IRLoad>(leftLoadedVar, leftVarSymbol, leftVarSymbol->type));
        }
        auto resultVar = std::make_shared<IRVar>();
        IROp irOp = turnBinaryOp(op);
        auto rightLiteral = std::make_shared<IRLiteral>(INT_LITERAL, res.value);
        if(irOp == ADD){
            //resultVar->type = currentScope->lookupTypeSymbol("usize");
            resultVar->type = leftVarSymbol->type;
            instrs.push_back(std::make_shared<IRAdd>(leftLoadedVar,nullptr,nullptr, rightLiteral, resultVar));
        }else if(irOp == SUB){
            //resultVar->type = currentScope->lookupTypeSymbol("usize");
            resultVar->type = leftVarSymbol->type;
            instrs.push_back(std::make_shared<IRSub>(leftLoadedVar,nullptr,nullptr, rightLiteral, resultVar));   
        }else if(irOp == MUL){
            //resultVar->type = currentScope->lookupTypeSymbol("usize");
            resultVar->type = leftVarSymbol->type;
            instrs.push_back(std::make_shared<IRMul>(leftLoadedVar,nullptr,nullptr, rightLiteral, resultVar));
        }else if(irOp == DIV){
            //resultVar->type = currentScope->lookupTypeSymbol("usize");
            resultVar->type = leftVarSymbol->type;
            instrs.push_back(std::make_shared<IRDiv>(leftLoadedVar,nullptr,nullptr,rightLiteral, resultVar));
        }else if(irOp == MOD){
            //resultVar->type = currentScope->lookupTypeSymbol("usize");
            resultVar->type = leftVarSymbol->type;
            instrs.push_back(std::make_shared<IRMod>(leftLoadedVar,nullptr,nullptr, rightLiteral, resultVar));  
        }else if(irOp == EQ){
            resultVar->type = currentScope->lookupTypeSymbol("BOOL");
            instrs.push_back(std::make_shared<IREq>(leftLoadedVar,nullptr,nullptr, rightLiteral, resultVar));    
        }else if(irOp == NEQ){
            resultVar->type = currentScope->lookupTypeSymbol("BOOL");
            instrs.push_back(std::make_shared<IRNeq>(leftLoadedVar,nullptr,nullptr, rightLiteral, resultVar));    
        }else if(irOp == LT){
            resultVar->type = currentScope->lookupTypeSymbol("BOOL");
            instrs.push_back(std::make_shared<IRLt>(leftLoadedVar,nullptr,nullptr, rightLiteral, resultVar));
        }else if(irOp == LEQ){  
            resultVar->type = currentScope->lookupTypeSymbol("BOOL");
            instrs.push_back(std::make_shared<IRLeq>(leftLoadedVar,nullptr,nullptr, rightLiteral, resultVar));
        }else if(irOp == GT){
            resultVar->type = currentScope->lookupTypeSymbol("BOOL");
            instrs.push_back(std::make_shared<IRGt>(leftLoadedVar,nullptr,nullptr, rightLiteral, resultVar));
        }else if(irOp == GEQ){
            resultVar->type = currentScope->lookupTypeSymbol("BOOL");
            instrs.push_back(std::make_shared<IRGeq>(leftLoadedVar,nullptr,nullptr, rightLiteral, resultVar));
        }else if(irOp == LOGICALAND){
            resultVar->type = currentScope->lookupTypeSymbol("BOOL");
            instrs.push_back(std::make_shared<IRLogicalAnd>(leftLoadedVar,nullptr,nullptr, rightLiteral, resultVar));
        }else if(irOp == LOGICALOR){
            resultVar->type = currentScope->lookupTypeSymbol("BOOL");
            instrs.push_back(std::make_shared<IRLogicalOr>(leftLoadedVar,nullptr,nullptr, rightLiteral, resultVar));
        }else if(irOp == ADD_EQ){
            instrs.push_back(std::make_shared<IRAdd>(leftLoadedVar,nullptr,nullptr, rightLiteral, resultVar));
            instrs.push_back(std::make_shared<IRStore>(leftVarSymbol->type,resultVar,nullptr,leftVarSymbol));
        }else if(irOp == SUB_EQ){
            instrs.push_back(std::make_shared<IRSub>(leftLoadedVar,nullptr,nullptr, rightLiteral, resultVar));
            instrs.push_back(std::make_shared<IRStore>(leftVarSymbol->type,resultVar,nullptr,leftVarSymbol));
        }else if(irOp == MUL_EQ){
            instrs.push_back(std::make_shared<IRMul>(leftLoadedVar,nullptr,nullptr, rightLiteral, resultVar));
            instrs.push_back(std::make_shared<IRStore>(leftVarSymbol->type,resultVar,nullptr,leftVarSymbol));
        }else if(irOp == DIV_EQ){
            instrs.push_back(std::make_shared<IRDiv>(leftLoadedVar,nullptr,nullptr, rightLiteral, resultVar));
            instrs.push_back(std::make_shared<IRStore>(leftVarSymbol->type,resultVar,nullptr,leftVarSymbol));
        }else if(irOp == MOD_EQ){
            instrs.push_back(std::make_shared<IRMod>(leftLoadedVar,nullptr,nullptr, rightLiteral, resultVar));
            instrs.push_back(std::make_shared<IRStore>(leftVarSymbol->type,resultVar,nullptr,leftVarSymbol));
        }else if(irOp == ASSIGNEQ){
            instrs.push_back(std::make_shared<IRStore>(leftVarSymbol->type,nullptr,rightLiteral,leftVarSymbol));
        }else {
            throw std::runtime_error("IRBuilder visit ExprOpbinary error: unknown binary op");
        }
    }

    void leftLiteralRightLoad(std::vector<std::shared_ptr<IRNode>> &instrs,std::shared_ptr<IRVar> leftVarSymbol, std::shared_ptr<IRVar> rightVarSymbol,binaryOp op, constInfo res,bool isRightCall ){
        auto rightLoadedVar = std::make_shared<IRVar>();
        if(isRightCall){
            rightLoadedVar = rightVarSymbol;
        }else{
            rightLoadedVar->type = rightVarSymbol->type;
            instrs.push_back(std::make_shared<IRLoad>(rightLoadedVar, rightVarSymbol, rightVarSymbol->type));
        }
        auto resultVar = std::make_shared<IRVar>();
        IROp irOp = turnBinaryOp(op);
        auto leftLiteral = std::make_shared<IRLiteral>(INT_LITERAL, res.value);
        if(irOp == ADD){
            //resultVar->type = currentScope->lookupTypeSymbol("usize");
            resultVar->type = rightVarSymbol->type; 
            instrs.push_back(std::make_shared<IRAdd>(nullptr,leftLiteral, rightLoadedVar, nullptr, resultVar));
        }else if(irOp == SUB){
            //resultVar->type = currentScope->lookupTypeSymbol("usize");
            resultVar->type = rightVarSymbol->type;
            instrs.push_back(std::make_shared<IRSub>(nullptr,leftLiteral, rightLoadedVar, nullptr, resultVar));
        }else if(irOp == MUL){
            //resultVar->type = currentScope->lookupTypeSymbol("usize");
            resultVar->type = rightVarSymbol->type;
            instrs.push_back(std::make_shared<IRMul>(nullptr,leftLiteral, rightLoadedVar, nullptr, resultVar));
        }else if(irOp == DIV){
            //resultVar->type = currentScope->lookupTypeSymbol("usize");
            resultVar->type = rightVarSymbol->type;
            instrs.push_back(std::make_shared<IRDiv>(nullptr,leftLiteral, rightLoadedVar, nullptr, resultVar));
        }else if(irOp == MOD){
            //resultVar->type = currentScope->lookupTypeSymbol("usize");
            resultVar->type = rightVarSymbol->type;
            instrs.push_back(std::make_shared<IRMod>(nullptr,leftLiteral, rightLoadedVar, nullptr, resultVar));
        }else if(irOp == EQ){
            resultVar->type = currentScope->lookupTypeSymbol("BOOL");
            instrs.push_back(std::make_shared<IREq>(nullptr,leftLiteral, rightLoadedVar, nullptr, resultVar));
        }else if(irOp == NEQ){
            resultVar->type = currentScope->lookupTypeSymbol("BOOL");
            instrs.push_back(std::make_shared<IRNeq>(nullptr,leftLiteral, rightLoadedVar, nullptr, resultVar));
        }else if(irOp == LT){
            resultVar->type = currentScope->lookupTypeSymbol("BOOL");
            instrs.push_back(std::make_shared<IRLt>(nullptr,leftLiteral, rightLoadedVar, nullptr, resultVar));
        }else if(irOp == LEQ){
            resultVar->type = currentScope->lookupTypeSymbol("BOOL");
            instrs.push_back(std::make_shared<IRLeq>(nullptr,leftLiteral, rightLoadedVar, nullptr, resultVar));
        }else if(irOp == GT){
            resultVar->type = currentScope->lookupTypeSymbol("BOOL");
            instrs.push_back(std::make_shared<IRGt>(nullptr,leftLiteral, rightLoadedVar, nullptr, resultVar));
        }else if(irOp == GEQ){
            resultVar->type = currentScope->lookupTypeSymbol("BOOL");
            instrs.push_back(std::make_shared<IRGeq>(nullptr,leftLiteral, rightLoadedVar, nullptr, resultVar));
        }else if(irOp == LOGICALAND){
            resultVar->type = currentScope->lookupTypeSymbol("BOOL");
            instrs.push_back(std::make_shared<IRLogicalAnd>(nullptr,leftLiteral, rightLoadedVar, nullptr, resultVar));
        }else if(irOp == LOGICALOR){
            resultVar->type = currentScope->lookupTypeSymbol("BOOL");
            instrs.push_back(std::make_shared<IRLogicalOr>(nullptr,leftLiteral, rightLoadedVar, nullptr, resultVar));
        }else {
            throw std::runtime_error("IRBuilder visit ExprOpbinary error: unknown binary op");
        }
    }

    void bothLiteral(std::vector<std::shared_ptr<IRNode>> &instrs,constInfo leftRes, constInfo rightRes,binaryOp op){
        auto resultVar = std::make_shared<IRVar>();
        IROp irOp = turnBinaryOp(op);
        auto leftLiteral = std::make_shared<IRLiteral>(INT_LITERAL, leftRes.value);
        auto rightLiteral = std::make_shared<IRLiteral>(INT_LITERAL, rightRes.value);
        std::string typeName;
        if(leftRes.type == "null" && rightRes.type == "null"){
            typeName = "i32";
        }else if(leftRes.type == "null"){
            typeName = rightRes.type;
        }else if(rightRes.type == "null"){
            typeName = leftRes.type;
        }else {
            typeName = leftRes.type;
        }
        if(irOp == ADD){
            //resultVar->type = currentScope->lookupTypeSymbol("usize");
            resultVar->type = currentScope->lookupTypeSymbol(typeName);
            instrs.push_back(std::make_shared<IRAdd>(nullptr,leftLiteral, nullptr, rightLiteral, resultVar));
        }else if(irOp == SUB){
            //resultVar->type = currentScope->lookupTypeSymbol("usize");
            resultVar->type = currentScope->lookupTypeSymbol(typeName);
            instrs.push_back(std::make_shared<IRSub>(nullptr,leftLiteral, nullptr, rightLiteral, resultVar));
        }else if(irOp == MUL){
            //resultVar->type = currentScope->lookupTypeSymbol("usize");
            resultVar->type = currentScope->lookupTypeSymbol(typeName);
            instrs.push_back(std::make_shared<IRMul>(nullptr,leftLiteral, nullptr, rightLiteral, resultVar));
        }else if(irOp == DIV){
            //resultVar->type = currentScope->lookupTypeSymbol("usize");
            resultVar->type = currentScope->lookupTypeSymbol(typeName);
            instrs.push_back(std::make_shared<IRDiv>(nullptr,leftLiteral, nullptr, rightLiteral, resultVar));
        }else if(irOp == MOD){
            //resultVar->type = currentScope->lookupTypeSymbol("usize");
            resultVar->type = currentScope->lookupTypeSymbol(typeName);
            instrs.push_back(std::make_shared<IRMod>(nullptr,leftLiteral, nullptr, rightLiteral, resultVar));
        }else if(irOp == EQ){
            resultVar->type = currentScope->lookupTypeSymbol("BOOL");
            instrs.push_back(std::make_shared<IREq>(nullptr,leftLiteral, nullptr, rightLiteral, resultVar));
        }else if(irOp == NEQ){
            resultVar->type = currentScope->lookupTypeSymbol("BOOL");
            instrs.push_back(std::make_shared<IRNeq>(nullptr,leftLiteral, nullptr, rightLiteral, resultVar));
        }else if(irOp == LT){
            resultVar->type = currentScope->lookupTypeSymbol("BOOL");
            instrs.push_back(std::make_shared<IRLt>(nullptr,leftLiteral, nullptr, rightLiteral, resultVar));
        }else if(irOp == LEQ){
            resultVar->type = currentScope->lookupTypeSymbol("BOOL");
            instrs.push_back(std::make_shared<IRLeq>(nullptr,leftLiteral, nullptr, rightLiteral, resultVar));
        }else if(irOp == GT){
            resultVar->type = currentScope->lookupTypeSymbol("BOOL");
            instrs.push_back(std::make_shared<IRGt>(nullptr,leftLiteral, nullptr, rightLiteral, resultVar));
        }else if(irOp == GEQ){
            resultVar->type = currentScope->lookupTypeSymbol("BOOL");
            instrs.push_back(std::make_shared<IRGeq>(nullptr,leftLiteral, nullptr, rightLiteral, resultVar));
        }else if(irOp == LOGICALAND){
            resultVar->type = currentScope->lookupTypeSymbol("BOOL");
            instrs.push_back(std::make_shared<IRLogicalAnd>(nullptr,leftLiteral, nullptr, rightLiteral, resultVar));
        }else if(irOp == LOGICALOR){
            resultVar->type = currentScope->lookupTypeSymbol("BOOL");
            instrs.push_back(std::make_shared<IRLogicalOr>(nullptr,leftLiteral, nullptr, rightLiteral, resultVar));
        }else {
            throw std::runtime_error("IRBuilder visit ExprOpbinary error: unknown binary op");
        }
    }

    std::vector<std::shared_ptr<IRNode>> visit(ExprOpbinary &node){
        std::vector<std::shared_ptr<IRNode>> instrs;
        if(auto *leftPath = dynamic_cast<ExprPath *>(& *node.left)){
            if(auto *rightPath = dynamic_cast<ExprPath *>(& *node.right)){
                if(leftPath->pathFirst->pathSegments.type == IDENTIFIER && rightPath->pathFirst->pathSegments.type == IDENTIFIER){
                    std::string leftVarName = leftPath->pathFirst->pathSegments.identifier;
                    std::string rightVarName = rightPath->pathFirst->pathSegments.identifier;
                    auto leftVarSymbol = currentScope->lookupValueSymbol(leftVarName);
                    auto rightVarSymbol = currentScope->lookupValueSymbol(rightVarName);
                    if(leftVarSymbol && rightVarSymbol){
                        bothLoad(instrs, leftVarSymbol, rightVarSymbol, node.op);
                    }else if(leftVarSymbol && !rightVarSymbol){
                        if(rightVarName == "usize" || rightVarName == "isize" ){
                            if(node.op == AS_CAST){
                                auto leftLoadedVar = std::make_shared<IRVar>();
                                instrs.push_back(std::make_shared<IRLoad>(leftLoadedVar, leftVarSymbol, leftVarSymbol->type));
                                auto resultVar = std::make_shared<IRVar>();
                                //todo cast instr
                                if(leftVarSymbol->type == currentScope->lookupTypeSymbol("i32")){
                                    instrs.push_back(std::make_shared<IRSext>(currentScope->lookupTypeSymbol("i32"),leftLoadedVar, currentScope->lookupTypeSymbol("isize"), resultVar));
                                    resultVar->type = currentScope->lookupTypeSymbol("isize");
                                }else if(leftVarSymbol->type == currentScope->lookupTypeSymbol("u32")){
                                    instrs.push_back(std::make_shared<IRZext>(currentScope->lookupTypeSymbol("i32"),leftLoadedVar, currentScope->lookupTypeSymbol("isize"), resultVar));
                                    resultVar->type = currentScope->lookupTypeSymbol("isize");
                                }
                            }
                        }else if(rightVarName == "u32" || rightVarName == "i32" ){
                            if(node.op == AS_CAST){
                                auto leftLoadedVar = std::make_shared<IRVar>();
                                instrs.push_back(std::make_shared<IRLoad>(leftLoadedVar, leftVarSymbol, leftVarSymbol->type));
                                auto resultVar = std::make_shared<IRVar>();
                                //todo cast instr
                                if(leftVarSymbol->type == currentScope->lookupTypeSymbol("isize")){
                                    instrs.push_back(std::make_shared<IRTrunc>(currentScope->lookupTypeSymbol("isize"),leftLoadedVar, currentScope->lookupTypeSymbol("i32"), resultVar));
                                    resultVar->type = currentScope->lookupTypeSymbol("i32");
                                }else if(leftVarSymbol->type == currentScope->lookupTypeSymbol("usize")){
                                    instrs.push_back(std::make_shared<IRTrunc>(currentScope->lookupTypeSymbol("isize"),leftLoadedVar, currentScope->lookupTypeSymbol("u32"), resultVar));
                                    resultVar->type = currentScope->lookupTypeSymbol("i32");
                                }
                            }
                        }else{
                            constInfo res = currentScope->lookupConstantSymbol(rightVarName);
                            leftLoadRightLiteral(instrs, leftVarSymbol, rightVarSymbol, node.op, res,false);
                        }
                    }else if(!leftVarSymbol && rightVarSymbol){
                        constInfo res = currentScope->lookupConstantSymbol(leftVarName);
                        leftLiteralRightLoad(instrs, leftVarSymbol, rightVarSymbol, node.op, res,false);
                    }else if(!leftVarSymbol && !rightVarSymbol){
                        constInfo leftRes = currentScope->lookupConstantSymbol(leftVarName);
                        constInfo rightRes = currentScope->lookupConstantSymbol(rightVarName);
                        bothLiteral(instrs, leftRes, rightRes, node.op);
                    }
                }
            }else if(auto *rightLiteral = dynamic_cast<ExprLiteral *>(& *node.right)){
                if(leftPath->pathFirst->pathSegments.type == IDENTIFIER){
                    std::string leftVarName = leftPath->pathFirst->pathSegments.identifier;
                    auto leftVarSymbol = currentScope->lookupValueSymbol(leftVarName);
                    if(leftVarSymbol){
                        long long int res = rightLiteral->integer;
                        constInfo rightRes;
                        rightRes.value = res;
                        rightRes.type = "i32";
                        leftLoadRightLiteral(instrs, leftVarSymbol, nullptr, node.op, rightRes,false);
                    }else{
                        constInfo leftRes = currentScope->lookupConstantSymbol(leftVarName);
                        constInfo rightRes = {rightLiteral->integer, "null"};
                        bothLiteral(instrs, leftRes, rightRes, node.op);
                    }
                }
            }else if(auto *rightCall = dynamic_cast<ExprCall *>(& *node.right)){
                auto callInstrs = visit(*rightCall);
                if(auto *callLastInstr = dynamic_cast<IRCall *>(& *callInstrs[callInstrs.size() - 1])){
                    auto rightCallRetVar = callLastInstr->retVar;
                    if(leftPath->pathFirst->pathSegments.type == IDENTIFIER){
                        std::string leftVarName = leftPath->pathFirst->pathSegments.identifier;
                        auto leftVarSymbol = currentScope->lookupValueSymbol(leftVarName);
                        if(leftVarSymbol){
                            auto leftLoadedVar = std::make_shared<IRVar>();
                            leftLoadedVar->type = leftVarSymbol->type;
                            instrs.push_back(std::make_shared<IRLoad>(leftLoadedVar, leftVarSymbol, leftVarSymbol->type));
                            for(auto & instr : callInstrs){
                                instrs.push_back(instr);
                            }
                            bothLoadForCall(instrs, leftVarSymbol,leftLoadedVar, rightCallRetVar, node.op);
                        }else{
                            constInfo res = currentScope->lookupConstantSymbol(leftVarName);
                            for(auto & instr : callInstrs){
                                instrs.push_back(instr);
                            }
                            leftLiteralRightLoad(instrs, nullptr, rightCallRetVar, node.op, res, true);
                        }
                    }
                }
            }else if(auto *rightMethodCall = dynamic_cast<ExprMethodcall *>(& *node.right)){
                //todo
                if(leftPath->pathFirst->pathSegments.type == IDENTIFIER){
                    std::string leftVarName = leftPath->pathFirst->pathSegments.identifier;
                    auto leftVarSymbol = currentScope->lookupValueSymbol(leftVarName);
                    if(leftVarSymbol){
                        auto leftLoadedVar = std::make_shared<IRVar>();
                        instrs.push_back(std::make_shared<IRLoad>(leftLoadedVar, leftVarSymbol, leftVarSymbol->type));
                        std::vector<std::shared_ptr<IRNode>> methodCallInstrs = visit(*rightMethodCall);
                        for(auto & instr : methodCallInstrs){
                            instrs.push_back(instr);
                        }
                        auto lastInstr = methodCallInstrs[methodCallInstrs.size() - 1];
                        if(auto *q = dynamic_cast<IRCall *>(& *lastInstr)){
                            auto rightMethodCallRetVar = q->retVar;
                            bothLoadForCall(instrs, leftVarSymbol,leftLoadedVar, rightMethodCallRetVar, node.op);
                        }
                    }else{
                        constInfo res = currentScope->lookupConstantSymbol(leftVarName);
                        std::vector<std::shared_ptr<IRNode>> methodCallInstrs = visit(*rightMethodCall);
                        for(auto & instr : methodCallInstrs){
                            instrs.push_back(instr);
                        }
                        auto lastInstr = methodCallInstrs[methodCallInstrs.size() - 1];
                        if(auto *q = dynamic_cast<IRCall *>(& *lastInstr)){
                            auto rightMethodCallRetVar = q->retVar;
                            leftLiteralRightLoad(instrs, nullptr, rightMethodCallRetVar, node.op, res,true);
                        }
                    }
                }
            }else if(auto *rightOpBinary = dynamic_cast<ExprOpbinary *>(& *node.right)){
                //todo nested binary op
                if(leftPath->pathFirst->pathSegments.type == IDENTIFIER){
                    std::string leftVarName = leftPath->pathFirst->pathSegments.identifier;
                    auto leftVarSymbol = currentScope->lookupValueSymbol(leftVarName);
                    if(leftVarSymbol){
                        auto leftLoadedVar = std::make_shared<IRVar>();
                        instrs.push_back(std::make_shared<IRLoad>(leftLoadedVar, leftVarSymbol, leftVarSymbol->type));
                        std::vector<std::shared_ptr<IRNode>> rightInstrs = visit(*rightOpBinary);
                        for(auto & instr : rightInstrs){
                            instrs.push_back(instr);
                        }
                        auto lastInstr = rightInstrs[rightInstrs.size() - 1];
                        if(auto *q = dynamic_cast<IRBinaryop *>(& *lastInstr)){
                            auto rightResultVar = q->result;
                            bothLoadForCall(instrs, leftVarSymbol,leftLoadedVar, rightResultVar, node.op);
                        }
                    }else{
                        constInfo res = currentScope->lookupConstantSymbol(leftVarName);
                        std::vector<std::shared_ptr<IRNode>> rightInstrs = visit(*rightOpBinary);
                        for(auto & instr : rightInstrs){
                            instrs.push_back(instr);
                        }
                        auto lastInstr = rightInstrs[rightInstrs.size() - 1];
                        if(auto *q = dynamic_cast<IRBinaryop *>(& *lastInstr)){
                            auto rightResultVar = q->result;
                            leftLiteralRightLoad(instrs, nullptr, rightResultVar, node.op, res,true);
                        }
                    }
                }
            }
        }else if(auto *leftLiteral = dynamic_cast<ExprLiteral *>(& *node.left)){
            if(auto *rightPath = dynamic_cast<ExprPath *>(& *node.right)){
                if(rightPath->pathFirst->pathSegments.type == IDENTIFIER){
                    std::string rightVarName = rightPath->pathFirst->pathSegments.identifier;
                    auto rightVarSymbol = currentScope->lookupValueSymbol(rightVarName);
                    if(rightVarSymbol){
                        constInfo res = {leftLiteral->integer,"null"};
                        leftLiteralRightLoad(instrs, nullptr, rightVarSymbol, node.op, res,false);
                    }else{
                        constInfo leftRes = {leftLiteral->integer,"null"};
                        constInfo rightRes = currentScope->lookupConstantSymbol(rightVarName);
                        bothLiteral(instrs, leftRes, rightRes, node.op);
                    }
                }
            }else if(auto *rightLiteral = dynamic_cast<ExprLiteral *>(& *node.right)){
                constInfo leftRes = {leftLiteral->integer,"null"};
                constInfo rightRes = {rightLiteral->integer,"null"};
                bothLiteral(instrs, leftRes, rightRes, node.op);
            }else if(auto *rightCall = dynamic_cast<ExprCall *>(& *node.right)){
                auto callInstrs = visit(*rightCall);
                if(auto *callLastInstr = dynamic_cast<IRCall *>(& *callInstrs[callInstrs.size() - 1])){
                    auto rightCallRetVar = callLastInstr->retVar;
                    constInfo res = {leftLiteral->integer, "null"};
                    for(auto & instr : callInstrs){
                        instrs.push_back(instr);
                    }
                    leftLiteralRightLoad(instrs, nullptr, rightCallRetVar, node.op, res,true);
                }
            }else if(auto *rightMethodCall = dynamic_cast<ExprMethodcall *>(& *node.right)){
                //todo
                std::vector<std::shared_ptr<IRNode>> methodCallInstrs = visit(*rightMethodCall);
                auto lastInstr = methodCallInstrs[methodCallInstrs.size() - 1];
                if(auto *q = dynamic_cast<IRCall *>(& *lastInstr)){
                    auto rightMethodCallRetVar = q->retVar;
                    constInfo res = {leftLiteral->integer, "null"};
                    for(auto & instr : methodCallInstrs){
                        instrs.push_back(instr);
                    }
                    leftLiteralRightLoad(instrs, nullptr, rightMethodCallRetVar, node.op, res,true);
                }   
            }else if(auto *rightOpBinary = dynamic_cast<ExprOpbinary *>(& *node.right)){
                //todo nested binary op
                constInfo leftRes = {leftLiteral->integer, "null"};
                std::vector<std::shared_ptr<IRNode>> rightInstrs = visit(*rightOpBinary);
                for(auto & instr : rightInstrs){
                    instrs.push_back(instr);
                }
                auto lastInstr = rightInstrs[rightInstrs.size() - 1];
                if(auto *q = dynamic_cast<IRBinaryop *>(& *lastInstr)){
                    auto rightResultVar = q->result;
                    leftLiteralRightLoad(instrs, nullptr, rightResultVar, node.op, leftRes,true);
                }
            }
        }else if(auto *leftCall = dynamic_cast<ExprCall *>(& *node.left)){
            if(auto *rightPath = dynamic_cast<ExprPath *>(& *node.right)){
                auto callInstrs = visit(*leftCall);
                if(auto *callLastInstr = dynamic_cast<IRCall *>(& *callInstrs[callInstrs.size() - 1])){
                    auto leftCallRetVar = callLastInstr->retVar;
                    if(rightPath->pathFirst->pathSegments.type == IDENTIFIER){
                        std::string rightVarName = rightPath->pathFirst->pathSegments.identifier;
                        auto rightVarSymbol = currentScope->lookupValueSymbol(rightVarName);
                        if(rightVarSymbol){
                            for(auto & instr : callInstrs){
                                instrs.push_back(instr);
                            }
                            auto rightLoadedVar = std::make_shared<IRVar>();
                            instrs.push_back(std::make_shared<IRLoad>(rightLoadedVar, rightVarSymbol, rightVarSymbol->type));
                            bothLoadForCall(instrs, rightVarSymbol,leftCallRetVar, rightLoadedVar, node.op);
                        }else{
                            constInfo rightRes = currentScope->lookupConstantSymbol(rightVarName);
                            for(auto & instr : callInstrs){
                                instrs.push_back(instr);
                            }
                            leftLoadRightLiteral(instrs, leftCallRetVar, nullptr, node.op, rightRes,true);
                        }
                    }
                }
            }else if(auto *rightLiteral = dynamic_cast<ExprLiteral *>(& *node.right)){
                auto callInstrs = visit(*leftCall);
                if(auto *callLastInstr = dynamic_cast<IRCall *>(& *callInstrs[callInstrs.size() - 1])){
                    auto leftCallRetVar = callLastInstr->retVar;
                    constInfo res = {rightLiteral->integer, "null"};
                    for(auto & instr : callInstrs){
                        instrs.push_back(instr);
                    }
                    leftLoadRightLiteral(instrs, leftCallRetVar, nullptr, node.op, res,true);
                }
            }else if(auto *rightCall = dynamic_cast<ExprCall *>(& *node.right)){
                auto leftCallInstrs = visit(*leftCall);
                auto rightCallInstrs = visit(*rightCall);
                if(auto *leftCallLastInstr = dynamic_cast<IRCall *>(& *leftCallInstrs[leftCallInstrs.size() - 1])){
                    if(auto *rightCallLastInstr = dynamic_cast<IRCall *>(& *rightCallInstrs[rightCallInstrs.size() - 1])){
                        auto leftCallRetVar = leftCallLastInstr->retVar;
                        auto rightCallRetVar = rightCallLastInstr->retVar;
                        for(auto & instr : leftCallInstrs){
                            instrs.push_back(instr);
                        }
                        for(auto & instr : rightCallInstrs){
                            instrs.push_back(instr);
                        }
                        bothLoadForCall(instrs, leftCallRetVar,leftCallRetVar, rightCallRetVar, node.op);
                    }
                }
            }else if(auto *rightMethodCall = dynamic_cast<ExprMethodcall *>(& *node.right)){
                //todo
                auto leftCallInstrs = visit(*leftCall);
                std::vector<std::shared_ptr<IRNode>> methodCallInstrs = visit(*rightMethodCall);
                if(auto *leftCallLastInstr = dynamic_cast<IRCall *>(& *leftCallInstrs[leftCallInstrs.size() - 1])){
                    auto leftCallRetVar = leftCallLastInstr->retVar;
                    auto lastInstr = methodCallInstrs[methodCallInstrs.size() - 1];
                    if(auto *q = dynamic_cast<IRCall *>(& *lastInstr)){
                        auto rightMethodCallRetVar = q->retVar;
                        for(auto & instr : leftCallInstrs){
                            instrs.push_back(instr);
                        }
                        for(auto & instr : methodCallInstrs){
                            instrs.push_back(instr);
                        }
                        bothLoadForCall(instrs, leftCallRetVar,leftCallRetVar, rightMethodCallRetVar, node.op);
                    }
                }
            }else if(auto *rightOpBinary = dynamic_cast<ExprOpbinary *>(& *node.right)){
                //todo nested binary op on right
                auto leftCallInstrs = visit(*leftCall);
                std::vector<std::shared_ptr<IRNode>> rightInstrs = visit(*rightOpBinary);
                if(auto *leftCallLastInstr = dynamic_cast<IRCall *>(& *leftCallInstrs[leftCallInstrs.size() - 1])){
                    auto leftCallRetVar = leftCallLastInstr->retVar;
                    for(auto & instr : leftCallInstrs){
                        instrs.push_back(instr);
                    }
                    for(auto & instr : rightInstrs){
                        instrs.push_back(instr);
                    }
                    if(auto *rightLastInster = dynamic_cast<IRBinaryop *>(& *rightInstrs[rightInstrs.size() -1]) ){
                        auto rightRetVar = rightLastInster->result;
                        bothLoadForCall(instrs, leftCallRetVar,leftCallRetVar, rightRetVar, node.op);
                    }
                }
            }
        }else if(auto *leftMethodCall = dynamic_cast<ExprMethodcall *>(& *node.left)){
            //todo
            if(auto *rightPath = dynamic_cast<ExprPath *>(& *node.right)){
                std::vector<std::shared_ptr<IRNode>> methodCallInstrs = visit(*leftMethodCall);
                auto lastInstr = methodCallInstrs[methodCallInstrs.size() - 1];
                if(auto *q = dynamic_cast<IRCall *>(& *lastInstr)){
                    auto leftMethodCallRetVar = q->retVar;
                    if(rightPath->pathFirst->pathSegments.type == IDENTIFIER){
                        std::string rightVarName = rightPath->pathFirst->pathSegments.identifier;
                        auto rightVarSymbol = currentScope->lookupValueSymbol(rightVarName);
                        if(rightVarSymbol){
                            for(auto & instr : methodCallInstrs){
                                instrs.push_back(instr);
                            }
                            auto rightLoadedVar = std::make_shared<IRVar>();
                            instrs.push_back(std::make_shared<IRLoad>(rightLoadedVar, rightVarSymbol, rightVarSymbol->type));
                            bothLoadForCall(instrs, rightVarSymbol,leftMethodCallRetVar, rightLoadedVar, node.op);
                        }else{
                            constInfo rightRes = currentScope->lookupConstantSymbol(rightVarName);
                            for(auto & instr : methodCallInstrs){
                                instrs.push_back(instr);
                            }
                            leftLoadRightLiteral(instrs, leftMethodCallRetVar, nullptr, node.op, rightRes,true);
                        }
                    }
                }
            }else if(auto *rightLiteral = dynamic_cast<ExprLiteral *>(& *node.right)){
                std::vector<std::shared_ptr<IRNode>> methodCallInstrs = visit(*leftMethodCall);
                auto lastInstr = methodCallInstrs[methodCallInstrs.size() - 1];
                if(auto *q = dynamic_cast<IRCall *>(& *lastInstr)){
                    auto leftMethodCallRetVar = q->retVar;
                    constInfo res = {rightLiteral->integer, "null"};
                    for(auto & instr : methodCallInstrs){
                        instrs.push_back(instr);
                    }
                    leftLoadRightLiteral(instrs, leftMethodCallRetVar, nullptr, node.op, res,true);
                }
            }else if(auto *rightCall = dynamic_cast<ExprCall *>(& *node.right)){
                std::vector<std::shared_ptr<IRNode>> leftMethodCallInstrs = visit(*leftMethodCall);
                auto rightCallInstrs = visit(*rightCall);
                auto lastInstr = leftMethodCallInstrs[leftMethodCallInstrs.size() - 1];
                if(auto *q = dynamic_cast<IRCall *>(& *lastInstr)){
                    auto leftMethodCallRetVar = q->retVar;
                    if(auto *rightCallLastInstr = dynamic_cast<IRCall *>(& *rightCallInstrs[rightCallInstrs.size() - 1])){
                        auto rightCallRetVar = rightCallLastInstr->retVar;
                        for(auto & instr : leftMethodCallInstrs){
                            instrs.push_back(instr);
                        }
                        for(auto & instr : rightCallInstrs){
                            instrs.push_back(instr);
                        }
                        bothLoadForCall(instrs, leftMethodCallRetVar,leftMethodCallRetVar, rightCallRetVar, node.op);
                    }
                }
            }else if(auto *rightMethodCall = dynamic_cast<ExprMethodcall *>(& *node.right)){
                //todo
                std::vector<std::shared_ptr<IRNode>> leftMethodCallInstrs = visit(*leftMethodCall);
                std::vector<std::shared_ptr<IRNode>> methodCallInstrs = visit(*rightMethodCall);
                auto lastInstr = leftMethodCallInstrs[leftMethodCallInstrs.size() - 1];
                if(auto *q = dynamic_cast<IRCall *>(& *lastInstr)){
                    auto leftMethodCallRetVar = q->retVar;
                    auto rightLastInstr = methodCallInstrs[methodCallInstrs.size() - 1];
                    if(auto *rightQ = dynamic_cast<IRCall *>(& *rightLastInstr)){
                        auto rightMethodCallRetVar = rightQ->retVar;
                        for(auto & instr : leftMethodCallInstrs){
                            instrs.push_back(instr);
                        }
                        for(auto & instr : methodCallInstrs){
                            instrs.push_back(instr);
                        }
                        bothLoadForCall(instrs, leftMethodCallRetVar,leftMethodCallRetVar, rightMethodCallRetVar, node.op);
                    }
                }
            }else if(auto *rightOpBinary = dynamic_cast<ExprOpbinary *>(& *node.right)){
                //todo nested binary op on right
                std::vector<std::shared_ptr<IRNode>> leftMethodCallInstrs = visit(*leftMethodCall);
                std::vector<std::shared_ptr<IRNode>> rightInstrs = visit(*rightOpBinary);
                auto lastInstr = leftMethodCallInstrs[leftMethodCallInstrs.size() - 1];
                if(auto *q = dynamic_cast<IRCall *>(& *lastInstr)){
                    auto leftMethodCallRetVar = q->retVar;
                    for(auto & instr : leftMethodCallInstrs){
                        instrs.push_back(instr);
                    }
                    for(auto & instr : rightInstrs){
                        instrs.push_back(instr);
                    }
                    if(auto *rightLastInster = dynamic_cast<IRBinaryop *>(& *rightInstrs[rightInstrs.size() -1]) ){
                        auto rightRetVar = rightLastInster->result;
                        bothLoadForCall(instrs, leftMethodCallRetVar,leftMethodCallRetVar, rightRetVar, node.op);
                    }
                }
            }
        }else if(auto *leftOpBinary = dynamic_cast<ExprOpbinary *>(& *node.left)){
            //todo nested binary op
            std::vector<std::shared_ptr<IRNode>> leftInstrs = visit(*leftOpBinary);
            for(auto & instr : leftInstrs){
                instrs.push_back(instr);
            }
            if(auto *leftLastInster = dynamic_cast<IRBinaryop *>(& *leftInstrs[leftInstrs.size() -1]) ){
                auto leftRetVar = leftLastInster->result;
                if(auto *rightPath = dynamic_cast<ExprPath *>(& *node.right)){
                    if(rightPath->pathFirst->pathSegments.type == IDENTIFIER){
                        std::string rightVarName = rightPath->pathFirst->pathSegments.identifier;
                        auto rightVarSymbol = currentScope->lookupValueSymbol(rightVarName);
                        if(rightVarSymbol){
                            auto rightLoadedVar = std::make_shared<IRVar>();
                            instrs.push_back(std::make_shared<IRLoad>(rightLoadedVar, rightVarSymbol, rightVarSymbol->type));
                            bothLoadForCall(instrs, rightVarSymbol,leftRetVar, rightLoadedVar, node.op);
                        }else{
                            if(rightVarName == "usize" || rightVarName == "isize" ){
                                if(node.op == AS_CAST){
                                    auto leftLoadedVar = std::make_shared<IRVar>();
                                    instrs.push_back(std::make_shared<IRLoad>(leftLoadedVar, leftRetVar, leftRetVar->type));
                                    auto resultVar = std::make_shared<IRVar>();
                                    //todo cast instr
                                    if(leftRetVar->type == currentScope->lookupTypeSymbol("i32")){
                                        instrs.push_back(std::make_shared<IRSext>(currentScope->lookupTypeSymbol("i32"),leftLoadedVar, currentScope->lookupTypeSymbol("isize"), resultVar));
                                        resultVar->type = currentScope->lookupTypeSymbol("isize");
                                    }else if(leftRetVar->type == currentScope->lookupTypeSymbol("u32")){
                                        instrs.push_back(std::make_shared<IRZext>(currentScope->lookupTypeSymbol("i32"),leftLoadedVar, currentScope->lookupTypeSymbol("isize"), resultVar));
                                        resultVar->type = currentScope->lookupTypeSymbol("isize");
                                    }
                                }
                            }else if(rightVarName == "u32" || rightVarName == "i32" ){
                                if(node.op == AS_CAST){
                                    auto leftLoadedVar = std::make_shared<IRVar>();
                                    instrs.push_back(std::make_shared<IRLoad>(leftLoadedVar, leftRetVar, leftRetVar->type));
                                    auto resultVar = std::make_shared<IRVar>();
                                    //todo cast instr
                                    if(leftRetVar->type == currentScope->lookupTypeSymbol("isize")){
                                        instrs.push_back(std::make_shared<IRTrunc>(currentScope->lookupTypeSymbol("isize"),leftLoadedVar, currentScope->lookupTypeSymbol("i32"), resultVar));
                                        resultVar->type = currentScope->lookupTypeSymbol("i32");
                                    }else if(leftRetVar->type == currentScope->lookupTypeSymbol("usize")){  
                                        instrs.push_back(std::make_shared<IRTrunc>(currentScope->lookupTypeSymbol("isize"),leftLoadedVar, currentScope->lookupTypeSymbol("u32"), resultVar));
                                        resultVar->type = currentScope->lookupTypeSymbol("i32");
                                    }
                                }
                            }else{
                                constInfo res = currentScope->lookupConstantSymbol(rightVarName);
                                leftLoadRightLiteral(instrs, leftRetVar, nullptr, node.op, res,true);
                            }
                        }
                    }
                }else if(auto *rightLiteral = dynamic_cast<ExprLiteral *>(& *node.right)){
                    constInfo res = {rightLiteral->integer, "null"};
                    leftLoadRightLiteral(instrs, leftRetVar, nullptr, node.op, res,true);
                }else if(auto *rightCall = dynamic_cast<ExprCall *>(& *node.right)){
                    auto rightCallInstrs = visit(*rightCall);
                    if(auto *rightCallLastInstr = dynamic_cast<IRCall *>(& *rightCallInstrs[rightCallInstrs.size() - 1])){
                        auto rightCallRetVar = rightCallLastInstr->retVar;
                        for(auto & instr : rightCallInstrs){
                            instrs.push_back(instr);
                        }
                        bothLoadForCall(instrs, rightCallRetVar,leftRetVar, rightCallRetVar, node.op);
                    }
                }else if(auto *rightMethodCall = dynamic_cast<ExprMethodcall *>(& *node.right)){
                    //todo
                }else if(auto *rightOpBinary = dynamic_cast<ExprOpbinary *>(& *node.right)){
                    //todo nested binary op on right
                    std::vector<std::shared_ptr<IRNode>> rightInstrs = visit(*rightOpBinary);
                    for(auto & instr : rightInstrs){
                        instrs.push_back(instr);
                    }
                    if(auto *rightLastInster = dynamic_cast<IRBinaryop *>(& *rightInstrs[rightInstrs.size() -1]) ){
                        auto rightRetVar = rightLastInster->result;
                        bothLoadForCall(instrs, leftRetVar,leftRetVar, rightRetVar, node.op);
                    }
                }
            }
        }else if(auto *leftUnary = dynamic_cast<ExprOpunary *>(& *node.left)){
            //todo
            if(leftUnary->op == DEREFERENCE){
                if(auto *rightLiteral = dynamic_cast<ExprLiteral *>(& *node.right)){
                    auto leftUnaryInstrs = visit(*leftUnary);
                    for(auto & instr : leftUnaryInstrs){
                        instrs.push_back(instr);
                    }
                    auto lastInstr = leftUnaryInstrs[leftUnaryInstrs.size() - 1];
                    if(auto *q = dynamic_cast<IRLoad *>(& *lastInstr)){
                        auto derefVar = q->tmp;
                        constInfo res = {rightLiteral->integer, "null"};
                        leftLoadRightLiteral(instrs, derefVar, nullptr, node.op, res,true);
                    }
                }
            }
        }
        return instrs;
    }

    std::vector<std::shared_ptr<IRNode>> visit(ExprOpunary &node){
        std::vector<std::shared_ptr<IRNode>> instrs;
        if(node.op == DEREFERENCE){
            if(auto *path = dynamic_cast<ExprPath *>(& *node.right)){
                if(path->pathFirst->pathSegments.type == IDENTIFIER){
                    std::string varName = path->pathFirst->pathSegments.identifier;
                    auto varSymbol = currentScope->lookupValueSymbol(varName);
                    if(varSymbol){
                        auto loadedVar = std::make_shared<IRVar>();
                        loadedVar->type = varSymbol->type;
                        instrs.push_back(std::make_shared<IRLoad>(loadedVar, varSymbol, loadedVar->type));
                        auto resultVar = std::make_shared<IRVar>();
                        if(auto *ptrType = dynamic_cast<IRPtrType *>(& *varSymbol->type)){
                            resultVar->type = ptrType->baseType;
                        }
                        instrs.push_back(std::make_shared<IRLoad>(resultVar, loadedVar, resultVar->type));
                        return instrs;
                    }
                }
            }
        }
        return instrs;
    }

    std::vector<std::shared_ptr<IRNode>> visit(ExprPath &node){
        return {};
    }

    std::vector<std::shared_ptr<IRNode>> visit(ExprReturn &node){
        std::vector<std::shared_ptr<IRNode>> instrs;
        if(auto *retExpr = dynamic_cast<ExprLiteral *>(& *node.expr)){
            instrs.push_back(std::make_shared<IRReturn>(currentScope->lookupTypeSymbol("i32"), std::make_shared<IRLiteral>(INT_LITERAL, retExpr->integer)));
        }else if(auto *retPath = dynamic_cast<ExprPath *>(& *node.expr)){
            if(retPath->pathFirst->pathSegments.type == IDENTIFIER){
                std::string retVarName = retPath->pathFirst->pathSegments.identifier;
                auto retVarSymbol = currentScope->lookupValueSymbol(retVarName);
                if(retVarSymbol){
                    auto retLoadedVar = std::make_shared<IRVar>();
                    instrs.push_back(std::make_shared<IRLoad>(retLoadedVar, retVarSymbol, retVarSymbol->type));
                    instrs.push_back(std::make_shared<IRReturn>(retVarSymbol->type, retLoadedVar));
                }else {
                    constInfo res = currentScope->lookupConstantSymbol(retVarName);
                    instrs.push_back(std::make_shared<IRReturn>(currentScope->lookupTypeSymbol(res.type), std::make_shared<IRLiteral>(INT_LITERAL, res.value)));
                }
            }
        }else if(auto *retCall = dynamic_cast<ExprCall *>(& *node.expr)){
            auto callInstrs = visit(*retCall);
            for(auto & instr : callInstrs){
                instrs.push_back(instr);
            }
            if(auto *callLastInstr = dynamic_cast<IRCall *>(& *callInstrs[callInstrs.size() - 1])){
                auto retVar = callLastInstr->retVar;
                instrs.push_back(std::make_shared<IRReturn>(retVar->type, retVar));
            }
        }else if(auto *retMethodCall = dynamic_cast<ExprMethodcall *>(& *node.expr)){
            auto methodCallInstrs = visit(*retMethodCall);
            for(auto & instr : methodCallInstrs){
                instrs.push_back(instr);
            }
            if(auto *methodCallLastInstr = dynamic_cast<IRCall *>(& *methodCallInstrs[methodCallInstrs.size() - 1])){
                auto retVar = methodCallLastInstr->retVar;
                instrs.push_back(std::make_shared<IRReturn>(retVar->type, retVar));
            }
        }else if(auto *retOpBinary = dynamic_cast<ExprOpbinary *>(& *node.expr)){
            auto opBinaryInstrs = visit(*retOpBinary);
            for(auto & instr : opBinaryInstrs){
                instrs.push_back(instr);
            }
            if(auto *opBinaryLastInstr = dynamic_cast<IRBinaryop *>(& *opBinaryInstrs[opBinaryInstrs.size() - 1])){
                auto retVar = opBinaryLastInstr->result;
                instrs.push_back(std::make_shared<IRReturn>(retVar->type, retVar));
            }
        }
        return instrs;
    }

    std::vector<std::shared_ptr<IRNode>> visit(ExprStruct &node){
        std::vector<std::shared_ptr<IRNode>> instrs;
        if(auto *p = dynamic_cast<ExprPath *>(& *node.pathInExpr)){
            if(p->pathFirst->pathSegments.type == IDENTIFIER){
                std::string structName = p->pathFirst->pathSegments.identifier;
                auto structTypeSymbol = currentScope->lookupTypeSymbol(structName);
                if(auto *structType = dynamic_cast<IRStructType *>(& *structTypeSymbol)){
                    auto structVar =  std::make_shared<IRVar>();
                    structVar->type = structTypeSymbol;
                    instrs.push_back(std::make_shared<IRAlloca>(structTypeSymbol, structVar));
                    //todo
                }
            }
        }
    }

    std::vector<std::shared_ptr<IRNode>> visit(ExprUnderscore &node){
        return {};
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

    // function param not adding to func irscope here
    std::shared_ptr<IRFunction> visit(ItemFnDecl &node){
        auto currentIRFunc = currentScope->lookupFunctionSymbol(node.identifier);
        auto funcScope = std::make_shared<IRScope>();
        funcScope->parent = currentScope;
        currentScope->children.push_back(funcScope);
        currentScope = funcScope;
        //add parameters to func scope
        for(auto &param: currentIRFunc->paramList->paramList){
            //todo
            if(auto p = std::dynamic_pointer_cast<IRVar>(param)){
                //currentScope->addValueSymbol(p->varName, p);
                auto bodyVar = std::make_shared<IRVar>();
                bodyVar->varName = p->varName;
                bodyVar->reName = p->reName;
                bodyVar->type = p->type;
                currentIRFunc->body->instrList.push_back(std::make_shared<IRAlloca>(p->type, bodyVar));
                currentIRFunc->body->instrList.push_back(std::make_shared<IRStore>(p->type, p, nullptr, bodyVar));
                currentScope->addValueSymbol(p->varName, bodyVar);
            }
        }
        if(node.fnBody){
            for(auto & stmt : node.fnBody->statements){
                if(auto *itemStmt = dynamic_cast<StmtItem *>(& *stmt)){
                    if(auto *p = dynamic_cast<ItemConstDecl *>(& *itemStmt)){
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
                    }else if(auto *p = dynamic_cast<ItemEnumDecl *>(& *itemStmt)){
                        //todo idk just wait and see
                    }else if(auto *p = dynamic_cast<ItemFnDecl *>(& *itemStmt)){
                        std::shared_ptr<IRType> returnType;
                        if(p->returnType){
                            returnType = resolveType(*p->returnType);
                        }
                        std::string funcName = p->identifier;
                        std::shared_ptr<IRParam> irParam;
                        if(node.fnParameters.SelfParam.isShortSelf){
                            auto selfType = std::make_shared<IRSelf>();
                            irParam->paramList.push_back(selfType);
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
                                }
                                irParam->paramList.push_back(currentVar);
                            }
                        }
                        auto currentFunction = std::make_shared<IRFunction>();
                        currentFunction->name = funcName;
                        currentFunction->retType = returnType;
                        currentFunction->paramList = irParam;
                        currentScope->addFunctionSymbol(funcName, currentFunction);
                    }else if(auto *p = dynamic_cast<ItemImplDecl *>(& *itemStmt)){
                        //no need to do anything
                    }else if(auto *p = dynamic_cast<ItemStructDecl *>(& *itemStmt)){
                        //todo
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
                        currentScope->addTypeSymbol(structName, currentStruct);
                    }else if(auto *p = dynamic_cast<ItemTraitDecl *>(& *itemStmt)){
                        //no need to do anything
                    }
                }
            }
        }
        if(node.fnBody){
            //std::vector<std::shared_ptr<IRBlock>> blocks;
            for(auto & stmt : node.fnBody->statements){
                //todo todo todo !!!
                if(auto *p = dynamic_cast<StmtExpr *>(& *stmt)){
                    //todo
                    if(auto *q = dynamic_cast<ExprIf *>(& *p->stmtExpr)){
                        auto IfBlocks = visit(*q);
                        if(currentIRFunc->body->blockList.size() == 0){
                            for(auto &instr: IfBlocks->instrList){
                                currentIRFunc->body->instrList.push_back(instr);
                            }
                            for(auto & block : IfBlocks->blockList){
                                currentIRFunc->body->blockList.push_back(block);
                            }
                        }else{
                            currentIRFunc->body->blockList.push_back(IfBlocks);
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
                            currentIRFunc->body->blockList.push_back(LoopBlocks);
                            for(auto & block : LoopBlocks->blockList){
                                currentIRFunc->body->blockList.push_back(block);
                            }
                        }
                    }else{
                        auto exprInstrs = visit(*p->stmtExpr);
                        if(currentIRFunc->body->blockList.size() == 0){
                            for(auto & instr : exprInstrs){
                                currentIRFunc->body->instrList.push_back(instr);
                            }
                        }else{
                            for(auto & instr : exprInstrs){
                                currentIRFunc->body->blockList[currentIRFunc->body->blockList.size() - 1]->instrList.push_back(instr);
                            }
                        }
                    }
                }else if(auto *p = dynamic_cast<StmtLet *>(& *stmt)){
                    auto letInstrs = visit(*p);
                    if(currentIRFunc->body->blockList.size() == 0){
                         for(auto & instr : letInstrs){
                            currentIRFunc->body->instrList.push_back(instr);
                        }
                    }else{
                        for(auto & instr : letInstrs){
                            currentIRFunc->body->blockList[currentIRFunc->body->blockList.size() - 1]->instrList.push_back(instr);
                        }
                    }
                }
            }
            if(node.fnBody->ExpressionWithoutBlock){
                if(auto *retExpr = dynamic_cast<ExprPath *>(& *node.fnBody->ExpressionWithoutBlock)){
                    if(retExpr->pathFirst->pathSegments.type == IDENTIFIER){
                        std::string retVarName = retExpr->pathFirst->pathSegments.identifier;
                        auto retVarSymbol = currentScope->lookupValueSymbol(retVarName);
                        if(retVarSymbol){
                            auto retLoadedVar = std::make_shared<IRVar>();
                            if(currentIRFunc->body->blockList.size() == 0){
                                retLoadedVar->type = retVarSymbol->type;
                                currentIRFunc->body->instrList.push_back(std::make_shared<IRLoad>(retLoadedVar, retVarSymbol, retVarSymbol->type));
                                currentIRFunc->body->instrList.push_back(std::make_shared<IRReturn>(retVarSymbol->type, retLoadedVar));
                            }else{
                                retLoadedVar->type = retVarSymbol->type;
                                currentIRFunc->body->blockList[currentIRFunc->body->blockList.size() - 1]->instrList.push_back(std::make_shared<IRLoad>(retLoadedVar, retVarSymbol, retVarSymbol->type));
                                currentIRFunc->body->blockList[currentIRFunc->body->blockList.size() - 1]->instrList.push_back(std::make_shared<IRReturn>(retVarSymbol->type, retLoadedVar));
                            }
                        }
                    }
                }else if(auto *retLiteral = dynamic_cast<ExprLiteral *>(& *node.fnBody->ExpressionWithoutBlock)){
                    if(currentIRFunc->body->blockList.size() == 0){
                        currentIRFunc->body->instrList.push_back(std::make_shared<IRReturn>(currentIRFunc->retType, std::make_shared<IRLiteral>(INT_LITERAL, retLiteral->integer)));
                    }else{
                        currentIRFunc->body->blockList[currentIRFunc->body->blockList.size() - 1]->instrList.push_back(std::make_shared<IRReturn>(currentIRFunc->retType, std::make_shared<IRLiteral>(INT_LITERAL, retLiteral->integer)));
                    }
                }else if(auto *retBinaryOp = dynamic_cast<ExprOpbinary *>(& *node.fnBody->ExpressionWithoutBlock)){
                    auto retInstrs = visit(*retBinaryOp);
                    if(currentIRFunc->body->blockList.size() == 0){
                        for(auto & instr : retInstrs){
                            currentIRFunc->body->instrList.push_back(instr);
                        }
                        if(auto *lastInstr = dynamic_cast<IRBinaryop *>(& *retInstrs[retInstrs.size() - 1])){
                            currentIRFunc->body->instrList.push_back(std::make_shared<IRReturn>(currentIRFunc->retType, lastInstr->result));
                        }
                    }else{
                        for(auto & instr : retInstrs){
                            currentIRFunc->body->blockList[currentIRFunc->body->blockList.size() - 1]->instrList.push_back(instr);
                        }
                        if(auto *lastInstr = dynamic_cast<IRBinaryop *>(& *retInstrs[retInstrs.size() - 1])){
                            currentIRFunc->body->blockList[currentIRFunc->body->blockList.size() - 1]->instrList.push_back(std::make_shared<IRReturn>(currentIRFunc->retType, lastInstr->result));
                        }
                    }
                }
            }
        }
        //deal with return todo!
        currentScope = currentScope->parent;
        if(currentIRFunc->name == "main"){
            if(currentIRFunc->body->blockList.size() == 0){
                currentIRFunc->body->instrList.push_back(std::make_shared<IRReturn>(currentScope->lookupTypeSymbol("i32"), std::make_shared<IRLiteral>(INT_LITERAL, 0)));
            }else{
                currentIRFunc->body->blockList[currentIRFunc->body->blockList.size() - 1]->instrList.push_back(std::make_shared<IRReturn>(currentScope->lookupTypeSymbol("i32"), std::make_shared<IRLiteral>(INT_LITERAL, 0)));
            }
        }
        
        return currentIRFunc;
    }


    std::shared_ptr<IRImpl> visit(ItemImplDecl &node){
        std::shared_ptr<IRImpl> implNode = std::make_shared<IRImpl>();
        if(auto *p = dynamic_cast<ExprPath *>(& *node.targetType)){
            if(p->pathFirst->pathSegments.type == IDENTIFIER){
                std::string structName = p->pathFirst->pathSegments.identifier;
                auto Type = currentScope->lookupTypeSymbol(structName);
                if(Type){
                    //todo add methods to structType
                    int j = 0;
                    if(auto *structType = dynamic_cast<IRStructType *>(& *Type)){
                        implNode->mainStructType = Type;
                        for(int i = 0;i < structType->memberFunctions.size();i ++){
                            //todo finish method adding
                            if(node.item_trait_fn[j]->identifier == structType->memberFunctions[i]->name){
                                structType->memberFunctions[i] = visit(*node.item_trait_fn[j]);
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
    std::vector<std::shared_ptr<IRNode>> visit(Statement &node){
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

    std::vector<std::shared_ptr<IRNode>> visit(StmtEmpty &node){
        return {};
    }

    std::vector<std::shared_ptr<IRNode>> visit(StmtExpr &node);

    std::vector<std::shared_ptr<IRNode>> visit(StmtItem &node){
        std::vector<std::shared_ptr<IRNode>> res;
        res.push_back(visit(*node.stmt_item));
        return res;
    }

    std::vector<std::shared_ptr<IRNode>> visit(StmtLet &node){
        std::vector<std::shared_ptr<IRNode>> instrs;
        //todo
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
        //todo
        std::shared_ptr<IRType> varType = resolveType(*node.type);
        auto currentVar = std::make_shared<IRVar>(varType,varName, reName);
        currentScope->addValueSymbol(varName, currentVar);
        instrs.push_back(std::make_shared<IRAlloca>(varType,currentVar));
        //todo init expr
        if(node.expression){
            if(auto *exprPath = dynamic_cast<ExprPath *>(& *node.expression)){
                if(exprPath->pathFirst->pathSegments.type == IDENTIFIER){
                    std::string initVarName = exprPath->pathFirst->pathSegments.identifier;
                    auto initVarSymbol = currentScope->lookupValueSymbol(initVarName);
                    if(initVarSymbol){
                        auto loadedVar = std::make_shared<IRVar>();
                        instrs.push_back(std::make_shared<IRLoad>(loadedVar, initVarSymbol, initVarSymbol->type));
                        instrs.push_back(std::make_shared<IRStore>(varType,loadedVar,nullptr,currentVar));
                    }else{
                        constInfo res = currentScope->lookupConstantSymbol(initVarName);
                        auto literalVar = std::make_shared<IRLiteral>();
                        literalVar->literalType = INT_LITERAL;
                        literalVar->intValue = res.value;
                        instrs.push_back(std::make_shared<IRStore>(varType,nullptr, literalVar, currentVar));
                    }
                }
            }else if(auto *exprLiteral = dynamic_cast<ExprLiteral *>(& *node.expression)){
                auto literalVar = std::make_shared<IRLiteral>();
                literalVar->literalType = INT_LITERAL;
                literalVar->intValue = exprLiteral->integer;
                instrs.push_back(std::make_shared<IRStore>(varType,nullptr, literalVar, currentVar));
            }else if(auto *exprCall = dynamic_cast<ExprCall *>(& *node.expression)){
                auto callInstrs = visit(*exprCall);
                if(auto *callLastInstr = dynamic_cast<IRCall *>(& *callInstrs[callInstrs.size() - 1])){
                    auto callRetVar = callLastInstr->retVar;
                    for(auto & instr : callInstrs){
                        instrs.push_back(instr);
                    }
                    // auto loadedVar = std::make_shared<IRVar>();
                    // instrs.push_back(std::make_shared<IRLoad>(loadedVar, callRetVar, callRetVar->type));
                    instrs.push_back(std::make_shared<IRStore>(varType, callRetVar,nullptr ,currentVar));
                }
            }else if(auto *exprMethodCall = dynamic_cast<ExprMethodcall *>(& *node.expression)){
                auto methodCallInstrs = visit(*exprMethodCall);
                auto lastInstr = methodCallInstrs[methodCallInstrs.size() - 1];
                if(auto *q = dynamic_cast<IRCall *>(& *lastInstr)){
                    auto methodCallRetVar = q->retVar;
                    for(auto & instr : methodCallInstrs){
                        instrs.push_back(instr);
                    }
                    // auto loadedVar = std::make_shared<IRVar>();
                    // instrs.push_back(std::make_shared<IRLoad>(loadedVar, methodCallRetVar, methodCallRetVar->type));
                    instrs.push_back(std::make_shared<IRStore>(varType, methodCallRetVar,nullptr, currentVar));
                }
            }else if(auto *exprOpbinary = dynamic_cast<ExprOpbinary *>(& *node.expression)){
                auto exprInstrs = visit(*exprOpbinary);
                if(auto *exprLastInstr = dynamic_cast<IRBinaryop *>(& *exprInstrs[exprInstrs.size() - 1])){
                    auto exprRetVar = exprLastInstr->result;
                    for(auto & instr : exprInstrs){
                        instrs.push_back(instr);
                    }
                    instrs.push_back(std::make_shared<IRStore>(varType, exprRetVar,nullptr, currentVar));
                }
            }
        }
        return instrs;
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
        return std::make_shared<IRArrayType>(currentType, size);
    }

    std::shared_ptr<IRStructType> visit(Path &node){
        return nullptr;
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