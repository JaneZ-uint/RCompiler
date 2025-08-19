#pragma once

#include <memory>
#include <vector>
#include "../ast/Item/item.h"
#include "../ast/Item/ItemFn.h"
#include "../ast/Item/ItemConst.h"
#include "../ast/Item/ItemEnum.h"
#include "../ast/Item/ItemImpl.h"
#include "../ast/Item/ItemStruct.h"
#include "../ast/Item/ItemTrait.h"
#include "../ast/Pattern/pattern.h"
#include "../ast/Pattern/PatternIdentifier.h"
#include "../ast/Pattern/PatternLiteral.h"
#include "../ast/Pattern/PatternPath.h"
#include "../ast/Pattern/PatternReference.h"
#include "../ast/Pattern/PatternStruct.h"
#include "../ast/Pattern/PatternTuple.h"
#include "../ast/Pattern/PatternWildcard.h"
#include "../ast/Statement/statement.h"
#include "../ast/Statement/StmtEmpty.h"
#include "../ast/Statement/StmtExpr.h"
#include "../ast/Statement/StmtItem.h"
#include "../ast/Statement/StmtLet.h"
#include "../ast/Type/type.h"
#include "../ast/Type/TypeArray.h"
#include "../ast/Type/TypeInferred.h"
#include "../ast/Type/TypePath.h"
#include "../ast/Type/TypeReference.h"
#include "../ast/Type/TypeSlice.h"
namespace JaneZ {
class ASTRootNode;
class Token;
class Item;
class ItemFnDecl;
class ItemConstDecl;
class ItemEnumDecl;
class ItemImplDecl;
class ItemStructDecl;
class ItemTraitDecl;
class Pattern;
class PatternIdentifier;
class PatternLiteral;
class PatternPath;
class PatternReference;
class PatternStruct;
class PatternTuple;
class PatternWildcard;
class Statement;
class StmtEmpty;
class StmtExpr;
class StmtItem;
class StmtLet;
class Type;
class TypeArray;
class TypeInferred;
class TypePath;
class TypeReference;
class TypeSlice;
class Parser{
private:
    std::vector<Token> tokens;

    size_t currentPos = 0;

    //Pratt Parser
    //Top-Down Operator Precedence


    //Recursive Descent Parser
    // Item
    std::unique_ptr<Item> parse_item();
    std::unique_ptr<ItemFnDecl> parse_item_fn();
    std::unique_ptr<ItemConstDecl> parse_item_const();
    std::unique_ptr<ItemEnumDecl> parse_item_enum();
    std::unique_ptr<ItemImplDecl> parse_item_impl();
    std::unique_ptr<ItemStructDecl> parse_item_struct();
    std::unique_ptr<ItemTraitDecl> parse_item_trait();

    // Pattern
    std::unique_ptr<Pattern> parse_pattern();
    std::unique_ptr<PatternIdentifier> parse_pattern_identifier();
    std::unique_ptr<PatternLiteral> parse_pattern_literal();
    std::unique_ptr<PatternPath> parse_pattern_path();
    std::unique_ptr<PatternReference> parse_pattern_reference();
    std::unique_ptr<PatternStruct> parse_pattern_struct();
    std::unique_ptr<PatternTuple> parse_pattern_tuple();
    std::unique_ptr<PatternWildcard> parse_pattern_wildcard();

    // Statement
    std::unique_ptr<Statement> parse_statement();
    std::unique_ptr<StmtEmpty> parse_stmt_empty(Token current);
    std::unique_ptr<StmtExpr> parse_stmt_expr(Token current);
    std::unique_ptr<StmtItem> parse_stmt_item(Token current);
    std::unique_ptr<StmtLet> parse_stmt_let(Token current);

    // Type
    std::unique_ptr<Type> parse_type();
    std::unique_ptr<TypeArray> parse_type_array();
    std::unique_ptr<TypeInferred> parse_type_inferred();
    std::unique_ptr<TypePath> parse_type_path();
    std::unique_ptr<TypeReference> parse_type_reference();
    std::unique_ptr<TypeSlice> parse_type_slice();

public:
    Parser(std::vector<Token> t) : tokens(std::move(t)) {}

    std::unique_ptr<ASTRootNode> parse();

};



}