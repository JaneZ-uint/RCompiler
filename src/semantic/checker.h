# pragma once

#include "NameResolver.h"
#include "globalScope.h"
namespace JaneZ {
class Checker{
public:
    void semantic_check(GlobalScopeBuilder &global_scope_builder,NameResolver &name_resolver, ASTRootNode &root){
        global_scope_builder.visit(root);
        name_resolver.current_scope = global_scope_builder.global_scope;
        name_resolver.visit(root);
    }
};
}