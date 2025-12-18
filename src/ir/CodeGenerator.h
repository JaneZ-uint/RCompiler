# pragma once
#include "IRAlloca.h"
#include "IRBinaryop.h"
#include "IRBr.h"
# include "IRBuilder.h"
#include "IRExit.h"
#include "IRFunction.h"
#include "IRGetptr.h"
#include "IRImpl.h"
#include "IRLiteral.h"
#include "IRLoad.h"
#include "IRNode.h"
#include "IRReturn.h"
#include "IRRoot.h"
#include "IRSext.h"
#include "IRStore.h"
#include "IRTrunc.h"
#include "IRType.h"
#include "IRVar.h"
#include "IRZext.h"
#include <memory>
#include <vector>

namespace JaneZ {
class CodeGenerator {
public:
    IRBuilder irBuilder;

    std::shared_ptr<IRRoot> irRoot;

    void generateCode(ASTRootNode &root) {
        irRoot = irBuilder.visit(root);
        for(auto &func : irRoot->children) {
            codeGen(*func);
        }
    }

    void codeGen(IRNode &node){
        if(auto *p = dynamic_cast<IRFunction *>(& node)){
            //print functions info here
            std::cout << "define ";;
            if(p->retType->type == BaseType::INT){
                if(auto *q = dynamic_cast<IRIntType *>(p->retType.get())){
                    if(q->bitWidth == 32){
                        std::cout << "i32 ";
                    }else if(q->bitWidth == 8){
                        std::cout << "i8 ";
                    }
                }
            }else if(p->retType->type == BaseType::ARRAY  ){
                //
            }else if(p->retType->type == BaseType::STRUCT){
                if(auto *q = dynamic_cast<IRStructType *>(p->retType.get())){   
                    std::cout << "%struct." << q->name << " ";
                }
            }
            std::cout << "@" << p->name << "(";
            for(size_t i = 0; i < p->paramList->paramList.size(); ++i){
                auto &param = p->paramList->paramList[i];
                if(auto *var = dynamic_cast<IRVar *>(& *param)){
                    if(var->type->type == BaseType::INT){
                        if(auto *q = dynamic_cast<IRIntType *>(var->type.get())){
                            if(q->bitWidth == 32){
                                std::cout << "i32 ";
                            }else if(q->bitWidth == 8){
                                std::cout << "i8 ";
                            }
                        }
                    }else if(var->type->type == BaseType::ARRAY  ){
                        //
                    }else if(var->type->type == BaseType::STRUCT){
                        if(auto *q = dynamic_cast<IRStructType *>(var->type.get())){
                            std::cout << "%struct." << q->name << " ";
                        }
                    }
                    std::cout << "%" << var->serial;
                }
            }
            std::cout << ") {\n";
            if(p->body){
                for(auto &instr: p->body->instrList){
                    if(auto *q = dynamic_cast<IRAlloca *>(& *instr)){
                        code(*q);
                    }
                }
                for(auto &block  :p->body->blockList){
                    for(auto &instr: block->instrList){
                        if(auto *q = dynamic_cast<IRAlloca *>(& *instr)){
                            code(*q);
                        }
                    }
                }
                for(auto &instr: p->body->instrList){
                    if(auto *q = dynamic_cast<IRAlloca *>(& *instr)){
                        continue;
                    }
                    code(*instr);
                }
                for(auto &block  :p->body->blockList){
                    for(auto &instr: block->instrList){
                        if(auto *q = dynamic_cast<IRAlloca *>(& *instr)){
                            continue;
                        }
                        code(*instr);   
                    }
                }
            }
            std::cout << "}\n";
        }else if(auto *p = dynamic_cast<IRImpl *>(& node)){
            auto type = p->mainStructType;
            for(auto &func: p->functions){
                //print functions info here
                std::cout << "define ";
                if(func->retType->type == BaseType::INT){
                    if(auto *q = dynamic_cast<IRIntType *>(func->retType.get())){
                        if(q->bitWidth == 32){
                            std::cout << "i32 ";
                        }else if(q->bitWidth == 8){
                            std::cout << "i8 ";
                        }
                    }
                }else if(func->retType->type == BaseType::ARRAY  ){ 
                    //
                }else if(func->retType->type == BaseType::STRUCT){
                    if(auto *q = dynamic_cast<IRStructType *>(func->retType.get())){
                        std::cout << "%struct." << q->name << " ";
                    }
                }
                if(auto *r = dynamic_cast<IRStructType *>(type.get())){
                    std::cout << "@" << r->name << "::" << func->name << "(";
                }
                for(size_t i = 0; i < func->paramList->paramList.size(); ++i){
                    auto &param = func->paramList->paramList[i];
                    if(auto *var = dynamic_cast<IRVar *>(& *param)){
                        if(var->type->type == BaseType::INT){
                            if(auto *q = dynamic_cast<IRIntType *>(var->type.get())){
                                if(q->bitWidth == 32){
                                    std::cout << "i32 ";
                                }else if(q->bitWidth == 8){
                                    std::cout << "i8 ";
                                }
                            }
                        }else if(var->type->type == BaseType::ARRAY  ){
                            //
                        }else if(var->type->type == BaseType::STRUCT){
                            if(auto *q = dynamic_cast<IRStructType *>(var->type.get())){
                                std::cout << "%struct." << q->name << " ";
                            }
                        }
                        std::cout << "%" << var->serial;
                    }
                    if(i != func->paramList->paramList.size() -1){
                        std::cout << ", ";
                    }
                }
                std::cout << ") {\n";
                if(func->body){
                    for(auto &instr: func->body->instrList){
                        if(auto *q = dynamic_cast<IRAlloca *>(& *instr)){
                            code(*q);   
                        }
                    }
                    for(auto &block  :func->body->blockList){
                        for(auto &instr: block->instrList){
                            if(auto *q = dynamic_cast<IRAlloca *>(& *instr)){
                                code(*q);   
                            }
                        }
                    }
                    for(auto &instr: func->body->instrList){
                        if(auto *q = dynamic_cast<IRAlloca *>(& *instr)){
                            continue;
                        }
                        code(*instr);
                    }
                    for(auto &block  :func->body->blockList){
                        for(auto &instr: block->instrList){
                            if(auto *q = dynamic_cast<IRAlloca *>(& *instr)){
                                continue;
                            }
                            code(*instr);   
                        }
                    }
                }
                std::cout << "}\n";
            }
        }else if(auto *p = dynamic_cast<IRType *>(& node)){
            std::cout << "%struct.";
            if(auto *q = dynamic_cast<IRStructType *>(p)){
                std::cout << q->name << " = type { ";
                for(size_t i = 0; i < q->memberTypes.size(); ++i){
                    if(q->memberTypes[i].second->type == BaseType::INT){
                        if(auto *r = dynamic_cast<IRIntType *>(q->memberTypes[i].second.get())){
                            if(r->bitWidth == 32){
                                std::cout << "i32";
                            }else if(r->bitWidth == 8){
                                std::cout << "i8";
                            }
                        }
                        std::cout << "i32";
                    }else if(q->memberTypes[i].second->type == BaseType::ARRAY  ){
                        //
                    }else if(q->memberTypes[i].second->type == BaseType::STRUCT){
                        if(auto *r = dynamic_cast<IRStructType *>(q->memberTypes[i].second.get())){
                            std::cout << "%struct." << r->name;
                        }
                    }
                    if(i != q->memberTypes.size() -1){
                        std::cout << ", ";
                    }
                }
                std::cout << " }\n";
            }
        }
    }

