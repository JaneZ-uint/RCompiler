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
#include "../ast/Expression/ExprIndex.h"
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
#include "../ast/Type/TypePath.h"
#include "../ast/Type/TypeReference.h"
#include "../ast/Type/TypeUnit.h"
#include "../ast/Path.h"
namespace JaneZ {
class Parser{
private:
    std::vector<Token> tokens;

    size_t currentPos = 0;

    //Pratt Parser for expr
    //Top-Down Operator Precedence
    binaryOp getBinaryOp(tokenType current);
    unaryOp getUnaryOp(tokenType current);
    int getLeftpower(tokenType type);
    int getRightpower(tokenType type);
    std::shared_ptr<Expression> parse_expr();
    std::shared_ptr<Expression> parse_expr_interface(int power);
    std::shared_ptr<Expression> parse_expr_prefix();
    std::shared_ptr<Expression> parse_expr_infix(std::shared_ptr<Expression> &&firstExpr);
    std::shared_ptr<ExprArray> parse_expr_array();
    std::shared_ptr<ExprBlock> parse_expr_block();
    std::shared_ptr<ExprBreak> parse_expr_break();
    std::shared_ptr<ExprCall> parse_expr_call(std::shared_ptr<Expression> &&expr);
    std::shared_ptr<ExprConstBlock> parse_expr_constblock();
    std::shared_ptr<ExprContinue> parse_expr_continue();
    std::shared_ptr<ExprField> parse_expr_field(std::shared_ptr<Expression> &&expr);
    std::shared_ptr<ExprGroup> parse_expr_group();
    std::shared_ptr<ExprIf> parse_expr_if();
    std::shared_ptr<ExprLiteral> parse_expr_literal();
    std::shared_ptr<ExprLoop> parse_expr_loop();
    //std::shared_ptr<ExprMatch> parse_expr_match();
    std::shared_ptr<ExprMethodcall> parse_expr_methodcall(std::shared_ptr<Expression> &&expr);
    std::shared_ptr<ExprOpbinary> parse_expr_opbinary();
    std::shared_ptr<ExprOpunary> parse_expr_opunary();
    std::shared_ptr<ExprPath> parse_expr_path();
    std::shared_ptr<ExprReturn> parse_expr_return();
    std::shared_ptr<ExprStruct> parse_expr_struct(std::shared_ptr<Expression> &&pathInExpr);
    std::shared_ptr<ExprUnderscore> parse_expr_underscore();

    //Recursive Descent Parser
    // Item
    std::shared_ptr<Item> parse_item();
    std::shared_ptr<ItemFnDecl> parse_item_fn();
    std::shared_ptr<ItemConstDecl> parse_item_const();
    std::shared_ptr<ItemEnumDecl> parse_item_enum();
    std::shared_ptr<ItemImplDecl> parse_item_impl();
    std::shared_ptr<ItemStructDecl> parse_item_struct();
    std::shared_ptr<ItemTraitDecl> parse_item_trait();

    // Pattern
    std::shared_ptr<Pattern> parse_pattern();
    std::shared_ptr<PatternIdentifier> parse_pattern_identifier();
    std::shared_ptr<PatternLiteral> parse_pattern_literal();
    std::shared_ptr<PatternPath> parse_pattern_path();
    std::shared_ptr<PatternReference> parse_pattern_reference();
    //std::shared_ptr<PatternStruct> parse_pattern_struct();
    //std::shared_ptr<PatternTuple> parse_pattern_tuple_struct();
    std::shared_ptr<PatternWildCard> parse_pattern_wildcard();

    // Statement
    std::shared_ptr<Statement> parse_statement();
    std::shared_ptr<StmtEmpty> parse_stmt_empty();
    std::shared_ptr<StmtExpr> parse_stmt_expr();
    std::shared_ptr<StmtItem> parse_stmt_item();
    std::shared_ptr<StmtLet> parse_stmt_let();

    // Type
    std::shared_ptr<ASTNode> parse_type();
    std::shared_ptr<TypeArray> parse_type_array();
    std::shared_ptr<TypeReference> parse_type_reference();
    std::shared_ptr<TypeUnit> parse_type_unit();

    // Path
    std::shared_ptr<Path> parse_path();

public:
    Parser(std::vector<Token> t) : tokens(std::move(t)) {}

    std::shared_ptr<ASTRootNode> parse();

};



}