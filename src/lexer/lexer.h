#pragma once
#include "../token/token.h"
#include <cctype>
#include <endian.h>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <regex>
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
    {"_", kUNDERSCORE},
};

class Lexer{
private:
    std::string sourceCode;

    std::vector<Token> result;

    //std::vector<Token> unraw_string;

    void process(){
        bool isDouble = false;
        bool isSingle = false;
        Token tmp;
        tmp.value = "";
        tmp.type = kUNKNOWN;
        //std::string test = "";
        for(int i = 0;i < sourceCode.size();i ++){
            char current = sourceCode[i];
            //test += current;
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
            /*if(current == ' '){
                continue;
            }*/
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
                            //raw_string.push_back(tmp);
                        }else{
                            tmp.type = kCSTRING_LITERAL;
                            //unraw_string.push_back(tmp);
                        }
                    }else if(string_type == 'r'){
                        tmp.type = kRAW_STRING_LITERAL;
                        //raw_string.push_back(tmp);
                    }else{
                        tmp.type = kSTRING_LITERAL;
                        //unraw_string.push_back(tmp);
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
            }else {
                std::string test = "";
                test += current;
                if(operatorTotokenType.find(test) != operatorTotokenType.end() && tmp.value.size() == 0){
                    tmp.value += current;
                    tokenType tp = operatorTotokenType.find(test)->second;
                    if(tp == kPLUS){
                        if(nextChar == '='){
                            tmp.value += nextChar;
                            tmp.type = kPLUSEQ;
                            i ++;
                        }else{
                            tmp.type = kPLUS;
                        }
                        result.push_back(tmp);
                        tmp.value = "";
                        tmp.type = kUNKNOWN;
                    }else if(tp == kMINUS){
                        if(nextChar == '='){
                            tmp.value += nextChar;
                            tmp.type = kMINUSEQ;
                            i ++;
                        }else if(nextChar == '>'){
                            tmp.value += nextChar;
                            tmp.type = kRARROW;
                            i ++;
                        }else{
                            tmp.type = kMINUS;
                        }
                        result.push_back(tmp);
                        tmp.value = "";
                        tmp.type = kUNKNOWN;
                    }else if(tp == kSTAR){
                        if(nextChar == '='){
                            tmp.value += nextChar;
                            tmp.type = kSTAREQ;
                            i ++;
                        }else{
                            tmp.type = kSTAR;
                        }
                        result.push_back(tmp);
                        tmp.value = "";
                        tmp.type = kUNKNOWN;
                    }else if(tp == kSLASH){
                        if(nextChar == '='){
                            tmp.value += nextChar;
                            tmp.type = kSLASHEQ;
                            i ++;
                        }else{
                            tmp.type = kSLASH;
                        }
                        result.push_back(tmp);
                        tmp.value = "";
                        tmp.type = kUNKNOWN;
                    }else if(tp == kPERCENT){
                        if(nextChar == '='){
                            tmp.value += nextChar;
                            tmp.type = kPERCENTEQ;
                            i ++;
                        }else{
                            tmp.type = kPERCENT;
                        }
                        result.push_back(tmp);
                        tmp.value = "";
                        tmp.type = kUNKNOWN;
                    }else if(tp == kCARET){
                        if(nextChar == '='){
                            tmp.value += nextChar;
                            tmp.type = kCARETEQ;
                            i ++;
                        }else{
                            tmp.type = kCARET;
                        }
                        result.push_back(tmp);
                        tmp.value = "";
                        tmp.type = kUNKNOWN;
                    }else if(tp == kNOT){
                        if(nextChar == '='){
                            tmp.value += nextChar;
                            tmp.type = kNE;
                            i ++;
                        }else{
                            tmp.type = kNOT;
                        }
                        result.push_back(tmp);
                        tmp.value = "";
                        tmp.type = kUNKNOWN;
                    }else if(tp == kAND){
                        if(nextChar == '='){
                            tmp.value += nextChar;
                            tmp.type = kANDEQ;
                            i ++;
                        }else if(nextChar == '&'){
                            tmp.value += nextChar;
                            tmp.type = kANDAND;
                            i ++;
                        }else{
                            tmp.type = kAND;
                        }
                        result.push_back(tmp);
                        tmp.value = "";
                        tmp.type = kUNKNOWN;
                    }else if(tp == kOR){
                        if(nextChar == '='){
                            tmp.value += nextChar;
                            tmp.type = kOREQ;
                            i ++;
                        }else if(nextChar == '|'){
                            tmp.value += nextChar;
                            tmp.type = kOROR;
                            i ++;
                        }else{
                            tmp.type = kOR;
                        }
                        result.push_back(tmp);
                        tmp.value = "";
                        tmp.type = kUNKNOWN;
                    }else if(tp == kEQ){
                        if(nextChar == '='){
                            tmp.value += nextChar;
                            tmp.type = kEQEQ;
                            i ++;
                        }else if(nextChar == '>'){
                            tmp.value += nextChar;
                            tmp.type = kFATARROW;
                            i ++;
                        }else {
                            tmp.type = kEQ;
                        }
                        result.push_back(tmp);
                        tmp.value = "";
                        tmp.type = kUNKNOWN;
                    }else if(tp == kGT){
                        if(nextChar == '>'){
                            tmp.value += nextChar;
                            if(nextnextChar == '='){
                                tmp.value += nextnextChar;
                                tmp.type = kSHREQ;
                                i ++;
                            }else{
                                tmp.type = kSHR;
                            }
                            i ++;
                        }else if(nextChar == '='){
                            tmp.value += nextChar;
                            tmp.type = kGE;
                            i ++;
                        }else{
                            tmp.type = kGT;
                        }
                        result.push_back(tmp);
                        tmp.value = "";
                        tmp.type = kUNKNOWN;
                    }else if(tp == kLT){
                        if(nextChar == '<'){
                            tmp.value += nextChar;
                            if(nextnextChar == '='){
                                tmp.value += nextnextChar;
                                tmp.type = kSHLEQ;
                                i ++;
                            }else{
                                tmp.type = kSHL;
                            }
                            i ++;
                        }else if(nextChar == '='){
                            tmp.value += nextChar;
                            tmp.type = kLE;
                            i ++;
                        }else{
                            tmp.type = kLT;
                        }
                        result.push_back(tmp);
                        tmp.value = "";
                        tmp.type = kUNKNOWN;
                    }else if(tp == kQUESTION){
                        tmp.type = kQUESTION;
                        result.push_back(tmp);
                        tmp.value = "";
                        tmp.type = kUNKNOWN;
                    } 
                }else if(punctuationTotokenType.find(test) != punctuationTotokenType.end() && tmp.value.size() == 0){
                    tmp.value += current;
                    tokenType tp = punctuationTotokenType.find(test)->second;
                    if(tp == kSEMI){
                        if(nextChar == ':'){
                            tmp.value += nextChar;
                            tmp.type = kPATHSEP;
                            i ++;
                        }else{
                            tmp.type = kSEMI;
                        }
                        result.push_back(tmp);
                        tmp.value = "";
                        tmp.type = kUNKNOWN;
                    }else {
                        tmp.type = tp;
                        result.push_back(tmp);
                        tmp.value = "";
                        tmp.type = kUNKNOWN;
                    }
                }else{
                    if(!checkIdentifier(current) && tmp.value.size() > 0){
                        if(checkNumber(tmp.value[0])){
                            if(checkIntegerliteral(tmp.value)){
                                tmp.type = kINTEGER_LITERAL;
                            }else{
                                throw std::runtime_error("Compile error: Invalid Integer Literal.");
                            }
                        }else {
                            tmp.type = kIDENTIFIER;
                        }
                        result.push_back(tmp);
                        tmp.value = "";
                        tmp.type = kUNKNOWN;
                        i --;
                    }else if(checkIdentifier(current)){
                        tmp.value += current;
                    }
                }
            }
        }
    }

    void checkKeyword(){
        for(auto &token: result){
            if(token.type == kIDENTIFIER){
                if(keywordTotokentype.find(token.value) != keywordTotokentype.end()){
                    token.type = keywordTotokentype.find(token.value)->second;
                }
            }
        }
    }

    void checkRAWSTRING(){   // independently deal with RAW_STRING RAW_CSTRING
        for(auto& token: result){
            if(token.type == kSTRING_LITERAL || token.type == kCSTRING_LITERAL){
                std::string current = token.value;
                std::string new_current = "";
                bool trans = false;
                if(token.type == kRAW_STRING_LITERAL){
                    for(int i = 0;i < current.size();i ++){
                        if(trans){
                            if(current[i] == 'n'){
                                new_current += '\n';
                            }else if(current[i] == 'r'){
                                new_current += '\r';
                            }else if(current[i] == 't'){
                                new_current += '\t';
                            }else{
                                new_current += current[i];
                            }
                            trans = false;
                            continue;
                        }
                        if(current[i] == '\\'){
                            trans = true;
                            continue;
                        }
                        new_current += current[i];
                    }
                    token.value = new_current;
                }else if(token.type == kRAW_CSTRING_LITERAL){
                    for(int i = 0;i < current.size();i ++){
                        if(trans){
                            if(current[i] == 'n'){
                                new_current += '\n';
                            }else if(current[i] == 'r'){
                                new_current += '\r';
                            }else if(current[i] == 't'){
                                new_current += '\t';
                            }else{
                                new_current += current[i];
                            }
                            trans = false;
                            continue;
                        }
                        if(current[i] == '\\'){
                            trans = true;
                            continue;
                        }
                        if(i == current.size() - 1){
                            new_current += '\0';
                        }
                        new_current += current[i];
                    }
                    token.value = new_current;
                }else{
                    continue;
                }
            }
        }
    }

    bool checkIntegerliteral(std::string current){
        std::regex integerRegex(R"((\b(?:0[xX][0-9a-fA-F_]+|0[oO][0-7_]+|0[bB][01_]+|\d+)(?:(i32)?|(isize)?|(u32)?|(usize)?)\b))");
        if(!std::regex_match(current,integerRegex)){
            return false;  
        }
        return true;
    }

    bool checkIdentifier(char current){
        if(std::isalnum(current) || current == '_'){
            return true;
        }
        return false;
    }

    bool checkNumber(char current){
        if('0' <= current && current <= '9'){
            return true;
        }
        return false;
    }

public:
    Lexer(const std::string source_code):sourceCode(source_code){}

    ~Lexer(){
        sourceCode = "";
    }

    std::vector<Token> work(){
        process();
        checkKeyword();
        checkRAWSTRING();
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