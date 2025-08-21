#pragma once

#include <memory>
#include <vector>
#include "../token/token.h"
#include "../ast/root.h"
#include "../ast/Expression/expression.h"
#include "../ast/Expression/ExprArray.h"
#include "../ast/Expression/ExprBlock.h"
#include "../ast/Expression/ExprBreak.h"
#include "../ast/Expression/ExprCall.h"
#include "../ast/Expression/ExprConstBlock.h"
#include "../ast/Expression/ExprContinue.h"
#include "../ast/Expression/ExprField.h"
#include "../ast/Expression/ExprGroup.h"
#include "../ast/Expression/ExprIf.h"
#include "../ast/Expression/ExprLiteral.h"
#include "../ast/Expression/ExprLoop.h"
#include "../ast/Expression/ExprMatch.h"
#include "../ast/Expression/ExprMethodcall.h"
#include "../ast/Expression/ExprOpbinary.h"
#include "../ast/Expression/ExprOpunary.h"
#include "../ast/Expression/ExprPath.h"
#include "../ast/Expression/ExprReturn.h"
#include "../ast/Expression/ExprStruct.h"
#include "../ast/Expression/ExprUnderscore.h"
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
//#include "../ast/Pattern/PatternPath.h"
#include "../ast/Pattern/PatternReference.h"
//#include "../ast/Pattern/PatternTupleStruct.h"
#include "../ast/Pattern/PatternWildcard.h"
#include "../ast/Statement/statement.h"
#include "../ast/Statement/StmtEmpty.h"
#include "../ast/Statement/StmtExpr.h"
#include "../ast/Statement/StmtItem.h"
#include "../ast/Statement/StmtLet.h"
#include "../ast/Type/type.h"
#include "../ast/Type/TypeArray.h"
#include "../ast/Type/TypeReference.h"
#include "../ast/Path.h"
namespace JaneZ {
class Parser{
private:
    std::vector<Token> tokens;

    size_t currentPos = 0;

    //Pratt Parser for expr
    //Top-Down Operator Precedence
    std::unique_ptr<Expression> parse_expr(); 
    std::unique_ptr<ExprArray> parse_expr_array();
    std::unique_ptr<ExprBlock> parse_expr_block();
    std::unique_ptr<ExprBreak> parse_expr_break();
    std::unique_ptr<ExprCall> parse_expr_call();
    std::unique_ptr<ExprConstBlock> parse_expr_constblock();
    std::unique_ptr<ExprContinue> parse_expr_continue();
    std::unique_ptr<ExprField> parse_expr_field();
    std::unique_ptr<ExprGroup> parse_expr_group();
    std::unique_ptr<ExprIf> parse_expr_if();
    std::unique_ptr<ExprLiteral> parse_expr_literal();
    std::unique_ptr<ExprLoop> parse_expr_loop();
    std::unique_ptr<ExprMatch> parse_expr_match();
    std::unique_ptr<ExprMethodcall> parse_expr_methodcall();
    std::unique_ptr<ExprOpbinary> parse_expr_opbinary();
    std::unique_ptr<ExprOpunary> parse_expr_opunary();
    std::unique_ptr<ExprPath> parse_expr_path();
    std::unique_ptr<ExprReturn> parse_expr_return();
    std::unique_ptr<ExprStruct> parse_expr_struct();
    std::unique_ptr<ExprUnderscore> parse_expr_underscore();

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
    std::unique_ptr<Pattern> parse_pattern_path();
    std::unique_ptr<PatternReference> parse_pattern_reference();
    //std::unique_ptr<PatternStruct> parse_pattern_struct();
    //std::unique_ptr<PatternTuple> parse_pattern_tuple_struct();
    std::unique_ptr<PatternWildCard> parse_pattern_wildcard();

    // Statement
    std::unique_ptr<Statement> parse_statement();
    std::unique_ptr<StmtEmpty> parse_stmt_empty();
    std::unique_ptr<StmtExpr> parse_stmt_expr();
    std::unique_ptr<StmtItem> parse_stmt_item();
    std::unique_ptr<StmtLet> parse_stmt_let();

    // Type
    std::unique_ptr<ASTNode> parse_type();
    std::unique_ptr<TypeArray> parse_type_array();
    std::unique_ptr<TypeReference> parse_type_reference();

    // Path
    std::unique_ptr<Path> parse_path();

public:
    Parser(std::vector<Token> t) : tokens(std::move(t)) {}

    std::unique_ptr<ASTRootNode> parse();

};



}