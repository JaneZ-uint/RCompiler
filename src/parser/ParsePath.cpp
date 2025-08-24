#include "parser.h"
#include <memory>
#include <stdexcept>
#include <vector>

namespace JaneZ {
std::unique_ptr<Path> Parser::parse_path() {
    PathIdentSegment current;
    if(currentPos >= tokens.size()){
        throw std::runtime_error("End of Program.");
    }
    PathIdentSegment tmp;
    if(tokens[currentPos].type == kIDENTIFIER){
        tmp.type = IDENTIFIER;
    }else if(tokens[currentPos].type == kSELF_TYPE){
        tmp.type = SELF_TYPE;
    }else if(tokens[currentPos].type == kSELF){
        tmp.type = SELF;
    }else{
        throw std::runtime_error("Wrong type when parsing path.");
    }
    tmp.identifier = tokens[currentPos].value;
    currentPos ++;
    return std::make_unique<Path>(std::move(current));
}

}