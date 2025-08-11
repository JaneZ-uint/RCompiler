#pragma once
#include "../token/token.h"
#include <string>
#include <unordered_map>
#include <vector>
#include <iostream>

namespace JaneZ {
static std::unordered_map<std::string, tokenType> keywordTotokentype = {
    {"as", kAS},
    {"break", kBREAK},
    {"const", kCONST},
    {"continue", kCONTINUE},
    {"create", kCREATE},
    {"else", kELSE},
    {"enum", kENUM},
    //{"extern",kEXTERN},
    {"false", kFALSE},
    {"fn", kFN},
    {"for", kFOR},
    {"if", kIF},
    {"impl", kIMPL},
    {"in", kIN},
    {"let", kLET},
    {"loop", kLOOP},
    {"match", kMATCH},
    {"mod", kMOD},
    {"move", kMOVE},
    {"mut", kMUT},
    //{"pub",kPUB},
    {"ref", kREF},
    {"return", kRETURN},
    {"self", kSELF},
    {"Self", kSELF_TYPE},
    {"static", kSTATIC},
    {"struct", kSTRUCT},
    {"super", kSUPER},
    {"trait", kTRAIT},
    {"true", kTRUE},
    {"type", kTYPE},
    {"unsafe", kUNSAFE},
    {"use", kUSE},
    {"where", kWHERE},
    {"while", kWHILE},
    //{"async",kASYNC},
    //{"await",kAWAIT},
    {"dyn", kDYN},
};

static std::unordered_map<std::string, tokenType> operatorTotokenType = {
    {"+", kPLUS},
    {"-", kMINUS},
    {"*", kSTAR},
    {"/", kSLASH},
    {"%", kPERCENT},
    {"^", kCARET},
    {"!", kNOT},
    {"&", kAND},
    {"|", kOR},
    {"&&", kANDAND},
    {"||", kOROR},
    {"<<", kSHL},
    {">>", kSHR},
    {"+=", kPLUSEQ},
    {"-=", kMINUSEQ},
    {"*=", kSTAREQ},
    {"/=", kSLASHEQ},
    {"%=", kPERCENTEQ},
    {"^=", kCARETEQ},
    {"&=", kANDEQ},
    {"|=", kOREQ},
    {"<<=", kSHLEQ},
    {">>=", kSHREQ},
    {"=", kEQ},
    {"==", kEQEQ},
    {"!=", kNE},
    {">", kGT},
    {"<", kLT},
    {">=", kGE},
    {"<=", kLE},
    {"::", kPATHSEP},
    {"->", kRARROW},
    {"=>", kFATARROW},
    {"?", kQUESTION},
};

static std::unordered_map<std::string, tokenType> punctuationTotokenType = {
    {",", kCOMMA},
    {";", kSEMI},
    {":", kCOLON},
    {".", kDOT},
    {"(", kL_PAREN},
    {")", kR_PAREN},
    {"[", kL_BRACKET},
    {"]", kR_BRACKET},
    {"{", kL_BRACE},
    {"}", kR_BRACE},
};

class Lexer{
private:
    std::string sourceCode;

    std::vector<Token> result;

    std::vector<Token> raw_string;

    void process(){
        bool isDouble = false;
        bool isSingle = false;
        Token tmp;
        tmp.value = "";
        tmp.type = kUNKNOWN;
        std::string test = "";
        for(int i = 0;i < sourceCode.size();i ++){
            char current = sourceCode[i];
            test += current;
            char nextChar;
            char nextnextChar;
            if(i == sourceCode.size() - 1){
                nextChar = '\0';
            }else{
                nextChar = sourceCode[i + 1];
            }
            if(i + 2 < sourceCode.size()){
                nextnextChar = sourceCode[i + 2];
            }else{
                nextnextChar = '\0';
            }
            if(current == ' '){
                continue;
            }
            if(isDouble){
                tmp.value += current;
                if(current == '"'){
                    char string_type = tmp.value[0];
                    char second_string_type;
                    if(tmp.value.size() > 1){
                        second_string_type = tmp.value[1];
                    }else{
                        second_string_type = '\0';
                    }
                    if(string_type == 'c'){
                        if(second_string_type == 'r'){
                            tmp.type = kRAW_CSTRING_LITERAL;
                            raw_string.push_back(tmp);
                        }else{
                            tmp.type = kCSTRING_LITERAL;
                        }
                    }else if(string_type == 'r'){
                        tmp.type = kRAW_STRING_LITERAL;
                        raw_string.push_back(tmp);
                    }else{
                        tmp.type = kSTRING_LITERAL;
                    }
                    result.push_back(tmp);
                    tmp.value = "";
                    tmp.type = kUNKNOWN;
                    isDouble = false;
                }
            }else if(isSingle){
                tmp.value += current;
                if(current == '\''){
                    tmp.type = kCHAR_LITERAL;
                    result.push_back(tmp);
                    tmp.value = "";
                    tmp.type = kUNKNOWN;
                }
            }else if(current == '"'){
                tmp.value += current;
                isDouble = true;
            }else if(current == '\''){
                tmp.value += current;
                isSingle = true;
            }
        }
    }

    void checkKeyword(){
        for(auto token: result){
            if(token.type == kIDENTIFIER){
                if(keywordTotokentype.find(token.value) != keywordTotokentype.end()){
                    token.type = keywordTotokentype.find(token.value)->second;
                }
            }
        }
    }

    void checkRAWSTRING(){   // independently deal with RAW_STRING RAW_CSTRING

    }



public:
    Lexer(const std::string source_code):sourceCode(source_code){}

    ~Lexer(){
        sourceCode = "";
    }

    std::vector<Token> work(){
        process();
        return result;
    }

    // for debug
    void print(){
        for(auto token: result){
            std::cout << token.value <<  ' ';
            printTokenType(token.type);
            std::cout << '\n';
        }
    }
};

}