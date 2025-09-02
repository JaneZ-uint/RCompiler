# pragma once

namespace JaneZ {
class ExprArray;
class ExprBlock;
class ExprBreak;
class ExprCall;
class ExprContinue;
class ExprField;
class ExprGroup;
class ExprIf;
class ExprIndex;
class ExprLiteral;
class ExprLoop;
class ExprMatch;
class ExprMethodcall;
class ExprOpbinary;
class ExprOpunary;
class ExprPath;
class ExprReturn;
class ExprUnderscore;

class ItemConstDecl;
class ItemEnumDecl;
class ItemFnDecl;
class ItemImplDecl;
class ItemModuleDecl;
class ItemStructDecl;
class ItemTraitDecl;

class PatternIdentifier;
class PatternLiteral;
class PatternPath;
class PatternReference;
class PatternTupleStruct;
class PatternWildCard;

class StmtEmpty;
class StmtExpr;
class StmtItem;
class StmtLet;

class TypeArray;
class TypePath;
class TypeReference;
class Type;
class TypeUnit;

class ASTNode;

class ASTRootNode;

class ASTVisitor{
public:
    ASTVisitor() = default;
    virtual ~ASTVisitor() = default;

    virtual void visit(ASTNode &node) = 0;

    virtual void visit(ASTRootNode &node) = 0;

    //Expression
    virtual void visit(ExprArray &node) = 0;
    virtual void visit(ExprBlock &node) = 0;
    virtual void visit(ExprBreak &node) = 0;
    virtual void visit(ExprCall &node) = 0;
    virtual void visit(ExprContinue &node) = 0;
    virtual void visit(ExprField &node) = 0;
    virtual void visit(ExprGroup &node) = 0;
    virtual void visit(ExprIf &node) = 0;
    virtual void visit(ExprIndex &node) = 0;
    virtual void visit(ExprLiteral &node) = 0;
    virtual void visit(ExprLoop &node) = 0;
    virtual void visit(ExprMatch &node) = 0;
    virtual void visit(ExprMethodcall &node) = 0;
    virtual void visit(ExprOpbinary &node) = 0;
    virtual void visit(ExprOpunary &node) = 0;
    virtual void visit(ExprPath &node) = 0;
    virtual void visit(ExprReturn &node) = 0;
    virtual void visit(ExprUnderscore &node) = 0;
    
    //Item 
    virtual void visit(ItemConstDecl &node) = 0;
    virtual void visit(ItemEnumDecl &node) = 0;
    virtual void visit(ItemFnDecl &node) = 0;
    virtual void visit(ItemImplDecl &node) = 0;
    virtual void visit(ItemStructDecl &node) = 0;
    virtual void visit(ItemTraitDecl &node) = 0;

    //Pattern
    virtual void visit(PatternIdentifier &node) = 0;
    virtual void visit(PatternLiteral &node) = 0;
    virtual void visit(PatternPath &node) = 0;
    virtual void visit(PatternReference &node) = 0;
    virtual void visit(PatternWildCard &node) = 0;
    virtual void visit(PatternTupleStruct &node) = 0;

    //Statement
    virtual void visit(StmtEmpty &node) = 0;
    virtual void visit(StmtExpr &node) = 0;
    virtual void visit(StmtItem &node) = 0;
    virtual void visit(StmtLet &node) = 0;

    //Type
    virtual void visit(Type &node) = 0;
    virtual void visit(TypeArray &node) = 0;
    virtual void visit(TypePath &node) = 0;
    virtual void visit(TypeReference &node) = 0;
    virtual void visit(TypeUnit &node) = 0;
};
}