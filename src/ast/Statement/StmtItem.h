# pragma once

#include "statement.h"
#include <memory>
namespace JaneZ {
class Item;
class StmtItem : public Statement {
public:
    std::shared_ptr<Item> stmt_item;

    StmtItem(std::shared_ptr<Item> si): stmt_item(std::move(si)) {}

    ~StmtItem() = default;

    void accept(ASTVisitor &visitor) override {
        visitor.visit(*this);
    }
};
}