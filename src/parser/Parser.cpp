#include "parser.h"
#include <memory>

namespace JaneZ {
std::unique_ptr<ASTRootNode> Parser::parse() {
    std::vector<std::unique_ptr<Item>> child;
    for(int i = 0;i < tokens.size();i ++) {
        std::unique_ptr<Item> current;
        current = parse_item();
        child.push_back(std::move(current));
    }
    return std::make_unique<ASTRootNode>(std::move(child));
}

}