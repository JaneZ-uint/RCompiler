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

    IRGlobalBuilder() = default;

    ~IRGlobalBuilder() = default;

    void visit(ASTRootNode &node){
        globalScope->addTypeSymbol("i32", std::make_shared<IRIntType>(32));
        globalScope->addTypeSymbol("u32", std::make_shared<IRIntType>(32));
        globalScope->addTypeSymbol("isize", std::make_shared<IRIntType>(32));
        globalScope->addTypeSymbol("usize", std::make_shared<IRIntType>(32));
        globalScope->addTypeSymbol("bool", std::make_shared<IRIntType>(8));
        globalScope->addTypeSymbol("void", std::make_shared<IRVoidType>());

        //Wait to add more functions like print, println, etc.

        for(auto& item : node.child){
            visit(*item);
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
        globalScope->addConstantSymbol(node.identifier, node.value);
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
            }
        }
        globalScope->addFunctionSymbol(node.identifier,std::make_shared<IRFunction>(retType,funcName,paramList));
    }

    void visit(ItemImplDecl &node){
        //idk what to do here
    }

    void visit(ItemStructDecl &node){
        std::vector<std::shared_ptr<IRType>> fieldTypes;
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