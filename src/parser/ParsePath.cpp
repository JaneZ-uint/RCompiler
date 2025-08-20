#include "parser.h"
#include <memory>
#include <stdexcept>
#include <vector>

namespace JaneZ {
std::unique_ptr<Path> Parser::parse_path() {
    std::vector<PathIdentSegment> current;
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
    if(currentPos >= tokens.size()){
        throw std::runtime_error("End of Program.");
    }
    current.push_back(tmp);
    while(tokens[currentPos].type == kPATHSEP){
        currentPos ++;
        if(currentPos >= tokens.size()) {
            throw std::runtime_error("End of Program.");
        }
        PathIdentSegment tp;
        if(tokens[currentPos].type == kIDENTIFIER){
            tp.type = IDENTIFIER;
        }else if(tokens[currentPos].type == kSELF_TYPE){
            tp.type = SELF_TYPE;
        }else if(tokens[currentPos].type == kSELF){
            tp.type = SELF;
        }else{
            throw std::runtime_error("Wrong type when parsing path.");
        }
        tp.identifier = tokens[currentPos].value;
        currentPos ++;
        if(currentPos >= tokens.size()){
            throw std::runtime_error("End of Program.");
        }
        current.push_back(tp);
    }
    return std::make_unique<Path>(std::move(current));
}

}