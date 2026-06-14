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

    constInfo constInfoFromDecl(ItemConstDecl &node) {
        constInfo info{node.value, "null"};
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
        return info;
    }

    constInfo requireConstInfo(const std::string &name) {
        if(name.empty()){
            throw std::runtime_error("IRGlobalBuilder: empty constant name");
        }
        auto info = globalScope->lookupConstantSymbol(name);
        if(info.type == "null"){
            throw std::runtime_error("IRGlobalBuilder: constant not found: " + name);
        }
        return info;
    }

    constInfo requireConstInfo(ExprPath *path) {
        if(!path || !path->pathFirst){
            throw std::runtime_error("IRGlobalBuilder: malformed constant path");
        }
        if(path->pathFirst->pathSegments.type != IDENTIFIER ||
           path->pathFirst->pathSegments.identifier.empty()){
            throw std::runtime_error("IRGlobalBuilder: malformed constant path");
        }
        std::string name = path->pathFirst->pathSegments.identifier;
        if(path->pathSecond){
            if(path->pathSecond->pathSegments.type != IDENTIFIER ||
               path->pathSecond->pathSegments.identifier.empty()){
                throw std::runtime_error("IRGlobalBuilder: malformed associated constant path");
            }
            name += "::" + path->pathSecond->pathSegments.identifier;
        }
        return requireConstInfo(name);
    }

    void addAssociatedConstants(ItemImplDecl &node) {
        auto *target = dynamic_cast<Path *>(& *node.targetType);
        if(!target || target->pathSegments.type != IDENTIFIER || target->pathSegments.identifier.empty()){
            return;
        }
        const std::string typeName = target->pathSegments.identifier;
        for(auto &constItem : node.item_trait_const){
            const std::string qualifiedName = typeName + "::" + constItem->identifier;
            if(globalScope->constant_table.find(qualifiedName) == globalScope->constant_table.end()){
                globalScope->addConstantSymbol(qualifiedName, constInfoFromDecl(*constItem));
            }
        }
    }

    void visit(ASTRootNode &node){
        globalScope = std::make_shared<IRScope>();
        globalScope->addTypeSymbol("i32", std::make_shared<IRIntType>(32));
        globalScope->addTypeSymbol("u32", std::make_shared<IRIntType>(32, true));
        globalScope->addTypeSymbol("isize", std::make_shared<IRIntType>(64));
        globalScope->addTypeSymbol("usize", std::make_shared<IRIntType>(64, true));
        globalScope->addTypeSymbol("bool", std::make_shared<IRIntType>(8, true));
        globalScope->addTypeSymbol("BOOL", std::make_shared<IRIntType>(1, true));
        globalScope->addTypeSymbol("char", std::make_shared<IRIntType>(32, true));
        globalScope->addTypeSymbol("String", std::make_shared<IRPtrType>(std::make_shared<IRIntType>(8, true)));
        globalScope->addTypeSymbol("str", std::make_shared<IRPtrType>(std::make_shared<IRIntType>(8, true)));
        globalScope->addTypeSymbol("void", std::make_shared<IRVoidType>());

        //Wait to add more functions like print, println, etc.
        implList.clear();

        for(auto& item : node.child){
            if(auto *p = dynamic_cast<ItemImplDecl *>(& *item)){
                implList.push_back(std::static_pointer_cast<ItemImplDecl>(item));
                continue;
            }
            if(auto *p = dynamic_cast<ItemConstDecl *>(& *item)){
                visit(*p);
                continue;
            }
            if(auto *p = dynamic_cast<ItemEnumDecl *>(& *item)){
                visit(*p);
                continue;
            }
        }

        for(auto& implItem : implList){
            addAssociatedConstants(*implItem);
        }

        for(auto& item : node.child){
            if(dynamic_cast<ItemImplDecl *>(& *item) ||
               dynamic_cast<ItemConstDecl *>(& *item) ||
               dynamic_cast<ItemEnumDecl *>(& *item)){
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
        globalScope->addConstantSymbol(node.identifier, constInfoFromDecl(node));
    }

    void visit(ItemEnumDecl &node){
        globalScope->addTypeSymbol(node.identifier, std::make_shared<IRIntType>(32));
        for(int i = 0;i < node.item_enum.size();i++){
            constInfo info;
            info.value = i;
            info.type = node.identifier;
            std::string qualifiedName = node.identifier + "::" + node.item_enum[i];
            if(globalScope->constant_table.find(qualifiedName) == globalScope->constant_table.end()){
                globalScope->addConstantSymbol(qualifiedName, info);
            }
        }
    }

    void visit(ItemFnDecl &node){
        std::shared_ptr<IRType> retType = nullptr;
        if(node.returnType){
            retType = resolveType(*node.returnType);
        }
        std::string funcName = node.identifier;
        std::shared_ptr<IRParam> paramList = std::make_shared<IRParam>();
        std::vector<std::shared_ptr<IRType>> typeList;
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
                    typeList.push_back(currentVar->type);
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
                typeList.push_back(ptrVar->type);
            }else if(auto *p = dynamic_cast<IRArrayType *>(& *retType)){
                auto ptrVar = std::make_shared<IRVar>();
                ptrVar->type = std::make_shared<IRPtrType>(retType);
                ptrVar->varName = "return_ptr";
                ptrVar->reName = "return_ptr";
                paramList->paramList.push_back(ptrVar);
                typeList.push_back(ptrVar->type);
            }
        }
        auto currentFunction = std::make_shared<IRFunction>(retType,funcName,paramList);
        currentFunction->body = std::make_shared<IRBlock>();
        currentFunction->typeList = typeList;
        globalScope->addFunctionSymbol(node.identifier,currentFunction);
    }

    void visit(ItemImplDecl &node){
        //todo with typelist
        if(auto *p = dynamic_cast<Path *>(& *node.targetType)){
            if(p->pathSegments.type == IDENTIFIER){
                std::string typeName = p->pathSegments.identifier;
                auto tp = globalScope->lookupTypeSymbol(typeName);
                if(tp){
                    if(auto structType = std::dynamic_pointer_cast<IRStructType>(tp)){
                        globalScope->type_table["Self"] = structType;
                        for(auto & itemFn: node.item_trait_fn){
                            std::shared_ptr<IRType> retType;
                            if(itemFn->returnType){
                                retType = resolveType(*itemFn->returnType);
                            }
                            std::string funcName = itemFn->identifier;
                            std::shared_ptr<IRParam> paramList =  std::make_shared<IRParam>();
                            std::vector<std::shared_ptr<IRType>> typeList;
                            if(itemFn->fnParameters.SelfParam.isShortSelf){
                                if(itemFn->fnParameters.SelfParam.short_self.is_and){
                                    auto selfParam = std::make_shared<IRVar>();
                                    selfParam->varName = "self";
                                    selfParam->reName = "self";
                                    selfParam->type = std::make_shared<IRPtrType>(structType);
                                    typeList.push_back(selfParam->type);
                                    selfParam->isSelf = true;
                                    paramList->paramList.push_back(selfParam);
                                }else{
                                    auto selfParam = std::make_shared<IRVar>();
                                    selfParam->varName = "self";
                                    selfParam->reName = "self";
                                    selfParam->type = structType;
                                    typeList.push_back(selfParam->type);
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
                                        typeList.push_back(currentVar->type);
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
                                    typeList.push_back(ptrVar->type);
                                }else if(auto *p = dynamic_cast<IRArrayType *>(& *retType)){
                                    auto ptrVar = std::make_shared<IRVar>();
                                    ptrVar->type = std::make_shared<IRPtrType>(retType);
                                    ptrVar->varName = "return_ptr";
                                    ptrVar->reName = "return_ptr";
                                    paramList->paramList.push_back(ptrVar);
                                    typeList.push_back(ptrVar->type);
                                }
                            }
                            auto currentFunction = std::make_shared<IRFunction>(retType,funcName,paramList);
                            currentFunction->body = std::make_shared<IRBlock>();
                            currentFunction->parentStructType = structType;
                            currentFunction->typeList = typeList;
                            structType->memberFunctions.push_back(currentFunction);
                        }
                        globalScope->type_table.erase("Self");
                    }
                    
                }
            }
        }
    }

    void caculateStructSize(std::shared_ptr<IRStructType> structType){
        int totalSize = 0;
        for(auto & member : structType->memberTypes){
            if(auto *inttype = dynamic_cast<IRIntType *>(& *member.second)){
                if(inttype->bitWidth == 8){
                    totalSize += 4;
                    continue;
                }
            }
            totalSize += member.second->size;
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

    std::shared_ptr<IRType> visit(Type &node){
        if(node.type == I32){
            return globalScope->lookupTypeSymbol("i32");
        }else if(node.type == U32){
            return globalScope->lookupTypeSymbol("u32");
        }else if(node.type == ISIZE){
            return globalScope->lookupTypeSymbol("isize");
        }else if(node.type == USIZE){
            return globalScope->lookupTypeSymbol("usize");
        }else if(node.type == BOOL){
            return globalScope->lookupTypeSymbol("bool");
        }else if(node.type == CHAR){
            return globalScope->lookupTypeSymbol("char");
        }else if(node.type == STR){
            return globalScope->lookupTypeSymbol("String");
        }else if(node.type == ENUM){
            return globalScope->lookupTypeSymbol("i32");
        }
        throw std::runtime_error("Unknown primitive type");
    }

    void caculateArraySize(std::shared_ptr<IRArrayType> arrayType){
        if(auto *innerArray = dynamic_cast<IRArrayType *>(& *arrayType->elementType)){
            caculateArraySize(std::dynamic_pointer_cast<IRArrayType>(arrayType->elementType));
            arrayType->size = innerArray->size * arrayType->length;
            if(auto inttype = std::dynamic_pointer_cast<IRIntType>(innerArray->elementType)){
                if(inttype->bitWidth == 8){
                    arrayType->size = (innerArray->size / 4) * arrayType->length;
                    if(arrayType->size % 4 != 0){
                        arrayType->size += 4 - (arrayType->size % 4);
                    }
                }
            }
        }else{
            arrayType->size = arrayType->elementType->size * arrayType->length;
            if(auto inttype = std::dynamic_pointer_cast<IRIntType>(arrayType->elementType)){
                if(inttype->bitWidth == 8){
                    if(arrayType->size % 4 != 0){
                        arrayType->size += 4 - (arrayType->size % 4);
                    }
                }
            }
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
                size = requireConstInfo(path).value;
            }else if(auto *opbinary = dynamic_cast<ExprOpbinary *>(& *node.expr)){
                if(opbinary->op == PLUS){
                    if(auto *left = dynamic_cast<ExprPath *>(& *opbinary->left)){
                        size += requireConstInfo(left).value;
                    }else if(auto *leftLiteral = dynamic_cast<ExprLiteral *>(& *opbinary->left)){
                        size += leftLiteral->integer;
                    }
                    if(auto *right = dynamic_cast<ExprPath *>(& *opbinary->right)){
                        size += requireConstInfo(right).value;
                    }else if(auto *rightLiteral = dynamic_cast<ExprLiteral *>(& *opbinary->right)){
                        size += rightLiteral->integer;
                    }
                }else if(opbinary->op == MINUS){
                    if(auto *left = dynamic_cast<ExprPath *>(& *opbinary->left)){
                        size += requireConstInfo(left).value;
                    }else if(auto *leftLiteral = dynamic_cast<ExprLiteral *>(& *opbinary->left)){
                        size += leftLiteral->integer;
                    }
                    if(auto *right = dynamic_cast<ExprPath *>(& *opbinary->right)){
                        size -= requireConstInfo(right).value;
                    }else if(auto *rightLiteral = dynamic_cast<ExprLiteral *>(& *opbinary->right)){
                        size -= rightLiteral->integer;
                    }
                }
            }
        }
        auto arrayType = std::make_shared<IRArrayType>(currentType, size);
        caculateArraySize(arrayType);
        return arrayType;
    }

    std::shared_ptr<IRType> visit(Path &node){
        auto typeName = node.pathSegments.identifier;
        auto type = globalScope->lookupTypeSymbol(typeName);
        if (type) return type;
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
        return std::make_shared<IRVoidType>();
    }
};
}
