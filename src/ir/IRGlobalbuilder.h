# pragma once

#include "../ast/astvisitor.h"
#include "../ast/root.h"
#include "../ast/Expression/ExprStruct.h"
#include "../ast/Expression/ExprLiteral.h"
#include "../ast/Expression/ExprOpbinary.h"
#include "../ast/Expression/ExprMethodcall.h"
#include "../ast/Expression/ExprPath.h"
#include "../ast/Item/ItemConst.h"
#include "../ast/Item/ItemEnum.h"
#include "../ast/Item/ItemFn.h"
#include "../ast/Item/ItemImpl.h"
#include "../ast/Item/ItemStruct.h"
#include "../ast/Item/ItemTrait.h"
#include "../ast/Pattern/PatternIdentifier.h"
#include "../ast/Pattern/PatternReference.h"
#include "../ast/Statement/StmtItem.h"
#include "../ast/Statement/StmtLet.h"
#include "../ast/Type/type.h"
#include "../ast/Type/TypeArray.h"
#include "../ast/Type/TypePath.h"
#include "../ast/Type/TypeReference.h"
#include "../ast/Type/TypeUnit.h"
#include "IRBlock.h"
#include "IRFunction.h"
#include "IRParam.h"
#include "IRScope.h"
#include "IRType.h"
#include "IRVar.h"
#include <memory>
#include <vector>

namespace JaneZ {
class IRGlobalBuilder {
public:
    std::shared_ptr<IRScope> globalScope;
    std::vector<std::shared_ptr<ItemImplDecl>> implList;

    IRGlobalBuilder() = default;

    ~IRGlobalBuilder() = default;

    void visit(ASTRootNode &node){
        globalScope = std::make_shared<IRScope>();
        globalScope->addTypeSymbol("i32", std::make_shared<IRIntType>(32));
        globalScope->addTypeSymbol("u32", std::make_shared<IRIntType>(32));
        globalScope->addTypeSymbol("isize", std::make_shared<IRIntType>(32));
        globalScope->addTypeSymbol("usize", std::make_shared<IRIntType>(32));
        globalScope->addTypeSymbol("bool", std::make_shared<IRIntType>(8));
        globalScope->addTypeSymbol("BOOL", std::make_shared<IRIntType>(1));
        globalScope->addTypeSymbol("void", std::make_shared<IRVoidType>());

        //Wait to add more functions like print, println, etc.

        for(auto& item : node.child){
            if(auto *p = dynamic_cast<ItemImplDecl *>(& *item)){
                implList.push_back(std::static_pointer_cast<ItemImplDecl>(item));
                continue;
            }
            visit(*item);
        }

        for(auto& implItem : implList){
            visit(*implItem);
        }
    }

    void visit(Item &node){
        if(auto *p = dynamic_cast<ItemFnDecl *>(& node)){
            visit(*p);
        }else if(auto *p = dynamic_cast<ItemStructDecl *>(& node)){
            visit(*p);
        }else if(auto *p = dynamic_cast<ItemEnumDecl *>(& node)){
            visit(*p);
        }else if(auto *p = dynamic_cast<ItemConstDecl *>(& node)){
            visit(*p);
        }else if(auto *p = dynamic_cast<ItemImplDecl *>(& node)){
            visit(*p);
        }else if(auto *p = dynamic_cast<ItemTraitDecl *>(& node)){
            visit(*p);
        }
    }

    void visit(ItemConstDecl &node){
        constInfo info;
        if(auto *p = dynamic_cast<Type *>(& *node.type)){
            //only primitive const for now
            if(p->type == I32){
                info.type = "i32";
            }else if(p->type == U32){
                info.type = "u32";
            }else if(p->type == ISIZE){
                info.type = "isize";
            }else if(p->type == USIZE){
                info.type = "usize";
            }
        }
        globalScope->addConstantSymbol(node.identifier, info);
    }

    void visit(ItemEnumDecl &node){
        //TODO just wait and see babe
    }

    void visit(ItemFnDecl &node){
        std::shared_ptr<IRType> retType = nullptr;
        if(node.returnType){
            retType = resolveType(*node.returnType);
        }
        std::string funcName = node.identifier;
        std::shared_ptr<IRParam> paramList = std::make_shared<IRParam>();
        if(node.fnParameters.FunctionParam.size() > 0){
            for(auto& param : node.fnParameters.FunctionParam){
                auto currentVar = std::make_shared<IRVar>();
                //left with ref and mut to do
                if(auto *p = dynamic_cast<PatternIdentifier *>(& *param.pattern)){
                    currentVar->varName = p->identifier;
                }else if(auto *p = dynamic_cast<PatternReference *>(& *param.pattern)){
                    if(auto *q = dynamic_cast<PatternIdentifier *>(& *p->patternWithoutRange)){
                        currentVar->varName = q->identifier;
                    }
                }
                currentVar->reName = currentVar->varName;
                if(param.type){
                    currentVar->type = resolveType(*param.type);
                }
                paramList->paramList.push_back(currentVar);
            }
        }
        if(!retType){
            retType = std::make_shared<IRVoidType>();
        }else{
            if(auto *p = dynamic_cast<IRStructType *>(& *retType)){
                auto ptrVar = std::make_shared<IRVar>();
                ptrVar->type = std::make_shared<IRPtrType>(retType);
                ptrVar->varName = "return_ptr";
                ptrVar->reName = "return_ptr";
                paramList->paramList.push_back(ptrVar);
            }
        }
        auto currentFunction = std::make_shared<IRFunction>(retType,funcName,paramList);
        currentFunction->body = std::make_shared<IRBlock>();
        globalScope->addFunctionSymbol(node.identifier,currentFunction);
    }