    void code(IRNode &node) {
        if(auto *p = dynamic_cast<IRAlloca *>(& node)){
            std::cout << "%" << p->var->serial << " = alloca ";
            if(p->var->type->type == BaseType::INT){
                if(auto *q = dynamic_cast<IRIntType *>(p->var->type.get())){
                    if(q->bitWidth == 32){
                        std::cout << "i32";
                    }else if(q->bitWidth == 8){
                        std::cout << "i8";
                    }
                }
            }else if(p->var->type->type == BaseType::ARRAY  ){
                //
            }else if(p->var->type->type == BaseType::STRUCT){
                if(auto *q = dynamic_cast<IRStructType *>(p->var->type.get())){
                    std::cout << "%struct." << q->name;
                }
            }
            std::cout << ", align 4\n";
        }else if(auto *p = dynamic_cast<IRLoad *>(& node)){
            std::cout << "%" << p->tmp->serial << " = load ";
            if(p->type->type == BaseType::INT){
                if(auto *q = dynamic_cast<IRIntType *>(p->type.get())){
                    if(q->bitWidth == 32){
                        std::cout << "i32";
                    }else if(q->bitWidth == 8){
                        std::cout << "i8";
                    }
                }
            }else if(p->type->type == BaseType::ARRAY  ){
                //
            }else if(p->type->type == BaseType::STRUCT){
                if(auto *q = dynamic_cast<IRStructType *>(p->type.get())){
                    std::cout << "%struct." << q->name;
                }
            }
            std::cout << ", ptr %" << p->addressVar->serial << ", align 4\n";
        }else if(auto *p = dynamic_cast<IRStore *>(& node)){
            std::cout << "store ";
            if(p->valueType->type == BaseType::INT){
                if(auto *q = dynamic_cast<IRIntType *>(p->valueType.get())){
                    if(q->bitWidth == 32){
                        std::cout << "i32 ";
                    }else if(q->bitWidth == 8){
                        std::cout << "i8 ";
                    }
                }
            }else if(p->valueType->type == BaseType::ARRAY  ){
                //
            }else if(p->valueType->type == BaseType::STRUCT){
                if(auto *q = dynamic_cast<IRStructType *>(p->valueType.get())){
                    std::cout << "%struct." << q->name << " ";
                }
            }
            if(p->storeValue){
                std::cout << "%" << p->storeValue->serial << ", ";
            }else{
                std::cout << p->storeLiteral->intValue << ", ";
            }
            std::cout << "ptr %" << p->address->serial << ", align 4\n";
        }else if(auto *p = dynamic_cast<IRReturn *>(& node)){
            std::cout << "ret ";
            if(!p->returnValue){
                if(p->returnLiteral){
                    std::cout << "i32 " << p->returnLiteral->intValue << "\n";
                    return;
                }
            }
            if(p->returnType->type == BaseType::INT){
                if(auto *q = dynamic_cast<IRIntType *>(p->returnType.get())){
                    if(q->bitWidth == 32){
                        std::cout << "i32 ";
                    }else if(q->bitWidth == 8){
                        std::cout << "i8 ";
                    }
                }
            }else if(p->returnType->type == BaseType::ARRAY  ){
                //
            }else if(p->returnType->type == BaseType::STRUCT){
                if(auto *q = dynamic_cast<IRStructType *>(p->returnType.get())){
                    std::cout << "%struct." << q->name << " ";
                }
            }
            if(p->returnValue){
                std::cout << "%" << p->returnValue->serial << "\n";
            }else{
                std::cout << "void\n";
            }
        }else if(auto *p = dynamic_cast<IRBr *>(& node)){
            if(p->falseLabel){
                std::cout << "br i1 %" << p->condition->serial << ", label %" << p->trueLabel->label << ", label %" << p->falseLabel->label << "\n";
            }else{
                std::cout << "br label %" << p->trueLabel->label << "\n";
            }
        }else if(auto *p = dynamic_cast<IRAdd *>(& node)){
            std::cout << "%" << p->result->serial << " = add ";
            if(p->left && p->right){
                if(p->left->type->type == BaseType::INT){
                    if(auto *q = dynamic_cast<IRIntType *>(p->left->type.get())){
                        if(q->bitWidth == 32){
                            std::cout << "i32 ";
                        }else if(q->bitWidth == 8){
                            std::cout << "i8 ";
                        }
                    }
                }
                std::cout << "%" << p->left->serial << ", %" << p->right->serial << "\n";
            }else if(p->left && p->rightLiteral){
                if(p->left->type->type == BaseType::INT){
                    if(auto *q = dynamic_cast<IRIntType *>(p->left->type.get())){
                        if(q->bitWidth == 32){
                            std::cout << "i32 ";
                        }else if(q->bitWidth == 8){
                            std::cout << "i8 ";
                        }
                    }
                }
                std::cout << "%" << p->left->serial << ", " << p->rightLiteral->intValue << "\n";
            }else if(p->leftLiteral && p->right){
                if(p->right->type->type == BaseType::INT){
                    if(auto *q = dynamic_cast<IRIntType *>(p->right->type.get())){
                        if(q->bitWidth == 32){
                            std::cout << "i32 ";
                        }else if(q->bitWidth == 8){
                            std::cout << "i8 ";
                        }
                    }
                }
                std::cout << p->leftLiteral->intValue << ", %" << p->right->serial << "\n";
            }else{
                std::cout << "i32 ";
                std::cout << p->leftLiteral->intValue << ", " << p->rightLiteral->intValue << "\n";
            }
        }else if(auto *p = dynamic_cast<IRSub *>(& node)){
            std::cout << "%" << p->result->serial << " = sub ";
            if(p->left && p->right){
                if(p->left->type->type == BaseType::INT){
                    if(auto *q = dynamic_cast<IRIntType *>(p->left->type.get())){
                        if(q->bitWidth == 32){
                            std::cout << "i32 ";
                        }else if(q->bitWidth == 8){
                            std::cout << "i8 ";
                        }
                    }
                }
                std::cout << "%" << p->left->serial << ", %" << p->right->serial << "\n";
            }else if(p->left && p->rightLiteral){   
                if(p->left->type->type == BaseType::INT){
                    if(auto *q = dynamic_cast<IRIntType *>(p->left->type.get())){
                        if(q->bitWidth == 32){
                            std::cout << "i32 ";
                        }else if(q->bitWidth == 8){
                            std::cout << "i8 ";
                        }
                    }
                }
                std::cout << "%" << p->left->serial << ", " << p->rightLiteral->intValue << "\n";
            }else if(p->leftLiteral && p->right){
                if(p->right->type->type == BaseType::INT){
                    if(auto *q = dynamic_cast<IRIntType *>(p->right->type.get())){
                        if(q->bitWidth == 32){
                            std::cout << "i32 ";
                        }else if(q->bitWidth == 8){
                            std::cout << "i8 ";
                        }
                    }
                }
                std::cout << p->leftLiteral->intValue << ", %" << p->right->serial << "\n";
            }else{
                std::cout << "i32 ";
                std::cout << p->leftLiteral->intValue << ", " << p->rightLiteral->intValue << "\n";
            }
        }else if(auto *p = dynamic_cast<IRMul *>(& node)){
            std::cout << "%" << p->result->serial << " = mul ";
            if(p->left && p->right){
                if(p->left->type->type == BaseType::INT){
                    if(auto *q = dynamic_cast<IRIntType *>(p->left->type.get())){
                        if(q->bitWidth == 32){
                            std::cout << "i32 ";
                        }else if(q->bitWidth == 8){
                            std::cout << "i8 ";
                        }
                    }
                }
                std::cout << "%" << p->left->serial << ", %" << p->right->serial << "\n";
            }else if(p->left && p->rightLiteral){   
                if(p->left->type->type == BaseType::INT){
                    if(auto *q = dynamic_cast<IRIntType *>(p->left->type.get())){
                        if(q->bitWidth == 32){
                            std::cout << "i32 ";
                        }else if(q->bitWidth == 8){
                            std::cout << "i8 ";
                        }
                    }
                }
                std::cout << "%" << p->left->serial << ", " << p->rightLiteral->intValue << "\n";
            }else if(p->leftLiteral && p->right){
                if(p->right->type->type == BaseType::INT){
                    if(auto *q = dynamic_cast<IRIntType *>(p->right->type.get())){
                        if(q->bitWidth == 32){
                            std::cout << "i32 ";
                        }else if(q->bitWidth == 8){
                            std::cout << "i8 ";
                        }
                    }
                }
                std::cout << p->leftLiteral->intValue << ", %" << p->right->serial << "\n";
            }else{
                std::cout << "i32 ";
                std::cout << p->leftLiteral->intValue << ", " << p->rightLiteral->intValue << "\n";
            }
        }else if(auto *p = dynamic_cast<IRDiv *>(& node)){
            std::cout << "%" << p->result->serial << " = sdiv "; 
            if(p->left && p->right){
                if(p->left->type->type == BaseType::INT){
                    if(auto *q = dynamic_cast<IRIntType *>(p->left->type.get())){
                        if(q->bitWidth == 32){
                            std::cout << "i32 ";
                        }else if(q->bitWidth == 8){
                            std::cout << "i8 ";
                        }
                    }
                }
                std::cout << "%" << p->left->serial << ", %" << p->right->serial << "\n";
            }else if(p->left && p->rightLiteral){   
                if(p->left->type->type == BaseType::INT){
                    if(auto *q = dynamic_cast<IRIntType *>(p->left->type.get())){
                        if(q->bitWidth == 32){
                            std::cout << "i32 ";
                        }else if(q->bitWidth == 8){
                            std::cout << "i8 ";
                        }
                    }
                }
                std::cout << "%" << p->left->serial << ", " << p->rightLiteral->intValue << "\n";
            }else if(p->leftLiteral && p->right){
                if(p->right->type->type == BaseType::INT){
                    if(auto *q = dynamic_cast<IRIntType *>(p->right->type.get())){
                        if(q->bitWidth == 32){
                            std::cout << "i32 ";
                        }else if(q->bitWidth == 8){
                            std::cout << "i8 ";
                        }
                    }
                }
                std::cout << p->leftLiteral->intValue << ", %" << p->right->serial << "\n";
            }else{
                std::cout << "i32 ";
                std::cout << p->leftLiteral->intValue << ", " << p->rightLiteral->intValue << "\n";
            }
        }else if(auto *p = dynamic_cast<IRMod *>(& node)){
            std::cout << "%" << p->result->serial << " = srem ";
            if(p->left && p->right){
                if(p->left->type->type == BaseType::INT){
                    if(auto *q = dynamic_cast<IRIntType *>(p->left->type.get())){
                        if(q->bitWidth == 32){
                            std::cout << "i32 ";
                        }else if(q->bitWidth == 8){
                            std::cout << "i8 ";     
                        }
                    }
                }
                std::cout << "%" << p->left->serial << ", %" << p->right->serial << "\n";
            }else if(p->left && p->rightLiteral){   
                if(p->left->type->type == BaseType::INT){
                    if(auto *q = dynamic_cast<IRIntType *>(p->left->type.get())){
                        if(q->bitWidth == 32){
                            std::cout << "i32 ";
                        }else if(q->bitWidth == 8){
                            std::cout << "i8 ";    
                        }
                    }
                }
                std::cout << "%" << p->left->serial << ", " << p->rightLiteral->intValue << "\n";
            }else if(p->leftLiteral && p->right){
                if(p->right->type->type == BaseType::INT){
                    if(auto *q = dynamic_cast<IRIntType *>(p->right->type.get())){
                        if(q->bitWidth == 32){
                            std::cout << "i32 ";
                        }else if(q->bitWidth == 8){
                            std::cout << "i8 ";    
                        }
                    }
                }
                std::cout << p->leftLiteral->intValue << ", %" << p->right->serial << "\n";
            }else{
                std::cout << "i32 ";
                std::cout << p->leftLiteral->intValue << ", " << p->rightLiteral->intValue << "\n";
            }
        }else if(auto *p = dynamic_cast<IREq *>(& node)){
            std::cout << "%" << p->result->serial << " = icmp eq ";
            if(p->left && p->right){
                if(p->left->type->type == BaseType::INT){
                    if(auto *q = dynamic_cast<IRIntType *>(p->left->type.get())){
                        if(q->bitWidth == 32){
                            std::cout << "i32 ";
                        }else if(q->bitWidth == 8){
                            std::cout << "i8 ";    
                        }
                    }
                }
                std::cout << "%" << p->left->serial << ", %" << p->right->serial << "\n";
            }else if(p->left && p->rightLiteral){   
                if(p->left->type->type == BaseType::INT){
                    if(auto *q = dynamic_cast<IRIntType *>(p->left->type.get())){
                        if(q->bitWidth == 32){
                            std::cout << "i32 ";    
                        }else if(q->bitWidth == 8){
                            std::cout << "i8 ";    
                        }
                    }
                }
                std::cout << "%" << p->left->serial << ", " << p->rightLiteral->intValue << "\n";
            }else if(p->leftLiteral && p->right){
                if(p->right->type->type == BaseType::INT){
                    if(auto *q = dynamic_cast<IRIntType *>(p->right->type.get())){
                        if(q->bitWidth == 32){
                            std::cout << "i32 ";    
                        }else if(q->bitWidth == 8){
                            std::cout << "i8 ";    
                        }
                    }
                }
                std::cout << p->leftLiteral->intValue << ", %" << p->right->serial << "\n";
            }else{
                std::cout << "i32 ";
                std::cout << p->leftLiteral->intValue << ", " << p->rightLiteral->intValue << "\n";
            }
        }else if(auto *p = dynamic_cast<IRNeq *>(& node)){
            std::cout << "%" << p->result->serial << " = icmp ne ";
            if(p->left && p->right){
                if(p->left->type->type == BaseType::INT){
                    if(auto *q = dynamic_cast<IRIntType *>(p->left->type.get())){
                        if(q->bitWidth == 32){  
                            std::cout << "i32 ";  
                        }else if(q->bitWidth == 8){ 
                            std::cout << "i8 ";    
                        }
                    }
                }
                std::cout << "%" << p->left->serial << ", %" << p->right->serial << "\n";
            }else if(p->left && p->rightLiteral){   
                if(p->left->type->type == BaseType::INT){
                    if(auto *q = dynamic_cast<IRIntType *>(p->left->type.get())){
                        if(q->bitWidth == 32){  
                            std::cout << "i32 ";    
                        }else if(q->bitWidth == 8){ 
                            std::cout << "i8 ";    
                        }
                    }
                }
                std::cout << "%" << p->left->serial << ", " << p->rightLiteral->intValue << "\n";
            }else if(p->leftLiteral && p->right){
                if(p->right->type->type == BaseType::INT){
                    if(auto *q = dynamic_cast<IRIntType *>(p->right->type.get())){
                        if(q->bitWidth == 32){  
                            std::cout << "i32 ";    
                        }else if(q->bitWidth == 8){ 
                            std::cout << "i8 ";    
                        }
                    }
                }
                std::cout << p->leftLiteral->intValue << ", %" << p->right->serial << "\n";
            }else{
                std::cout << "i32 ";
                std::cout << p->leftLiteral->intValue << ", " << p->rightLiteral->intValue << "\n";
            }
        }else if(auto *p = dynamic_cast<IRLt *>(& node)){
            std::cout << "%" << p->result->serial << " = icmp slt ";
            if(p->left && p->right){
                if(p->left->type->type == BaseType::INT){
                    if(auto *q = dynamic_cast<IRIntType *>(p->left->type.get())){
                        if(q->bitWidth == 32){  
                            std::cout << "i32 ";  
                        }else if(q->bitWidth == 8){ 
                            std::cout << "i8 ";   
                        }       
                    }
                }
                std::cout << "%" << p->left->serial << ", %" << p->right->serial << "\n";
            }else if(p->left && p->rightLiteral){   
                if(p->left->type->type == BaseType::INT){       
                    if(auto *q = dynamic_cast<IRIntType *>(p->left->type.get())){
                        if(q->bitWidth == 32){  
                            std::cout << "i32 ";    
                        }else if(q->bitWidth == 8){ 
                            std::cout << "i8 ";    
                        }
                    }
                }
                std::cout << "%" << p->left->serial << ", " << p->rightLiteral->intValue << "\n";
            }else if(p->leftLiteral && p->right){
                if(p->right->type->type == BaseType::INT){
                    if(auto *q = dynamic_cast<IRIntType *>(p->right->type.get())){
                        if(q->bitWidth == 32){  
                            std::cout << "i32 ";    
                        }else if(q->bitWidth == 8){ 
                            std::cout << "i8 ";    
                        }
                    }
                }
                std::cout << p->leftLiteral->intValue << ", %" << p->right->serial << "\n";
            }else{
                std::cout << "i32 ";
                std::cout << p->leftLiteral->intValue << ", " << p->rightLiteral->intValue << "\n";
            }   
        }else if(auto *p = dynamic_cast<IRLeq *>(& node)){
            std::cout << "%" << p->result->serial << " = icmp sle ";
            if(p->left && p->right){
                if(p->left->type->type == BaseType::INT){
                    if(auto *q = dynamic_cast<IRIntType *>(p->left->type.get())){
                        if(q->bitWidth == 32){  
                            std::cout << "i32 ";  
                        }else if(q->bitWidth == 8){ 
                            std::cout << "i8 ";    
                        }
                    }
                }
                std::cout << "%" << p->left->serial << ", %" << p->right->serial << "\n";
            }else if(p->left && p->rightLiteral){   
                if(p->left->type->type == BaseType::INT){
                    if(auto *q = dynamic_cast<IRIntType *>(p->left->type.get())){
                        if(q->bitWidth == 32){  
                            std::cout << "i32 ";    
                        }else if(q->bitWidth == 8){ 
                            std::cout << "i8 ";    
                        }
                    }
                }
                std::cout << "%" << p->left->serial << ", " << p->rightLiteral->intValue << "\n";
            }else if(p->leftLiteral && p->right){
                if(p->right->type->type == BaseType::INT){
                    if(auto *q = dynamic_cast<IRIntType *>(p->right->type.get())){
                        if(q->bitWidth == 32){  
                            std::cout << "i32 ";    
                        }else if(q->bitWidth == 8){ 
                            std::cout << "i8 ";    
                        }
                    }
                }
                std::cout << p->leftLiteral->intValue << ", %" << p->right->serial << "\n";
            }else{
                std::cout << "i32 ";
                std::cout << p->leftLiteral->intValue << ", " << p->rightLiteral->intValue << "\n";
            }   
        }else if(auto *p = dynamic_cast<IRGt *>(& node)){
            std::cout << "%" << p->result->serial << " = icmp sgt ";
            if(p->left && p->right){
                if(p->left->type->type == BaseType::INT){       
                    if(auto *q = dynamic_cast<IRIntType *>(p->left->type.get())){
                        if(q->bitWidth == 32){  
                            std::cout << "i32 ";  
                        }else if(q->bitWidth == 8){ 
                            std::cout << "i8 ";    
                        }
                    }
                }
                std::cout << "%" << p->left->serial << ", %" << p->right->serial << "\n";
            }else if(p->left && p->rightLiteral){   
                if(p->left->type->type == BaseType::INT){       
                    if(auto *q = dynamic_cast<IRIntType *>(p->left->type.get())){
                        if(q->bitWidth == 32){  
                            std::cout << "i32 ";    
                        }else if(q->bitWidth == 8){ 
                            std::cout << "i8 ";    
                        }
                    }
                }
                std::cout << "%" << p->left->serial << ", " << p->rightLiteral->intValue << "\n";
            }else if(p->leftLiteral && p->right){
                if(p->right->type->type == BaseType::INT){
                    if(auto *q = dynamic_cast<IRIntType *>(p->right->type.get())){
                        if(q->bitWidth == 32){  
                            std::cout << "i32 ";    
                        }else if(q->bitWidth == 8){ 
                            std::cout << "i8 ";    
                        }
                    }
                }
                std::cout << p->leftLiteral->intValue << ", %" << p->right->serial << "\n";
            }else{
                std::cout << "i32 ";
                std::cout << p->leftLiteral->intValue << ", " << p->rightLiteral->intValue << "\n";
            }
        }else if(auto *p = dynamic_cast<IRGeq *>(& node)){
            std::cout << "%" << p->result->serial << " = icmp sge ";
            if(p->left && p->right){
                if(p->left->type->type == BaseType::INT){
                    if(auto *q = dynamic_cast<IRIntType *>(p->left->type.get())){
                        if(q->bitWidth == 32){  
                            std::cout << "i32 ";  
                        }else if(q->bitWidth == 8){ 
                            std::cout << "i8 ";    
                        }
                    }
                }
                std::cout << "%" << p->left->serial << ", %" << p->right->serial << "\n";
            }else if(p->left && p->rightLiteral){   
                if(p->left->type->type == BaseType::INT){
                    if(auto *q = dynamic_cast<IRIntType *>(p->left->type.get())){
                        if(q->bitWidth == 32){  
                            std::cout << "i32 ";    
                        }else if(q->bitWidth == 8){ 
                            std::cout << "i8 ";    
                        }
                    }
                }
                std::cout << "%" << p->left->serial << ", " << p->rightLiteral->intValue << "\n";
            }else if(p->leftLiteral && p->right){
                if(p->right->type->type == BaseType::INT){
                    if(auto *q = dynamic_cast<IRIntType *>(p->right->type.get())){
                        if(q->bitWidth == 32){  
                            std::cout << "i32 ";    
                        }else if(q->bitWidth == 8){ 
                            std::cout << "i8 ";    
                        }
                    }
                }
                std::cout << p->leftLiteral->intValue << ", %" << p->right->serial << "\n";
            }else{
                std::cout << "i32 ";
                std::cout << p->leftLiteral->intValue << ", " << p->rightLiteral->intValue << "\n";
            }   
        }else if(auto *p = dynamic_cast<IRLogicalAnd *>(& node)){
            std::cout << "%" << p->result->serial << " = and ";
            if(p->left && p->right){
                if(p->left->type->type == BaseType::INT){
                    if(auto *q = dynamic_cast<IRIntType *>(p->left->type.get())){
                        if(q->bitWidth == 32){  
                            std::cout << "i32 ";  
                        }else if(q->bitWidth == 8){ 
                            std::cout << "i8 ";    
                        }
                    }
                }
                std::cout << "%" << p->left->serial << ", %" << p->right->serial << "\n";
            }else if(p->left && p->rightLiteral){   
                if(p->left->type->type == BaseType::INT){
                    if(auto *q = dynamic_cast<IRIntType *>(p->left->type.get())){
                        if(q->bitWidth == 32){  
                            std::cout << "i32 ";    
                        }else if(q->bitWidth == 8){ 
                            std::cout << "i8 ";    
                        }
                    }
                }
                std::cout << "%" << p->left->serial << ", " << p->rightLiteral->intValue << "\n";
            }else if(p->leftLiteral && p->right){
                if(p->right->type->type == BaseType::INT){
                    if(auto *q = dynamic_cast<IRIntType *>(p->right->type.get())){
                        if(q->bitWidth == 32){  
                            std::cout << "i32 ";    
                        }else if(q->bitWidth == 8){ 
                            std::cout << "i8 ";    
                        }
                    }
                }
                std::cout << p->leftLiteral->intValue << ", %" << p->right->serial << "\n";
            }else{
                std::cout << "i32 ";
                std::cout << p->leftLiteral->intValue << ", " << p->rightLiteral->intValue << "\n";
            }
        }else if(auto *p = dynamic_cast<IRLogicalOr *>(& node)){
            std::cout << "%" << p->result->serial << " = or ";
            if(p->left && p->right){
                if(p->left->type->type == BaseType::INT){
                    if(auto *q = dynamic_cast<IRIntType *>(p->left->type.get())){
                        if(q->bitWidth == 32){  
                            std::cout << "i32 ";  
                        }else if(q->bitWidth == 8){ 
                            std::cout << "i8 ";    
                        }
                    }
                }
                std::cout << "%" << p->left->serial << ", %" << p->right->serial << "\n";
            }else if(p->left && p->rightLiteral){   
                if(p->left->type->type == BaseType::INT){
                    if(auto *q = dynamic_cast<IRIntType *>(p->left->type.get())){
                        if(q->bitWidth == 32){  
                            std::cout << "i32 ";    
                        }else if(q->bitWidth == 8){ 
                            std::cout << "i8 ";    
                        }
                    }
                }
                std::cout << "%" << p->left->serial << ", " << p->rightLiteral->intValue << "\n";
            }else if(p->leftLiteral && p->right){
                if(p->right->type->type == BaseType::INT){
                    if(auto *q = dynamic_cast<IRIntType *>(p->right->type.get())){
                        if(q->bitWidth == 32){  
                            std::cout << "i32 ";    
                        }else if(q->bitWidth == 8){ 
                            std::cout << "i8 ";    
                        }
                    }
                }
                std::cout << p->leftLiteral->intValue << ", %" << p->right->serial << "\n";
            }else{
                std::cout << "i32 ";
                std::cout << p->leftLiteral->intValue << ", " << p->rightLiteral->intValue << "\n";
            }
        }else if(auto *p = dynamic_cast<IRTrunc *>(& node)){
            std::cout << "%" << p->result->serial << " = trunc ";
            if(p->value->type->type == BaseType::INT){
                if(auto *q = dynamic_cast<IRIntType *>(p->value->type.get())){
                    if(q->bitWidth == 32){  
                        std::cout << "i32 ";  
                    }else if(q->bitWidth == 8){ 
                        std::cout << "i8 ";    
                    }
                }
            }
            std::cout << "%" << p->value->serial << " to ";
            if(p->targetType->type == BaseType::INT){
                if(auto *q = dynamic_cast<IRIntType *>(p->targetType.get())){
                    if(q->bitWidth == 32){  
                        std::cout << "i32\n";  
                    }else if(q->bitWidth == 8){ 
                        std::cout << "i8\n";    
                    }else if(q->bitWidth == 1){
                        std::cout << "i1\n";    
                    }
                }
            }
        }else if(auto *p = dynamic_cast<IRSext *>(& node)){
            std::cout << "%" << p->result->serial << " = sext ";
            if(p->value->type->type == BaseType::INT){
                if(auto *q = dynamic_cast<IRIntType *>(p->value->type.get())){
                    if(q->bitWidth == 32){  
                        std::cout << "i32 ";  
                    }else if(q->bitWidth == 8){ 
                        std::cout << "i8 ";    
                    }else if(q->bitWidth == 1){
                        std::cout << "i1 ";    
                    }
                }
            }
            std::cout << "%" << p->value->serial << " to ";
            if(p->targetType->type == BaseType::INT){
                if(auto *q = dynamic_cast<IRIntType *>(p->targetType.get())){
                    if(q->bitWidth == 32){  
                        std::cout << "i32\n";  
                    }else if(q->bitWidth == 8){ 
                        std::cout << "i8\n";    
                    }
                }
            }
        }else if(auto *p = dynamic_cast<IRZext *>(& node)){
            std::cout << "%" << p->result->serial << " = zext ";
            if(p->value->type->type == BaseType::INT){
                if(auto *q = dynamic_cast<IRIntType *>(p->value->type.get())){
                    if(q->bitWidth == 32){  
                        std::cout << "i32 ";  
                    }else if(q->bitWidth == 8){ 
                        std::cout << "i8 ";    
                    }else if(q->bitWidth == 1){
                        std::cout << "i1 ";    
                    }
                }
            }
            std::cout << "%" << p->value->serial << " to ";
            if(p->targetType->type == BaseType::INT){
                if(auto *q = dynamic_cast<IRIntType *>(p->targetType.get())){
                    if(q->bitWidth == 32){  
                        std::cout << "i32\n";  
                    }else if(q->bitWidth == 8){ 
                        std::cout << "i8\n";    
                    }
                }
            }
        }else if(auto *p = dynamic_cast<IRCall *>(& node)){
            std::cout << "%" << p->retVar->serial << " = call ";
            if(p->retVar->type->type == BaseType::INT){
                if(auto *q = dynamic_cast<IRIntType *>(p->retVar.get())){
                    if(q->bitWidth == 32){
                        std::cout << "i32 ";
                    }else if(q->bitWidth == 8){
                        std::cout << "i8 ";
                    }
                }
            }else if(p->retVar->type->type == BaseType::ARRAY  ){
                //
            }else if(p->retVar->type->type == BaseType::STRUCT){
                if(auto *q = dynamic_cast<IRStructType *>(p->retVar->type.get())){
                    std::cout << "%struct." << q->name << " ";
                }
            }
            std::cout << "@" << p->function->name << "(";
            for(size_t i = 0; i < p->pList->paramList.size(); i++){
                auto &arg = p->pList->paramList[i];
                if(auto *p = dynamic_cast<IRVar *>(& *arg)){
                    if(p->type->type == BaseType::INT){
                        if(auto *q = dynamic_cast<IRIntType *>(p->type.get())){
                            if(q->bitWidth == 32){
                                std::cout << "i32 ";
                            }else if(q->bitWidth == 8){
                                std::cout << "i8 ";
                            }
                        }
                    }else if(p->type->type == BaseType::ARRAY  ){
                        //
                    }else if(p->type->type == BaseType::STRUCT){
                        if(auto *q = dynamic_cast<IRStructType *>(p->type.get())){
                            std::cout << "%struct." << q->name << " ";
                        }
                    }
                    std::cout << "%" << p->serial;
                }else if(auto *p = dynamic_cast<IRLiteral *>(& *arg)){
                    std::cout << "i32 ";
                    std::cout << p->intValue;
                }
                if(i != p->pList->paramList.size() -1){
                    std::cout << ", ";
                }
            }
            std::cout << ")\n";
        }else if(auto *p = dynamic_cast<IRGetptr *>(& node)){
            std::cout << "%" << p->res->serial << " = getelementptr ";
            if(p->type->type == BaseType::STRUCT){
                if(auto *q = dynamic_cast<IRStructType *>(p->type.get())){
                    std::cout << "%struct." << q->name << ", ";
                }
            }
            if(p->base->type->type == BaseType::STRUCT){
                if(auto *q = dynamic_cast<IRStructType *>(p->base->type.get())){
                    std::cout << "%struct." << q->name << "* ";
                }
            }
            if(p->offset != -1){
                std::cout << "%" << p->base->serial << ", i32 0, i32 " << p->offset << "\n";
            }else{
                std::cout << "%" << p->base->serial << ", i32 0, i32 %" << p->index->serial << "\n";    
            }
        }else if(auto *p = dynamic_cast<IRExit *>(& node)){
            std::cout << "call void @exit(i32 0)\n";
        }
    }
};
}