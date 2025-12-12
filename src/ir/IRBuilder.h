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
#include "IRReturn.h"
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
            irRoot->children.push_back(visit(*item));
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
        }else if(auto *p = dynamic_cast<ExprIf *>(& node)) {
            return visit(*p);
        }else if(auto *p = dynamic_cast<ExprIndex *>(& node)) {
            return visit(*p);
        }else if(auto *p = dynamic_cast<ExprLiteral *>(& node)) {
            return visit(*p);
        }else if(auto *p = dynamic_cast<ExprLoop *>(& node)) {
            return visit(*p);
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
        if(!node.arrayExpr.empty()){
            //TODO: have no idea yet
        }else{
            // rmk: 疑似在建ASTNode的时候认为是 [type;size] ，实际上是和ArrayType搞混了
            // 所以这里的type完全是一个虚假的名字 应该是
            // [initial;size] 滑跪了
            
        }
    }

    std::vector<std::shared_ptr<IRNode>> visit(ExprBlock &node);

    std::vector<std::shared_ptr<IRNode>> visit(ExprBreak &node);

    std::vector<std::shared_ptr<IRNode>> visit(ExprCall &node){
        std::vector<std::shared_ptr<IRNode>> instrs;
        std::string funcName = "";
        if(auto *p = dynamic_cast<ExprPath *>(& *node.expr)){
            if(p->pathFirst->pathSegments.type == IDENTIFIER){
                funcName = p->pathFirst->pathSegments.identifier;
            }
        }
        auto currentIRFunc = currentScope->lookupFunctionSymbol(funcName);
        auto currentCallInstr = std::make_shared<IRCall>();
        currentCallInstr->function = currentIRFunc;
        auto callRet = std::make_shared<IRVar>();
        currentCallInstr->retVar = callRet;
        for(auto & arg : node.callParams){
            //TODO process arguments
            if(auto *p = dynamic_cast<ExprPath *>(& *arg)){
                if(p->pathFirst->pathSegments.type == IDENTIFIER){
                    std::string varName = p->pathFirst->pathSegments.identifier;
                    auto varSymbol = currentScope->lookupValueSymbol(varName);
                    //TODO load instruction
                    if(varSymbol == nullptr){
                        //constant
                        long long int res = currentScope->lookupConstantSymbol(varName);
                        currentCallInstr->pList->paramList.push_back(std::make_shared<IRLiteral>(INT_LITERAL, res));
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
                    currentCallInstr->pList->paramList.push_back(std::make_shared<IRLiteral>(INT_LITERAL, p->constValue));
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

    std::vector<std::shared_ptr<IRNode>> visit(ExprContinue &node);

    std::vector<std::shared_ptr<IRNode>> visit(ExprField &node);

    std::vector<std::shared_ptr<IRNode>> visit(ExprGroup &node){
        return {};
    }

    std::vector<std::shared_ptr<IRNode>> visit(ExprIf &node){
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
        //todo br 
        auto trueBlock = std::make_shared<IRBlock>();
        auto falseBlock = std::make_shared<IRBlock>();
        instrs.push_back(std::make_shared<IRBr>(condVar, trueBlock, falseBlock));
        //todo true block
        auto ifScope = std::make_shared<IRScope>();
        ifScope->parent = currentScope;
        currentScope->children.push_back(ifScope);
        currentScope = ifScope;
        //todo
        if(node.thenBlock){
            bool hasReturn = false;
            for(auto & stmt : node.thenBlock->statements){
                if(auto *m = dynamic_cast<StmtExpr *>(& *stmt)){
                    if(auto *retCheck = dynamic_cast<ExprReturn *>(& *m->stmtExpr)){
                        hasReturn = true;
                        break;
                    }
                }
                auto blockInstrs = visit(*stmt);
                for(auto & instr : blockInstrs){
                    trueBlock->instrList.push_back(instr);
                }
            }
            if(hasReturn){

            }
            if(node.thenBlock->ExpressionWithoutBlock){
                //todo about br instruction
            }
        }
        currentScope = currentScope->parent;
        //todo false block
        if(node.elseBlock){

        }else{

        }
    }
    std::vector<std::shared_ptr<IRNode>> visit(ExprIndex &node);

    std::vector<std::shared_ptr<IRNode>> visit(ExprLiteral &node);

    std::vector<std::shared_ptr<IRNode>> visit(ExprLoop &node);

    std::vector<std::shared_ptr<IRNode>> visit(ExprMethodcall &node);

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
        }
        throw std::runtime_error("IRBuilder turnBinaryOp error: unknown binary op");
    }

    void bothLoad(std::vector<std::shared_ptr<IRNode>> &instrs,std::shared_ptr<IRVar> leftVarSymbol, std::shared_ptr<IRVar> rightVarSymbol,binaryOp op){
        auto leftLoadedVar = std::make_shared<IRVar>();
        auto rightLoadedVar = std::make_shared<IRVar>();
        instrs.push_back(std::make_shared<IRLoad>(leftLoadedVar, leftVarSymbol, leftVarSymbol->type));
        instrs.push_back(std::make_shared<IRLoad>(rightLoadedVar, rightVarSymbol, rightVarSymbol->type));
        auto resultVar = std::make_shared<IRVar>();
        //todo get binary op
        IROp irOp = turnBinaryOp(op);
        if(irOp == ADD){
            instrs.push_back(std::make_shared<IRAdd>(leftLoadedVar,nullptr, rightLoadedVar, nullptr, resultVar));
        }else if(irOp == SUB){
            instrs.push_back(std::make_shared<IRSub>(leftLoadedVar,nullptr, rightLoadedVar, nullptr, resultVar));   
        }else if(irOp == MUL){
            instrs.push_back(std::make_shared<IRMul>(leftLoadedVar,nullptr, rightLoadedVar, nullptr, resultVar));
        }else if(irOp == DIV){
            instrs.push_back(std::make_shared<IRDiv>(leftLoadedVar,nullptr, rightLoadedVar, nullptr, resultVar));   
        }else if(irOp == MOD){
            instrs.push_back(std::make_shared<IRMod>(leftLoadedVar,nullptr, rightLoadedVar, nullptr, resultVar));
        }else if(irOp == EQ){
            instrs.push_back(std::make_shared<IREq>(leftLoadedVar,nullptr, rightLoadedVar, nullptr, resultVar));    
        }else if(irOp == NEQ){
            instrs.push_back(std::make_shared<IRNeq>(leftLoadedVar,nullptr, rightLoadedVar, nullptr, resultVar));    
        }else if(irOp == LT){
            instrs.push_back(std::make_shared<IRLt>(leftLoadedVar,nullptr, rightLoadedVar, nullptr, resultVar));    
        }else if(irOp == LEQ){  
            instrs.push_back(std::make_shared<IRLeq>(leftLoadedVar,nullptr, rightLoadedVar, nullptr, resultVar));    
        }else if(irOp == GT){
            instrs.push_back(std::make_shared<IRGt>(leftLoadedVar,nullptr, rightLoadedVar, nullptr, resultVar));    
        }else if(irOp == GEQ){
            instrs.push_back(std::make_shared<IRGeq>(leftLoadedVar,nullptr, rightLoadedVar, nullptr, resultVar));
        }else if(irOp == LOGICALAND){
            instrs.push_back(std::make_shared<IRLogicalAnd>(leftLoadedVar,nullptr, rightLoadedVar, nullptr, resultVar));    
        }else if(irOp == LOGICALOR){
            instrs.push_back(std::make_shared<IRLogicalOr>(leftLoadedVar,nullptr, rightLoadedVar, nullptr, resultVar));
        }else if(irOp == ADD_EQ){
            instrs.push_back(std::make_shared<IRAddEq>(leftLoadedVar,nullptr, rightLoadedVar, nullptr, resultVar));
            instrs.push_back(std::make_shared<IRStore>(leftVarSymbol->type,resultVar,nullptr,leftVarSymbol));
        }else if(irOp == SUB_EQ){
            instrs.push_back(std::make_shared<IRSubEq>(leftLoadedVar,nullptr, rightLoadedVar, nullptr, resultVar));
            instrs.push_back(std::make_shared<IRStore>(leftVarSymbol->type,resultVar,nullptr,leftVarSymbol));
        }else if(irOp == MUL_EQ){
            instrs.push_back(std::make_shared<IRMulEq>(leftLoadedVar,nullptr, rightLoadedVar, nullptr, resultVar));
            instrs.push_back(std::make_shared<IRStore>(leftVarSymbol->type,resultVar,nullptr,leftVarSymbol));
        }else if(irOp == DIV_EQ){
            instrs.push_back(std::make_shared<IRDivEq>(leftLoadedVar,nullptr, rightLoadedVar, nullptr, resultVar));
            instrs.push_back(std::make_shared<IRStore>(leftVarSymbol->type,resultVar,nullptr,leftVarSymbol));
        }else if(irOp == MOD_EQ){
            instrs.push_back(std::make_shared<IRModEq>(leftLoadedVar,nullptr, rightLoadedVar, nullptr, resultVar));
            instrs.push_back(std::make_shared<IRStore>(leftVarSymbol->type,resultVar,nullptr,leftVarSymbol));
        }else {
            throw std::runtime_error("IRBuilder visit ExprOpbinary error: unknown binary op");
        }
    }

    void bothLoadForCall(std::vector<std::shared_ptr<IRNode>> &instrs,std::shared_ptr<IRVar> leftVarSymbol,std::shared_ptr<IRVar> leftLoadedVar, std::shared_ptr<IRVar> rightCallRetVar,binaryOp op){
        auto resultVar = std::make_shared<IRVar>();
        IROp irOp = turnBinaryOp(op);
        if(irOp == ADD){
            instrs.push_back(std::make_shared<IRAdd>(leftLoadedVar,nullptr, rightCallRetVar, nullptr, resultVar));
        }else if(irOp == SUB){
            instrs.push_back(std::make_shared<IRSub>(leftLoadedVar,nullptr, rightCallRetVar, nullptr, resultVar));   
        }else if(irOp == MUL){
            instrs.push_back(std::make_shared<IRMul>(leftLoadedVar,nullptr, rightCallRetVar, nullptr, resultVar));
        }else if(irOp == DIV){
            instrs.push_back(std::make_shared<IRDiv>(leftLoadedVar,nullptr, rightCallRetVar, nullptr, resultVar));   
        }else if(irOp == MOD){
            instrs.push_back(std::make_shared<IRMod>(leftLoadedVar,nullptr, rightCallRetVar, nullptr, resultVar));
        }else if(irOp == EQ){
            instrs.push_back(std::make_shared<IREq>(leftLoadedVar,nullptr, rightCallRetVar, nullptr, resultVar));    
        }else if(irOp == NEQ){
            instrs.push_back(std::make_shared<IRNeq>(leftLoadedVar,nullptr, rightCallRetVar, nullptr, resultVar));    
        }else if(irOp == LT){
            instrs.push_back(std::make_shared<IRLt>(leftLoadedVar,nullptr, rightCallRetVar, nullptr, resultVar));    
        }else if(irOp == LEQ){
            instrs.push_back(std::make_shared<IRLeq>(leftLoadedVar,nullptr, rightCallRetVar, nullptr, resultVar));
        }else if(irOp == GT){
            instrs.push_back(std::make_shared<IRGt>(leftLoadedVar,nullptr, rightCallRetVar, nullptr, resultVar));
        }else if(irOp == GEQ){
            instrs.push_back(std::make_shared<IRGeq>(leftLoadedVar,nullptr, rightCallRetVar, nullptr, resultVar));
        }else if(irOp == LOGICALAND){
            instrs.push_back(std::make_shared<IRLogicalAnd>(leftLoadedVar,nullptr, rightCallRetVar, nullptr, resultVar));
        }else if(irOp == LOGICALOR){
            instrs.push_back(std::make_shared<IRLogicalOr>(leftLoadedVar,nullptr, rightCallRetVar, nullptr, resultVar));
        }else if(irOp == ADD_EQ){
            instrs.push_back(std::make_shared<IRAddEq>(leftLoadedVar,nullptr, rightCallRetVar, nullptr, resultVar));
            instrs.push_back(std::make_shared<IRStore>(leftVarSymbol->type,resultVar,nullptr,leftVarSymbol));
        }else if(irOp == SUB_EQ){
            instrs.push_back(std::make_shared<IRSubEq>(leftLoadedVar,nullptr, rightCallRetVar, nullptr, resultVar));
            instrs.push_back(std::make_shared<IRStore>(leftVarSymbol->type,resultVar,nullptr,leftVarSymbol));
        }else if(irOp == MUL_EQ){
            instrs.push_back(std::make_shared<IRMulEq>(leftLoadedVar,nullptr, rightCallRetVar, nullptr, resultVar));
            instrs.push_back(std::make_shared<IRStore>(leftVarSymbol->type,resultVar,nullptr,leftVarSymbol));
        }else if(irOp == DIV_EQ){
            instrs.push_back(std::make_shared<IRDivEq>(leftLoadedVar,nullptr, rightCallRetVar, nullptr, resultVar));
            instrs.push_back(std::make_shared<IRStore>(leftVarSymbol->type,resultVar,nullptr,leftVarSymbol));
        }else if(irOp == MOD_EQ){
            instrs.push_back(std::make_shared<IRModEq>(leftLoadedVar,nullptr, rightCallRetVar, nullptr, resultVar));
            instrs.push_back(std::make_shared<IRStore>(leftVarSymbol->type,resultVar,nullptr,leftVarSymbol));
        }else {
            throw std::runtime_error("IRBuilder visit ExprOpbinary error: unknown binary op");
        }
    }

    void leftLoadRightLiteral(std::vector<std::shared_ptr<IRNode>> &instrs,std::shared_ptr<IRVar> leftVarSymbol, std::shared_ptr<IRVar> rightVarSymbol,binaryOp op, long long int res){
        auto leftLoadedVar = std::make_shared<IRVar>();
        instrs.push_back(std::make_shared<IRLoad>(leftLoadedVar, leftVarSymbol, leftVarSymbol->type));
        auto resultVar = std::make_shared<IRVar>();
        IROp irOp = turnBinaryOp(op);
        auto rightLiteral = std::make_shared<IRLiteral>(INT_LITERAL, res);
        if(irOp == ADD){
            instrs.push_back(std::make_shared<IRAdd>(leftLoadedVar,nullptr,nullptr, rightLiteral, resultVar));
        }else if(irOp == SUB){
            instrs.push_back(std::make_shared<IRSub>(leftLoadedVar,nullptr,nullptr, rightLiteral, resultVar));   
        }else if(irOp == MUL){
            instrs.push_back(std::make_shared<IRMul>(leftLoadedVar,nullptr,nullptr, rightLiteral, resultVar));
        }else if(irOp == DIV){
            instrs.push_back(std::make_shared<IRDiv>(leftLoadedVar,nullptr,nullptr,rightLiteral, resultVar));
        }else if(irOp == MOD){
            instrs.push_back(std::make_shared<IRMod>(leftLoadedVar,nullptr,nullptr, rightLiteral, resultVar));  
        }else if(irOp == EQ){
            instrs.push_back(std::make_shared<IREq>(leftLoadedVar,nullptr,nullptr, rightLiteral, resultVar));    
        }else if(irOp == NEQ){
            instrs.push_back(std::make_shared<IRNeq>(leftLoadedVar,nullptr,nullptr, rightLiteral, resultVar));    
        }else if(irOp == LT){
            instrs.push_back(std::make_shared<IRLt>(leftLoadedVar,nullptr,nullptr, rightLiteral, resultVar));
        }else if(irOp == LEQ){  
            instrs.push_back(std::make_shared<IRLeq>(leftLoadedVar,nullptr,nullptr, rightLiteral, resultVar));
        }else if(irOp == GT){
            instrs.push_back(std::make_shared<IRGt>(leftLoadedVar,nullptr,nullptr, rightLiteral, resultVar));
        }else if(irOp == GEQ){
            instrs.push_back(std::make_shared<IRGeq>(leftLoadedVar,nullptr,nullptr, rightLiteral, resultVar));
        }else if(irOp == LOGICALAND){
            instrs.push_back(std::make_shared<IRLogicalAnd>(leftLoadedVar,nullptr,nullptr, rightLiteral, resultVar));
        }else if(irOp == LOGICALOR){
            instrs.push_back(std::make_shared<IRLogicalOr>(leftLoadedVar,nullptr,nullptr, rightLiteral, resultVar));
        }else if(irOp == ADD_EQ){
            instrs.push_back(std::make_shared<IRAddEq>(leftLoadedVar,nullptr,nullptr, rightLiteral, resultVar));
            instrs.push_back(std::make_shared<IRStore>(leftVarSymbol->type,resultVar,nullptr,leftVarSymbol));
        }else if(irOp == SUB_EQ){
            instrs.push_back(std::make_shared<IRSubEq>(leftLoadedVar,nullptr,nullptr, rightLiteral, resultVar));
            instrs.push_back(std::make_shared<IRStore>(leftVarSymbol->type,resultVar,nullptr,leftVarSymbol));
        }else if(irOp == MUL_EQ){
            instrs.push_back(std::make_shared<IRMulEq>(leftLoadedVar,nullptr,nullptr, rightLiteral, resultVar));
            instrs.push_back(std::make_shared<IRStore>(leftVarSymbol->type,resultVar,nullptr,leftVarSymbol));
        }else if(irOp == DIV_EQ){
            instrs.push_back(std::make_shared<IRDivEq>(leftLoadedVar,nullptr,nullptr, rightLiteral, resultVar));
            instrs.push_back(std::make_shared<IRStore>(leftVarSymbol->type,resultVar,nullptr,leftVarSymbol));
        }else if(irOp == MOD_EQ){
            instrs.push_back(std::make_shared<IRModEq>(leftLoadedVar,nullptr,nullptr, rightLiteral, resultVar));
            instrs.push_back(std::make_shared<IRStore>(leftVarSymbol->type,resultVar,nullptr,leftVarSymbol));
        }else {
            throw std::runtime_error("IRBuilder visit ExprOpbinary error: unknown binary op");
        }
    }

    void leftLiteralRightLoad(std::vector<std::shared_ptr<IRNode>> &instrs,std::shared_ptr<IRVar> leftVarSymbol, std::shared_ptr<IRVar> rightVarSymbol,binaryOp op, long long int res,bool isRightCall ){
        auto rightLoadedVar = std::make_shared<IRVar>();
        if(isRightCall){
            rightLoadedVar = rightVarSymbol;
        }else{
            instrs.push_back(std::make_shared<IRLoad>(rightLoadedVar, rightVarSymbol, rightVarSymbol->type));
        }
        auto resultVar = std::make_shared<IRVar>();
        IROp irOp = turnBinaryOp(op);
        auto leftLiteral = std::make_shared<IRLiteral>(INT_LITERAL, res);
        if(irOp == ADD){
            instrs.push_back(std::make_shared<IRAdd>(nullptr,leftLiteral, rightLoadedVar, nullptr, resultVar));
        }else if(irOp == SUB){
            instrs.push_back(std::make_shared<IRSub>(nullptr,leftLiteral, rightLoadedVar, nullptr, resultVar));
        }else if(irOp == MUL){
            instrs.push_back(std::make_shared<IRMul>(nullptr,leftLiteral, rightLoadedVar, nullptr, resultVar));
        }else if(irOp == DIV){
            instrs.push_back(std::make_shared<IRDiv>(nullptr,leftLiteral, rightLoadedVar, nullptr, resultVar));
        }else if(irOp == MOD){
            instrs.push_back(std::make_shared<IRMod>(nullptr,leftLiteral, rightLoadedVar, nullptr, resultVar));
        }else if(irOp == EQ){
            instrs.push_back(std::make_shared<IREq>(nullptr,leftLiteral, rightLoadedVar, nullptr, resultVar));
        }else if(irOp == NEQ){
            instrs.push_back(std::make_shared<IRNeq>(nullptr,leftLiteral, rightLoadedVar, nullptr, resultVar));
        }else if(irOp == LT){
            instrs.push_back(std::make_shared<IRLt>(nullptr,leftLiteral, rightLoadedVar, nullptr, resultVar));
        }else if(irOp == LEQ){
            instrs.push_back(std::make_shared<IRLeq>(nullptr,leftLiteral, rightLoadedVar, nullptr, resultVar));
        }else if(irOp == GT){
            instrs.push_back(std::make_shared<IRGt>(nullptr,leftLiteral, rightLoadedVar, nullptr, resultVar));
        }else if(irOp == GEQ){
            instrs.push_back(std::make_shared<IRGeq>(nullptr,leftLiteral, rightLoadedVar, nullptr, resultVar));
        }else if(irOp == LOGICALAND){
            instrs.push_back(std::make_shared<IRLogicalAnd>(nullptr,leftLiteral, rightLoadedVar, nullptr, resultVar));
        }else if(irOp == LOGICALOR){
            instrs.push_back(std::make_shared<IRLogicalOr>(nullptr,leftLiteral, rightLoadedVar, nullptr, resultVar));
        }else {
            throw std::runtime_error("IRBuilder visit ExprOpbinary error: unknown binary op");
        }
    }

    void bothLiteral(std::vector<std::shared_ptr<IRNode>> &instrs,long long int leftRes, long long int rightRes,binaryOp op){
        auto resultVar = std::make_shared<IRVar>();
        IROp irOp = turnBinaryOp(op);
        auto leftLiteral = std::make_shared<IRLiteral>(INT_LITERAL, leftRes);
        auto rightLiteral = std::make_shared<IRLiteral>(INT_LITERAL, rightRes);
        if(irOp == ADD){
            instrs.push_back(std::make_shared<IRAdd>(nullptr,leftLiteral, nullptr, rightLiteral, resultVar));
        }else if(irOp == SUB){
            instrs.push_back(std::make_shared<IRSub>(nullptr,leftLiteral, nullptr, rightLiteral, resultVar));
        }else if(irOp == MUL){
            instrs.push_back(std::make_shared<IRMul>(nullptr,leftLiteral, nullptr, rightLiteral, resultVar));
        }else if(irOp == DIV){
            instrs.push_back(std::make_shared<IRDiv>(nullptr,leftLiteral, nullptr, rightLiteral, resultVar));
        }else if(irOp == MOD){
            instrs.push_back(std::make_shared<IRMod>(nullptr,leftLiteral, nullptr, rightLiteral, resultVar));
        }else if(irOp == EQ){
            instrs.push_back(std::make_shared<IREq>(nullptr,leftLiteral, nullptr, rightLiteral, resultVar));
        }else if(irOp == NEQ){
            instrs.push_back(std::make_shared<IRNeq>(nullptr,leftLiteral, nullptr, rightLiteral, resultVar));
        }else if(irOp == LT){
            instrs.push_back(std::make_shared<IRLt>(nullptr,leftLiteral, nullptr, rightLiteral, resultVar));
        }else if(irOp == LEQ){
            instrs.push_back(std::make_shared<IRLeq>(nullptr,leftLiteral, nullptr, rightLiteral, resultVar));
        }else if(irOp == GT){
            instrs.push_back(std::make_shared<IRGt>(nullptr,leftLiteral, nullptr, rightLiteral, resultVar));
        }else if(irOp == GEQ){
            instrs.push_back(std::make_shared<IRGeq>(nullptr,leftLiteral, nullptr, rightLiteral, resultVar));
        }else if(irOp == LOGICALAND){
            instrs.push_back(std::make_shared<IRLogicalAnd>(nullptr,leftLiteral, nullptr, rightLiteral, resultVar));
        }else if(irOp == LOGICALOR){
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
                        //both are variable
                        bothLoad(instrs, leftVarSymbol, rightVarSymbol, node.op);
                    }else if(leftVarSymbol && !rightVarSymbol){
                        //right is constant
                        long long int res = currentScope->lookupConstantSymbol(rightVarName);
                        leftLoadRightLiteral(instrs, leftVarSymbol, rightVarSymbol, node.op, res);
                    }else if(!leftVarSymbol && rightVarSymbol){
                        //left is constant
                        long long int res = currentScope->lookupConstantSymbol(leftVarName);
                        leftLiteralRightLoad(instrs, leftVarSymbol, rightVarSymbol, node.op, res,false);
                    }else if(!leftVarSymbol && !rightVarSymbol){
                        //both are constant
                        long long int leftRes = currentScope->lookupConstantSymbol(leftVarName);
                        long long int rightRes = currentScope->lookupConstantSymbol(rightVarName);
                        bothLiteral(instrs, leftRes, rightRes, node.op);
                    }
                }
            }else if(auto *rightLiteral = dynamic_cast<ExprLiteral *>(& *node.right)){
                //todo left is path right is literal
                if(leftPath->pathFirst->pathSegments.type == IDENTIFIER){
                    std::string leftVarName = leftPath->pathFirst->pathSegments.identifier;
                    auto leftVarSymbol = currentScope->lookupValueSymbol(leftVarName);
                    if(leftVarSymbol){
                        long long int res = rightLiteral->constValue;
                        leftLoadRightLiteral(instrs, leftVarSymbol, nullptr, node.op, res);
                    }else{
                        long long int leftRes = currentScope->lookupConstantSymbol(leftVarName);
                        long long int rightRes = rightLiteral->constValue;
                        bothLiteral(instrs, leftRes, rightRes, node.op);
                    }
                }
            }else if(auto *rightCall = dynamic_cast<ExprCall *>(& *node.right)){
                //todo
                auto callInstrs = visit(*rightCall);
                if(auto *callLastInstr = dynamic_cast<IRCall *>(& *callInstrs[callInstrs.size() -1])){
                    //todo 
                    auto rightCallRetVar = callLastInstr->retVar;
                    if(leftPath->pathFirst->pathSegments.type == IDENTIFIER){
                        std::string leftVarName = leftPath->pathFirst->pathSegments.identifier;
                        auto leftVarSymbol = currentScope->lookupValueSymbol(leftVarName);
                        if(leftVarSymbol){
                            auto leftLoadedVar = std::make_shared<IRVar>();
                            instrs.push_back(std::make_shared<IRLoad>(leftLoadedVar, leftVarSymbol, leftVarSymbol->type));
                            for(auto & instr : callInstrs){
                                instrs.push_back(instr);
                            }
                            bothLoadForCall(instrs, leftVarSymbol,leftLoadedVar, rightCallRetVar, node.op);
                        }else{
                            long long int res = currentScope->lookupConstantSymbol(leftVarName);
                            for(auto & instr : callInstrs){
                                instrs.push_back(instr);
                            }
                            leftLiteralRightLoad(instrs, nullptr, rightCallRetVar, node.op, res, true);
                        }
                    }
                }
            }
        }
        auto leftInstrs = visit(*node.left);
        auto rightInstrs = visit(*node.right);
        //todo process left
        
        return instrs;
    }

    std::vector<std::shared_ptr<IRNode>> visit(ExprOpunary &node);

    std::vector<std::shared_ptr<IRNode>> visit(ExprPath &node);

    std::vector<std::shared_ptr<IRNode>> visit(ExprReturn &node);

    std::vector<std::shared_ptr<IRNode>> visit(ExprStruct &node);

    std::vector<std::shared_ptr<IRNode>> visit(ExprUnderscore &node);
    
    //Item 
    std::shared_ptr<IRNode> visit(Item &node){
        if(auto *p = dynamic_cast<ItemConstDecl *>(& node)) {
            visit(*p);
        }else if(auto *p = dynamic_cast<ItemEnumDecl *>(& node)) {
            visit(*p);
        }else if(auto *p = dynamic_cast<ItemFnDecl *>(& node)) {
            visit(*p);
        }else if(auto *p = dynamic_cast<ItemImplDecl *>(& node)) {
            visit(*p);
        }else if(auto *p = dynamic_cast<ItemStructDecl *>(& node)) {    
            visit(*p);
        }else if(auto *p = dynamic_cast<ItemTraitDecl *>(& node)) {
            visit(*p);
        }else{
            throw std::runtime_error("IRBuilder visit Item error");
        }
    }

    std::shared_ptr<IRNode> visit(ItemConstDecl &node);

    std::shared_ptr<IRNode> visit(ItemEnumDecl &node);

    std::shared_ptr<IRFunction> visit(ItemFnDecl &node){
        auto currentIRFunc = currentScope->lookupFunctionSymbol(node.identifier);
        auto funcScope = std::make_shared<IRScope>();
        funcScope->parent = currentScope;
        currentScope->children.push_back(funcScope);
        currentScope = funcScope;
        if(node.fnBody){
            for(auto & stmt : node.fnBody->statements){
                if(auto *itemStmt = dynamic_cast<StmtItem *>(& *stmt)){
                    if(auto *p = dynamic_cast<ItemConstDecl *>(& *itemStmt)){
                        currentScope->addConstantSymbol(p->identifier, p->value);
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
                        currentScope->addFunctionSymbol(funcName, std::make_shared<IRFunction>(returnType, irParam, funcName));
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
                        currentScope->addTypeSymbol(structName, std::make_shared<IRStructType>(structName, fieldTypes));
                    }else if(auto *p = dynamic_cast<ItemTraitDecl *>(& *itemStmt)){
                        //no need to do anything
                    }
                }
            }
        }
        // auto funcRetVar = std::make_shared<IRVar>();
        // if(currentIRFunc->retType != currentScope->lookupTypeSymbol("void")){
        //     currentIRFunc->body->instrList.push_back(std::make_shared<IRAlloca>(currentIRFunc->retType, funcRetVar));
        //     auto tmpRet = std::make_shared<IRVar>();
        //     currentIRFunc->retBlock->instrList.push_back(std::make_shared<IRLoad>(tmpRet, funcRetVar, currentIRFunc->retType));
        //     currentIRFunc->retBlock->instrList.push_back(std::make_shared<IRReturn>(currentIRFunc->retType, tmpRet));
        // }
        //todo processing the function body
        if(node.fnBody){
            for(auto & stmt : node.fnBody->statements){
                std::vector<std::shared_ptr<IRNode>> instructions = visit(*stmt);
                for(auto & instr : instructions){
                    currentIRFunc->body->instrList.push_back(instr);
                }
            }
            if(node.fnBody->ExpressionWithoutBlock){
                //todo about br instruction
            }
        }
        //deal with return

        currentScope = currentScope->parent;
    }


    std::shared_ptr<IRNode> visit(ItemImplDecl &node){
        // no need to do anything
        // I plan to do the IRFunction build in IRGlobalBuilder
        return nullptr;
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

    std::vector<std::shared_ptr<IRNode>> visit(StmtExpr &node){
        //TODO
    }

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
        auto currentVar = std::make_shared<IRVar>(varName, reName, varType);
        currentScope->addValueSymbol(varName, currentVar);
        instrs.push_back(std::make_shared<IRAlloca>(varType,currentVar));
        //todo init expr

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
            size = node.expr->constValue;
        }
        return std::make_shared<IRArrayType>(currentType, size);
    }

    std::shared_ptr<IRStructType> visit(Path &node){
        if(node.pathSegments.type == IDENTIFIER){
            auto typeName = node.pathSegments.identifier;
            auto structType = currentScope->lookupTypeSymbol(typeName);
            if(structType){
                return std::dynamic_pointer_cast<IRStructType>(structType);
            }else{
                throw std::runtime_error("IRBuilder visit Path error: unknown type " + typeName);
            }
        }
        //TODO self
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