    void visit(ItemImplDecl &node){
        if(auto *p = dynamic_cast<Path *>(& *node.targetType)){
            if(p->pathSegments.type == IDENTIFIER){
                std::string typeName = p->pathSegments.identifier;
                auto tp = globalScope->lookupTypeSymbol(typeName);
                if(tp){
                    if(auto structType = std::dynamic_pointer_cast<IRStructType>(tp)){
                        for(auto & itemFn: node.item_trait_fn){
                            std::shared_ptr<IRType> retType;
                            if(itemFn->returnType){
                                retType = resolveType(*itemFn->returnType);
                            }
                            std::string funcName = itemFn->identifier;
                            std::shared_ptr<IRParam> paramList =  std::make_shared<IRParam>();
                            if(itemFn->fnParameters.SelfParam.isShortSelf){
                                if(itemFn->fnParameters.SelfParam.short_self.is_and){
                                    auto selfParam = std::make_shared<IRVar>();
                                    selfParam->varName = "self";
                                    selfParam->reName = "self";
                                    selfParam->type = std::make_shared<IRPtrType>(structType);
                                    selfParam->isSelf = true;
                                    paramList->paramList.push_back(selfParam);
                                }else{
                                    auto selfParam = std::make_shared<IRVar>();
                                    selfParam->varName = "self";
                                    selfParam->reName = "self";
                                    selfParam->type = structType;
                                    selfParam->isSelf = true;
                                    paramList->paramList.push_back(selfParam);
                                }
                            } 
                            if(itemFn->fnParameters.FunctionParam.size() > 0){
                                for(auto& param : itemFn->fnParameters.FunctionParam){
                                    auto currentVar = std::make_shared<IRVar>();
                                    if(auto *p = dynamic_cast<PatternIdentifier *>(& *param.pattern)){
                                        currentVar->varName = p->identifier;
                                    }else if(auto *p = dynamic_cast<PatternReference *>(& *param.pattern)){
                                        if(auto *q = dynamic_cast<PatternIdentifier *>(& *p->patternWithoutRange)){
                                            currentVar->varName = q->identifier;
                                        }
                                    }
                                    currentVar->reName = currentVar->varName;
                                    if(param.type){
                                        currentVar->type = resolveType(*param.type);
                                    }
                                    paramList->paramList.push_back(currentVar);
                                }
                            }
                            if(!retType){
                                retType = std::make_shared<IRVoidType>();
                            }else{
                                if(auto *p = dynamic_cast<IRStructType *>(& *retType)){
                                    auto ptrVar = std::make_shared<IRVar>();
                                    ptrVar->type = std::make_shared<IRPtrType>(retType);
                                    ptrVar->varName = "return_ptr";
                                    ptrVar->reName = "return_ptr";
                                    paramList->paramList.push_back(ptrVar);
                                }
                            }
                            auto currentFunction = std::make_shared<IRFunction>(retType,funcName,paramList);
                            currentFunction->body = std::make_shared<IRBlock>();
                            currentFunction->parentStructType = structType;
                            structType->memberFunctions.push_back(currentFunction);
                        }
                    }
                    
                }
            }
        }
    }

    void caculateStructSize(std::shared_ptr<IRStructType> structType){
        int totalSize = 0;
        for(auto & member : structType->memberTypes){
            if(auto *p = dynamic_cast<IRIntType *>(member.second.get())){
                totalSize += p->bitWidth / 8;
            }else if(auto *p = dynamic_cast<IRArrayType *>(member.second.get())){
                if(auto *q = dynamic_cast<IRIntType *>(p->elementType.get())){
                    totalSize += (p->size * q->bitWidth) / 8;
                }else if(auto *q = dynamic_cast<IRArrayType *>(member.second.get())){
                    if(auto *r = dynamic_cast<IRIntType *>(q->elementType.get())){
                        totalSize += (p->size * q->size * r->bitWidth) /8;
                    }
                }
            }else if(auto *p = dynamic_cast<IRStructType *>(member.second.get())){
                totalSize += p->size;
            }
        }
        structType->size = totalSize;
    }

