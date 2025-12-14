# pragma once

#include "../ast/astvisitor.h"
#include "../ast/root.h"
#include "../ast/Expression/ExprStruct.h"
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
#include "IRParam.h"
#include "IRScope.h"
#include "IRType.h"
#include "IRVar.h"
#include "IRSelf.h"
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
                implList.push_back(std::shared_ptr<ItemImplDecl>(p));
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
        std::shared_ptr<IRType> retType;
        if(node.returnType){
            retType = resolveType(*node.returnType);
        }
        std::string funcName = node.identifier;
        std::shared_ptr<IRParam> paramList = std::make_shared<IRParam>();
        if(node.fnParameters.SelfParam.isShortSelf){
            auto selfParam = std::make_shared<IRSelf>();
            paramList->paramList.push_back(selfParam);
        } 
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
        globalScope->addFunctionSymbol(node.identifier,std::make_shared<IRFunction>(retType,funcName,paramList));
    }

    void visit(ItemImplDecl &node){
        if(auto *p = dynamic_cast<Path *>(& *node.targetType)){
            if(p->pathSegments.type == IDENTIFIER){
                std::string typeName = p->pathSegments.identifier;
                auto tp = globalScope->lookupTypeSymbol(typeName);
                if(tp){
                    if(auto structType = std::dynamic_pointer_cast<IRStructType>(tp)){
                        for(auto &itemConst  : node.item_trait_const){
                            std::string constName = itemConst->identifier;
                            auto constValue = itemConst->value;
                            structType->memberConstants.push_back({constName, constValue});
                        }
                        for(auto & itemFn: node.item_trait_fn){
                            std::shared_ptr<IRType> retType;
                            if(itemFn->returnType){
                                retType = resolveType(*itemFn->returnType);
                            }
                            std::string funcName = itemFn->identifier;
                            std::shared_ptr<IRParam> paramList =  std::make_shared<IRParam>();
                            if(itemFn->fnParameters.SelfParam.isShortSelf){
                                auto selfParam = std::make_shared<IRSelf>();
                                paramList->paramList.push_back(selfParam);
                            } 
                            if(itemFn->fnParameters.FunctionParam.size() > 0){
                                for(auto& param : itemFn->fnParameters.FunctionParam){
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
                            //processing the function body is needed.
                            //TODO 
                            auto fnScope = std::make_shared<IRScope>();
                            fnScope->parent = globalScope;
                            globalScope->children.push_back(fnScope);
                            if(itemFn->fnParameters.SelfParam.isShortSelf){
                                //todo deal with self
                                auto currentSelf = std::make_shared<IRVar>();
                                currentSelf->varName = "self";
                                currentSelf->reName = "self";
                                currentSelf->type = structType;
                                fnScope->addValueSymbol("self", currentSelf);
                            }
                            for(auto& param : paramList->paramList){
                                if(auto varParam = std::dynamic_pointer_cast<IRVar>(param)){
                                    fnScope->addValueSymbol(varParam->varName, varParam);
                                }
                            }
                            structType->memberFunctions.push_back(std::make_shared<IRFunction>(retType,funcName,paramList));
                        }
                    }
                    
                }
            }
        }
    }

    void visit(ItemStructDecl &node){
        std::vector<std::pair<std::string,std::shared_ptr<IRType>>> fieldTypes;
        std::string structName = node.identifier;
        for(auto & field : node.item_struct){
            if(field.structElem){
                fieldTypes.push_back({field.identifier, resolveType(*field.structElem)});
            }
        }
        globalScope->addTypeSymbol(structName, std::make_shared<IRStructType>(structName, fieldTypes));
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
            return std::make_shared<IRIntType>(32);
        }else if(node.type == U32){
            return std::make_shared<IRIntType>(32);
        }else if(node.type == ISIZE){
            return std::make_shared<IRIntType>(32);
        }else if(node.type == USIZE){
            return std::make_shared<IRIntType>(32);
        }else if(node.type == BOOL){
            return std::make_shared<IRIntType>(8);
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
            size = node.expr->constValue;
        }
        return std::make_shared<IRArrayType>(currentType, size);
    }

    std::shared_ptr<IRStructType> visit(Path &node){
        if(node.pathSegments.type == IDENTIFIER){
            auto typeName = node.pathSegments.identifier;
            auto structType = globalScope->lookupTypeSymbol(typeName);
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
        return std::make_shared<IRVoidType>();
    }
};
}