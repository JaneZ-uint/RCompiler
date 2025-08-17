# pragma once

#include "statement.h"
#include <memory>
namespace JaneZ {
class Item;
class StmtItem : public Statement {
private:
    std::unique_ptr<Item> stmt_item;

public:
    StmtItem(std::unique_ptr<Item> si): stmt_item(std::move(si)) {}

    ~StmtItem() = default;

    void accept(ASTVisitor &visitor) override {
        visitor.visit(*this);
    }
};
}