    void visit(ItemStructDecl &node){
        std::vector<std::pair<std::string,std::shared_ptr<IRType>>> fieldTypes;
        std::string structName = node.identifier;
        for(auto & field : node.item_struct){
            if(field.structElem){
                fieldTypes.push_back({field.identifier, resolveType(*field.structElem)});
            }
        }
        auto currentStructType = std::make_shared<IRStructType>();
        currentStructType->name = structName;
        currentStructType->true_name = structName;
        currentStructType->memberTypes = fieldTypes;
        caculateStructSize(currentStructType);
        globalScope->addTypeSymbol(structName, currentStructType);
    }

    void visit(ItemTraitDecl &node){
        //no need 
    }

    std::shared_ptr<IRType> resolveType(ASTNode &typeNode){
        if(auto *p = dynamic_cast<Type *>(& typeNode)){
            return visit(*p);
        }else if(auto *p = dynamic_cast<TypeArray *>(& typeNode)){
            return visit(*p);
        }else if(auto *p = dynamic_cast<Path *>(& typeNode)){
            return visit(*p);
        }else if(auto *p = dynamic_cast<TypeReference *>(& typeNode)){
            return visit(*p);
        }else if(auto *p = dynamic_cast<TypeUnit *>(& typeNode)){
            return visit(*p);   
        }
        throw std::runtime_error("IRBuilder resolveType error: unknown type node");
    }

    std::shared_ptr<IRIntType> visit(Type &node){
        if(node.type == I32){
            return std::dynamic_pointer_cast<IRIntType>(globalScope->lookupTypeSymbol("i32"));
        }else if(node.type == U32){
            return std::dynamic_pointer_cast<IRIntType>(globalScope->lookupTypeSymbol("u32"));
        }else if(node.type == ISIZE){
            return std::dynamic_pointer_cast<IRIntType>(globalScope->lookupTypeSymbol("isize"));
        }else if(node.type == USIZE){
            return std::dynamic_pointer_cast<IRIntType>(globalScope->lookupTypeSymbol("usize"));
        }else if(node.type == BOOL){
            return std::dynamic_pointer_cast<IRIntType>(globalScope->lookupTypeSymbol("bool"));
        }
        throw std::runtime_error("Unknown primitive type");
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
                    constInfo res = globalScope->lookupConstantSymbol(constName);
                    size = res.value;
                }
            }else if(auto *opbinary = dynamic_cast<ExprOpbinary *>(& *node.expr)){
                if(opbinary->op == PLUS){
                    if(auto *left = dynamic_cast<ExprPath *>(& *opbinary->left)){
                        if(left->pathFirst->pathSegments.type == IDENTIFIER){
                            std::string constName = left->pathFirst->pathSegments.identifier;
                            constInfo res = globalScope->lookupConstantSymbol(constName);
                            size += res.value;
                        }
                    }else if(auto *leftLiteral = dynamic_cast<ExprLiteral *>(& *opbinary->left)){
                        size += leftLiteral->integer;
                    }
                    if(auto *right = dynamic_cast<ExprPath *>(& *opbinary->right)){
                        if(right->pathFirst->pathSegments.type == IDENTIFIER){
                            std::string constName = right->pathFirst->pathSegments.identifier;
                            constInfo res = globalScope->lookupConstantSymbol(constName);
                            size += res.value;
                        }
                    }else if(auto *rightLiteral = dynamic_cast<ExprLiteral *>(& *opbinary->right)){
                        size += rightLiteral->integer;
                    }
                }else if(opbinary->op == MINUS){
                    if(auto *left = dynamic_cast<ExprPath *>(& *opbinary->left)){
                        if(left->pathFirst->pathSegments.type == IDENTIFIER){
                            std::string constName = left->pathFirst->pathSegments.identifier;
                            constInfo res = globalScope->lookupConstantSymbol(constName);
                            size += res.value;
                        }
                    }else if(auto *leftLiteral = dynamic_cast<ExprLiteral *>(& *opbinary->left)){
                        size += leftLiteral->integer;
                    }
                    if(auto *right = dynamic_cast<ExprPath *>(& *opbinary->right)){
                        if(right->pathFirst->pathSegments.type == IDENTIFIER){
                            std::string constName = right->pathFirst->pathSegments.identifier;
                            constInfo res = globalScope->lookupConstantSymbol(constName);
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
        auto typeName = node.pathSegments.identifier;
        auto structType = globalScope->lookupTypeSymbol(typeName);
        return std::dynamic_pointer_cast<IRStructType>(structType);
    }

    std::shared_ptr<IRPtrType> visit(TypeReference &node){
        auto refType = std::make_shared<IRPtrType>();
        if(node.typeNoBounds){
            refType->baseType = resolveType(*node.typeNoBounds);
        }
        return refType;
    }

    std::shared_ptr<IRVoidType> visit(TypeUnit &node){
        return std::make_shared<IRVoidType>();
    }
};
}