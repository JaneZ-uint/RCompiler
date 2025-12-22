# pragma once
#include "IRAlloca.h"
#include "IRBinaryop.h"
#include "IRBr.h"
# include "IRBuilder.h"
#include "IRExit.h"
#include "IRFunction.h"
#include "IRGetint.h"
#include "IRGetptr.h"
#include "IRImpl.h"
#include "IRLiteral.h"
#include "IRLoad.h"
#include "IRNode.h"
#include "IRPrint.h"
#include "IRReturn.h"
#include "IRRoot.h"
#include "IRSext.h"
#include "IRStore.h"
#include "IRTrunc.h"
#include "IRType.h"
#include "IRVar.h"
#include "IRZext.h"
#include "IRMem.h"
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
            std::cout << "define ";
            if(!p->retType){
                std::cout << "void ";
            }else if(p->retType->type == BaseType::INT){
                if(auto *q = dynamic_cast<IRIntType *>(p->retType.get())){
                    if(q->bitWidth == 32){
                        std::cout << "i32 ";
                    }else if(q->bitWidth == 8){
                        std::cout << "i8 ";
                    }
                }
            }else if(p->retType->type == BaseType::ARRAY  ){
                if(auto *q = dynamic_cast<IRArrayType *>(p->retType.get())){
                    std::cout << "[" << q->size << " x ";
                    if(q->elementType->type == BaseType::INT){
                        if(auto *r = dynamic_cast<IRIntType *>(q->elementType.get())){
                            if(r->bitWidth == 32){
                                std::cout << "i32";
                            }else if(r->bitWidth == 8){
                                std::cout << "i8";
                            }
                        }else if(q->elementType->type == BaseType::ARRAY  ){
                            if(auto *r = dynamic_cast<IRArrayType *>(q->elementType.get())){
                                std::cout << "[" << r->size << " x ";
                                if(r->elementType->type == BaseType::INT){
                                    if(auto *s = dynamic_cast<IRIntType *>(r->elementType.get())){
                                        if(s->bitWidth == 32){
                                            std::cout << "i32";
                                        }else if(s->bitWidth == 8){
                                            std::cout << "i8";
                                        }
                                    }
                                }
                                std::cout << "]";
                            }
                        }else if(q->elementType->type == BaseType::STRUCT){
                            if(auto *r = dynamic_cast<IRStructType *>(q->elementType.get())){
                                std::cout << "%struct." << r->name;
                            }
                        }
                    }
                    std::cout << "] ";
                }
            }else if(p->retType->type == BaseType::STRUCT){
                if(auto *q = dynamic_cast<IRStructType *>(p->retType.get())){   
                    std::cout << "%struct." << q->name << " ";
                }
            }else if(p->retType->type == BaseType::PTR){
                std::cout << "ptr ";
            }else if(p->retType->type == BaseType::VOID && p->name != "main"){
                std::cout << "void ";
            }
            if(p->name == "main"){
                std::cout << "i32 ";
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
                        if(auto *q = dynamic_cast<IRArrayType *>(var->type.get())){
                            std::cout << "[" << q->size << " x ";
                            if(q->elementType->type == BaseType::INT){
                                if(auto *r = dynamic_cast<IRIntType *>(q->elementType.get())){
                                    if(r->bitWidth == 32){
                                        std::cout << "i32";
                                    }else if(r->bitWidth == 8){
                                        std::cout << "i8";
                                    }
                                }else if(q->elementType->type == BaseType::ARRAY  ){
                                    if(auto *r = dynamic_cast<IRArrayType *>(q->elementType.get())){
                                        std::cout << "[" << r->size << " x ";
                                        if(r->elementType->type == BaseType::INT){
                                            if(auto *s = dynamic_cast<IRIntType *>(r->elementType.get())){
                                                if(s->bitWidth == 32){
                                                    std::cout << "i32";
                                                }else if(s->bitWidth == 8){
                                                    std::cout << "i8";
                                                }
                                            }
                                        }
                                        std::cout << "]";
                                    }
                                }else if(q->elementType->type == BaseType::STRUCT){
                                    if(auto *r = dynamic_cast<IRStructType *>(q->elementType.get())){
                                        std::cout << "%struct." << r->name;
                                    }
                                }else if(q->elementType->type == BaseType::PTR){
                                    std::cout << "ptr";
                                }
                            }
                            std::cout << "] ";
                        }
                    }else if(var->type->type == BaseType::STRUCT){
                        std::cout << "ptr ";
                    }else if(var->type->type == BaseType::PTR){
                        std::cout << "ptr ";
                    }
                    std::cout << "%" << var->serial ;
                    if(i != p->paramList->paramList.size() -1){
                        std::cout << ", ";
                    }
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
                    if(block->instrList.empty()){
                        continue;
                    }
                    std::cout << block->label << ":\n";
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
                    if(auto *q = dynamic_cast<IRArrayType *>(func->retType.get())){
                        std::cout << "[" << q->size << " x ";
                        if(q->elementType->type == BaseType::INT){
                            if(auto *r = dynamic_cast<IRIntType *>(q->elementType.get())){
                                if(r->bitWidth == 32){
                                    std::cout << "i32";
                                }else if(r->bitWidth == 8){
                                    std::cout << "i8";
                                }
                            }else if(q->elementType->type == BaseType::ARRAY  ){
                                if(auto *r = dynamic_cast<IRArrayType *>(q->elementType.get())){
                                    std::cout << "[" << r->size << " x ";
                                    if(r->elementType->type == BaseType::INT){
                                        if(auto *s = dynamic_cast<IRIntType *>(r->elementType.get())){
                                            if(s->bitWidth == 32){
                                                std::cout << "i32";
                                            }else if(s->bitWidth == 8){
                                                std::cout << "i8";
                                            }
                                        }
                                    }
                                    std::cout << "]";
                                }
                            }else if(q->elementType->type == BaseType::STRUCT){
                                if(auto *r = dynamic_cast<IRStructType *>(q->elementType.get())){
                                    std::cout << "%struct." << r->name;
                                }
                            }
                        }
                        std::cout << "] ";
                    }
                }else if(func->retType->type == BaseType::STRUCT){
                    std::cout << "void ";
                }else if(func->retType->type == BaseType::PTR){
                    std::cout << "ptr ";
                }else if(func->retType->type == BaseType::VOID){
                    std::cout << "void ";
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
                            if(auto *q = dynamic_cast<IRArrayType *>(var->type.get())){
                                std::cout << "[" << q->size << " x ";
                                if(q->elementType->type == BaseType::INT){
                                    if(auto *r = dynamic_cast<IRIntType *>(q->elementType.get())){
                                        if(r->bitWidth == 32){
                                            std::cout << "i32";
                                        }else if(r->bitWidth == 8){
                                            std::cout << "i8";
                                        }
                                    }else if(q->elementType->type == BaseType::ARRAY  ){
                                        if(auto *r = dynamic_cast<IRArrayType *>(q->elementType.get())){
                                            std::cout << "[" << r->size << " x ";
                                            if(r->elementType->type == BaseType::INT){
                                                if(auto *s = dynamic_cast<IRIntType *>(r->elementType.get())){
                                                    if(s->bitWidth == 32){
                                                        std::cout << "i32";
                                                    }else if(s->bitWidth == 8){
                                                        std::cout << "i8";
                                                    }
                                                }
                                            }
                                            std::cout << "]";
                                        }
                                    }else if(q->elementType->type == BaseType::STRUCT){
                                        if(auto *r = dynamic_cast<IRStructType *>(q->elementType.get())){
                                            std::cout << "%struct." << r->name;
                                        }
                                    }
                                }
                                std::cout << "] ";
                            }
                        }else if(var->type->type == BaseType::STRUCT){
                            if(auto *q = dynamic_cast<IRStructType *>(var->type.get())){
                                std::cout << "ptr ";
                            }
                        }else if(var->type->type == BaseType::PTR){
                            std::cout << "ptr ";
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
                        if(block->instrList.empty()){
                            continue;
                        }
                        std::cout << block->label << ":\n";
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
                    }else if(q->memberTypes[i].second->type == BaseType::ARRAY  ){
                        if(auto *r = dynamic_cast<IRArrayType *>(q->memberTypes[i].second.get())){
                            std::cout << "[" << r->size << " x ";
                            if(r->elementType->type == BaseType::INT){
                                if(auto *s = dynamic_cast<IRIntType *>(r->elementType.get())){
                                    if(s->bitWidth == 32){
                                        std::cout << "i32";
                                    }else if(s->bitWidth == 8){
                                        std::cout << "i8";
                                    }
                                }
                            }else if(r->elementType->type == BaseType::ARRAY  ){
                                if(auto *s = dynamic_cast<IRArrayType *>(r->elementType.get())){
                                    std::cout << "[" << s->size << " x ";
                                    if(s->elementType->type == BaseType::INT){
                                        if(auto *t = dynamic_cast<IRIntType *>(s->elementType.get())){
                                            if(t->bitWidth == 32){
                                                std::cout << "i32";
                                            }else if(t->bitWidth == 8){
                                                std::cout << "i8";
                                            }
                                        }
                                    }
                                    std::cout << "]";
                                }
                            }else if(r->elementType->type == BaseType::STRUCT){
                                if(auto *s = dynamic_cast<IRStructType *>(r->elementType.get())){
                                    std::cout << "%struct." << s->name;
                                }
                            }
                            std::cout << "]"; 
                        }
                    }else if(q->memberTypes[i].second->type == BaseType::STRUCT){
                        if(auto *r = dynamic_cast<IRStructType *>(q->memberTypes[i].second.get())){
                            std::cout << "%struct." << r->name;
                        }
                    }else if(q->memberTypes[i].second->type == BaseType::PTR){
                        std::cout << "ptr";
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
                if(auto *q = dynamic_cast<IRArrayType *>(p->var->type.get())){
                    std::cout << "[" << q->size << " x ";
                    if(q->elementType->type == BaseType::INT){
                        if(auto *r = dynamic_cast<IRIntType *>(q->elementType.get())){
                            if(r->bitWidth == 32){
                                std::cout << "i32";
                            }else if(r->bitWidth == 8){
                                std::cout << "i8";
                            }
                        }else if(q->elementType->type == BaseType::ARRAY  ){
                            if(auto *r = dynamic_cast<IRArrayType *>(q->elementType.get())){
                                std::cout << "[" << r->size << " x ";
                                if(r->elementType->type == BaseType::INT){
                                    if(auto *s = dynamic_cast<IRIntType *>(r->elementType.get())){
                                        if(s->bitWidth == 32){
                                            std::cout << "i32";
                                        }else if(s->bitWidth == 8){
                                            std::cout << "i8";
                                        }
                                    }
                                }
                                std::cout << "]";
                            }
                        }else if(q->elementType->type == BaseType::STRUCT){
                            if(auto *r = dynamic_cast<IRStructType *>(q->elementType.get())){
                                std::cout << "%struct." << r->name;
                            }
                        }
                    }
                    std::cout << "] ";
                }
            }else if(p->var->type->type == BaseType::STRUCT){
                if(auto *q = dynamic_cast<IRStructType *>(p->var->type.get())){
                    std::cout << "%struct." << q->name;
                }
            }else if(p->var->type->type == BaseType::PTR){
                std::cout << "ptr";
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
                if(auto *q = dynamic_cast<IRArrayType *>(p->type.get())){
                    std::cout << "[" << q->size << " x ";
                    if(q->elementType->type == BaseType::INT){
                        if(auto *r = dynamic_cast<IRIntType *>(q->elementType.get())){
                            if(r->bitWidth == 32){
                                std::cout << "i32";
                            }else if(r->bitWidth == 8){
                                std::cout << "i8";
                            }
                        }else if(q->elementType->type == BaseType::ARRAY  ){
                            if(auto *r = dynamic_cast<IRArrayType *>(q->elementType.get())){
                                std::cout << "[" << r->size << " x ";
                                if(r->elementType->type == BaseType::INT){
                                    if(auto *s = dynamic_cast<IRIntType *>(r->elementType.get())){
                                        if(s->bitWidth == 32){
                                            std::cout << "i32";
                                        }else if(s->bitWidth == 8){
                                            std::cout << "i8";
                                        }
                                    }
                                }
                                std::cout << "]";
                            }
                        }else if(q->elementType->type == BaseType::STRUCT){
                            if(auto *r = dynamic_cast<IRStructType *>(q->elementType.get())){
                                std::cout << "%struct." << r->name;
                            }
                        }
                    }
                    std::cout << "] ";
                }
            }else if(p->type->type == BaseType::STRUCT){
                if(auto *q = dynamic_cast<IRStructType *>(p->type.get())){
                    std::cout << "%struct." << q->name;
                }
            }else if(p->type->type == BaseType::PTR){
                std::cout << "ptr";
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
                if(auto *q = dynamic_cast<IRArrayType *>(p->valueType.get())){
                    std::cout << "[" << q->size << " x ";
                    if(q->elementType->type == BaseType::INT){
                        if(auto *r = dynamic_cast<IRIntType *>(q->elementType.get())){
                            if(r->bitWidth == 32){
                                std::cout << "i32";
                            }else if(r->bitWidth == 8){
                                std::cout << "i8";
                            }
                        }else if(q->elementType->type == BaseType::ARRAY  ){
                            if(auto *r = dynamic_cast<IRArrayType *>(q->elementType.get())){
                                std::cout << "[" << r->size << " x ";
                                if(r->elementType->type == BaseType::INT){
                                    if(auto *s = dynamic_cast<IRIntType *>(r->elementType.get())){
                                        if(s->bitWidth == 32){
                                            std::cout << "i32";
                                        }else if(s->bitWidth == 8){
                                            std::cout << "i8";
                                        }
                                    }
                                }
                                std::cout << "]";
                            }
                        }else if(q->elementType->type == BaseType::STRUCT){
                            if(auto *r = dynamic_cast<IRStructType *>(q->elementType.get())){
                                std::cout << "%struct." << r->name;
                            }
                        }
                    }
                    std::cout << "] ";
                }
            }else if(p->valueType->type == BaseType::STRUCT){
                if(auto *q = dynamic_cast<IRStructType *>(p->valueType.get())){
                    std::cout << "%struct." << q->name << " ";
                }
            }else if(p->valueType->type == BaseType::PTR){
                std::cout << "ptr ";
            }
            if(p->storeValue){
                std::cout << "%" << p->storeValue->serial << ", ";
            }else{
                std::cout << p->storeLiteral->intValue << ", ";
            }
            std::cout << "ptr %" << p->address->serial << ", align 4\n";
        }else if(auto *p = dynamic_cast<IRReturn *>(& node)){
            std::cout << "ret ";
            if(p->returnType->type == BaseType::INT){
                if(auto *q = dynamic_cast<IRIntType *>(p->returnType.get())){
                    if(q->bitWidth == 32){
                        std::cout << "i32 ";
                    }else if(q->bitWidth == 8){
                        std::cout << "i8 ";
                    }
                    if(p->returnValue){
                        std::cout << "%" << p->returnValue->serial << "\n";
                    }else if(p->returnLiteral){
                        std::cout << p->returnLiteral->intValue << "\n";
                    }
                }
            }else if(p->returnType->type == BaseType::ARRAY  ){
                if(auto *q = dynamic_cast<IRArrayType *>(p->returnType.get())){
                    std::cout << "[" << q->size << " x ";
                    if(q->elementType->type == BaseType::INT){
                        if(auto *r = dynamic_cast<IRIntType *>(q->elementType.get())){
                            if(r->bitWidth == 32){
                                std::cout << "i32";
                            }else if(r->bitWidth == 8){
                                std::cout << "i8";
                            }
                        }else if(q->elementType->type == BaseType::ARRAY  ){
                            if(auto *r = dynamic_cast<IRArrayType *>(q->elementType.get())){
                                std::cout << "[" << r->size << " x ";
                                if(r->elementType->type == BaseType::INT){
                                    if(auto *s = dynamic_cast<IRIntType *>(r->elementType.get())){
                                        if(s->bitWidth == 32){
                                            std::cout << "i32";
                                        }else if(s->bitWidth == 8){
                                            std::cout << "i8";
                                        }
                                    }
                                }
                                std::cout << "]";
                            }
                        }else if(q->elementType->type == BaseType::STRUCT){
                            if(auto *r = dynamic_cast<IRStructType *>(q->elementType.get())){
                                std::cout << "%struct." << r->name;
                            }
                        }
                    }
                    std::cout << "] ";
                }
            }else if(p->returnType->type == BaseType::STRUCT){
                if(auto *q = dynamic_cast<IRStructType *>(p->returnType.get())){
                    std::cout << "%struct." << q->name << " ";
                }
            }else if(p->returnType->type == BaseType::PTR){
                std::cout << "ptr ";
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
            if(p->function->retType->type == BaseType::INT){
                std::cout << "%" << p->retVar->serial << " = call ";
            }else{
                std::cout << "call ";
            }
            
            if(p->retVar->type->type == BaseType::INT){
                if(auto *q = dynamic_cast<IRIntType *>(p->retVar.get())){
                    if(q->bitWidth == 32){
                        std::cout << "i32 ";
                    }else if(q->bitWidth == 8){
                        std::cout << "i8 ";
                    }
                }
            }else if(p->retVar->type->type == BaseType::ARRAY  ){
                if(auto *q = dynamic_cast<IRArrayType *>(p->retVar->type.get())){
                    std::cout << "[" << q->size << " x ";
                    if(q->elementType->type == BaseType::INT){
                        if(auto *r = dynamic_cast<IRIntType *>(q->elementType.get())){
                            if(r->bitWidth == 32){
                                std::cout << "i32";
                            }else if(r->bitWidth == 8){
                                std::cout << "i8";
                            }
                        }
                    }else if(q->elementType->type == BaseType::ARRAY  ){
                        if(auto *r = dynamic_cast<IRArrayType *>(q->elementType.get())){
                            std::cout << "[" << r->size << " x ";
                            if(r->elementType->type == BaseType::INT){
                                if(auto *s = dynamic_cast<IRIntType *>(r->elementType.get())){
                                    if(s->bitWidth == 32){
                                        std::cout << "i32";
                                    }else if(s->bitWidth == 8){
                                        std::cout << "i8";
                                    }
                                }
                            }
                            std::cout << "]";
                        }
                    }else if(q->elementType->type == BaseType::STRUCT){
                        if(auto *r = dynamic_cast<IRStructType *>(q->elementType.get())){
                            std::cout << "%struct." << r->name;
                        }
                    }
                    std::cout << "] ";
                }
            }else if(p->retVar->type->type == BaseType::STRUCT){
                std::cout << "void ";
            }else if(p->retVar->type->type == BaseType::VOID){
                std::cout << "void ";
            }
            if(p->function->parentStructType){
                std::cout << "@" << p->function->parentStructType->name << "::" << p->function->name << "(";
            }else{
                std::cout << "@" << p->function->name << "(";
            }
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
                        if(auto *q = dynamic_cast<IRArrayType *>(p->type.get())){
                            std::cout << "[" << q->size << " x ";
                            if(q->elementType->type == BaseType::INT){
                                if(auto *r = dynamic_cast<IRIntType *>(q->elementType.get())){
                                    if(r->bitWidth == 32){
                                        std::cout << "i32";
                                    }else if(r->bitWidth == 8){
                                        std::cout << "i8";
                                    }
                                }
                            }else if(q->elementType->type == BaseType::ARRAY  ){
                                if(auto *r = dynamic_cast<IRArrayType *>(q->elementType.get())){
                                    std::cout << "[" << r->size << " x ";
                                    if(r->elementType->type == BaseType::INT){
                                        if(auto *s = dynamic_cast<IRIntType *>(r->elementType.get())){
                                            if(s->bitWidth == 32){
                                                std::cout << "i32";
                                            }else if(s->bitWidth == 8){
                                                std::cout << "i8";
                                            }
                                        }
                                    }
                                    std::cout << "]";
                                }
                            }else if(q->elementType->type == BaseType::STRUCT){
                                if(auto *r = dynamic_cast<IRStructType *>(q->elementType.get())){
                                    std::cout << "ptr ";
                                }
                            }
                            std::cout << "] ";
                        }
                    }else if(p->type->type == BaseType::STRUCT){
                        if(auto *q = dynamic_cast<IRStructType *>(p->type.get())){
                            std::cout << "ptr ";
                        }
                    }else if(p->type->type == BaseType::PTR){
                        std::cout << "ptr ";
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
            }else if(p->type->type == BaseType::ARRAY  ){
                if(auto *q = dynamic_cast<IRArrayType *>(p->type.get())){
                    std::cout << "[" << q->size << " x ";
                    if(q->elementType->type == BaseType::INT){
                        if(auto *r = dynamic_cast<IRIntType *>(q->elementType.get())){
                            if(r->bitWidth == 32){
                                std::cout << "i32";
                            }else if(r->bitWidth == 8){
                                std::cout << "i8";
                            }
                        }
                    }else if(q->elementType->type == BaseType::ARRAY  ){
                        if(auto *r = dynamic_cast<IRArrayType *>(q->elementType.get())){
                            std::cout << "[" << r->size << " x ";
                            if(r->elementType->type == BaseType::INT){
                                if(auto *s = dynamic_cast<IRIntType *>(r->elementType.get())){
                                    if(s->bitWidth == 32){
                                        std::cout << "i32";
                                    }else if(s->bitWidth == 8){
                                        std::cout << "i8";
                                    }
                                }
                            }
                            std::cout << "]";
                        }
                    }else if(q->elementType->type == BaseType::STRUCT){
                        if(auto *r = dynamic_cast<IRStructType *>(q->elementType.get())){
                            std::cout << "%struct." << r->name;
                        }
                    }
                    std::cout << "], ";
                }
            }else if(p->type->type == BaseType::PTR){
                if(auto *q = dynamic_cast<IRPtrType *>(p->type.get())){
                    if(auto *r = dynamic_cast<IRStructType *>(& *q->baseType)){
                        std::cout << "%struct." << r->name << ", ";
                    }else if(auto *r = dynamic_cast<IRArrayType *>(q)){
                        std::cout << "[" << r->size << " x ";
                        if(r->elementType->type == BaseType::INT){
                            if(auto *s = dynamic_cast<IRIntType *>(r->elementType.get())){
                                if(s->bitWidth == 32){
                                    std::cout << "i32";
                                }else if(s->bitWidth == 8){
                                    std::cout << "i8";
                                }
                            }
                        }else if(r->elementType->type == BaseType::ARRAY  ){
                            if(auto *s = dynamic_cast<IRArrayType *>(r->elementType.get())){
                                std::cout << "[" << s->size << " x ";
                                if(s->elementType->type == BaseType::INT){
                                    if(auto *t = dynamic_cast<IRIntType *>(s->elementType.get())){
                                        if(t->bitWidth == 32){
                                            std::cout << "i32";
                                        }else if(t->bitWidth == 8){
                                            std::cout << "i8";
                                        }
                                    }
                                }
                                std::cout << "]";
                            }
                        }else if(r->elementType->type == BaseType::STRUCT){
                            if(auto *s = dynamic_cast<IRStructType *>(r->elementType.get())){
                                std::cout << "%struct." << s->name;
                            }
                        }
                        std::cout << "], ";
                    }
                }
            }
            if(p->offset != -1){
                std::cout << "ptr " <<"%" << p->base->serial << ", i32 0, i32 " << p->offset << "\n";
            }else{
                std::cout << "ptr " << "%" << p->base->serial << ", i32 0, i32 %" << p->index->serial << "\n";    
            }
        }else if(auto *p = dynamic_cast<IRExit *>(& node)){
            std::cout << "call void @__builtin_exit(i32 0)\n";
        }else if(auto *p = dynamic_cast<IRPrint *>(& node)){
            std::cout << "call void @printlnInt(i32 ";
            if(p->printLiteral){
                std::cout << p->printLiteral->intValue;
            }else if(p->printVar){
                std::cout << "%" << p->printVar->serial;
            }
            std::cout << ")\n";
        }else if(auto *p = dynamic_cast<IRGetint *>(& node)){
            std::cout << "%" << p->result->serial << " = call i32 @getInt()\n";
        }else if(auto *p = dynamic_cast<IRMemcpy *>(& node)){
            std::cout << "call void @memcpy(ptr ";
            std::cout << "%" << p->dest->serial << ", ptr ";
            std::cout << "%" << p->value->serial << ", i32 " ;
            std::cout << p->size << ")\n";
        }else if(auto *p = dynamic_cast<IRMemset *>(& node)){
            std::cout << "call void @memset(ptr ";
            std::cout << "%" << p->dest->serial << ", i32 " ;
            std::cout << p->value << ", i32 " ;
            std::cout << p->size << ")\n";
        }
    }
};
}