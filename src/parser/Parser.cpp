#include "parser.h"
#include <memory>

namespace JaneZ {
std::unique_ptr<ASTRootNode> Parser::parse() {
    std::vector<std::unique_ptr<Item>> child;
    while(true) {
        std::unique_ptr<Item> current;
        current = parse_item();
        child.push_back(std::move(current));
        if(currentPos >= tokens.size()) {
            break;
        }
    }
    return std::make_unique<ASTRootNode>(std::move(child));
}

}