#pragma once

#include <memory>
#include <vector>
namespace JaneZ {
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

public:
    Parser(std::vector<Token> t) : tokens(std::move(t)) {}

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
    std::unique_ptr<StmtEmpty> parse_stmt_empty();
    std::unique_ptr<StmtExpr> parse_stmt_expr();
    std::unique_ptr<StmtItem> parse_stmt_item();
    std::unique_ptr<StmtLet> parse_stmt_let();

    // Type
    std::unique_ptr<Type> parse_type();
    std::unique_ptr<TypeArray> parse_type_array();
    std::unique_ptr<TypeInferred> parse_type_inferred();
    std::unique_ptr<TypePath> parse_type_path();
    std::unique_ptr<TypeReference> parse_type_reference();
    std::unique_ptr<TypeSlice> parse_type_slice();

};

}