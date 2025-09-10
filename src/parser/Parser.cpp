#include "parser.h"
#include <memory>

namespace JaneZ {
std::shared_ptr<ASTRootNode> Parser::parse() {
    std::vector<std::shared_ptr<Item>> child;
    while(true) {
        std::shared_ptr<Item> current;
        current = parse_item();
        child.push_back(std::move(current));
        if(currentPos >= tokens.size()) {
            break;
        }
    }
    return std::make_shared<ASTRootNode>(std::move(child));
}

}