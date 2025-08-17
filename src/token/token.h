# pragma once

#include <string>
#include <iostream>
namespace JaneZ {
enum tokenType{
    // identifier
    kIDENTIFIER,

    // literal
    kINTEGER_LITERAL,
    kCHAR_LITERAL,
    kSTRING_LITERAL,
    kRAW_STRING_LITERAL,
    kCSTRING_LITERAL,
    kRAW_CSTRING_LITERAL,

    //keyword
    kAS,
    kBREAK,
    kCONST,
    kCONTINUE,
    kCREATE,
    kELSE,
    kENUM,
    //kEXTERN,
    kFALSE,
    kFN,
    kFOR,
    kIF,
    kIMPL,
    kIN,
    kLET,
    kLOOP,
    kMATCH,
    kMOD,
    kMOVE,
    kMUT,
    //kPUB,
    kREF,
    kRETURN,
    kSELF,   // self
    kSELF_TYPE, // Self
    kSTATIC,
    kSTRUCT,
    kSUPER,
    kTRAIT,
    kTRUE,
    kTYPE,
    kUNSAFE,
    kUSE,
    kWHERE,
    kWHILE,
    //kASYNC,
    //kAWAIT,
    kDYN,

    /*kABSTRACT,
    kBECOME,
    kBOX,
    kDO,
    kFINAL,
    kMACRO,
    kOVERRIDE,
    kPRIV,
    kTYPEOF,
    kUNSIZED,
    kVIRTUAL,
    kYIELD,
    kTRY,
    kGEN,*/

    //operators
    kPLUS, // +
    kMINUS, // -
    kSTAR, // *
    kSLASH, // /
    kPERCENT, // %
    kCARET, // ^
    kNOT, // !
    kAND, // &
    kOR, // |
    kANDAND, // &&
    kOROR, // ||
    kSHL, // <<
    kSHR, // >>
    kPLUSEQ, // +=
    kMINUSEQ, // -=
    kSTAREQ, // *=
    kSLASHEQ, // /=
    kPERCENTEQ, // %=
    kCARETEQ, // ^=
    kANDEQ, // &=
    kOREQ, // |=
    kSHLEQ, // <<=
    kSHREQ, // >>=
    kEQ, // =
    kEQEQ, // ==
    kNE, // !=
    kGT, // >
    kLT, // <
    kGE, // >=
    kLE, // <=
    kPATHSEP, // ::
    kRARROW, // ->
    kFATARROW, // =>
    kQUESTION, // ?

    // punctuation
    kCOMMA, // ,
    kSEMI, // ;
    kCOLON, // :
    kDOT, // .
    kL_PAREN, // (
    kR_PAREN, // )
    kL_BRACKET, // [
    kR_BRACKET, // ]
    kL_BRACE, // {
    kR_BRACE, // }

    kEOF, // END OF FILE
    kUNKNOWN // ERROR
};

static void printTokenType(tokenType tmp){
    if(tmp == kIDENTIFIER){
        std::cout << "kIDENTIFIER";
    }else if (tmp == kINTEGER_LITERAL) {
        std::cout << "kINTEGER_LITERAL";
    }else if (tmp == kCHAR_LITERAL) {
        std::cout << "kCHAR_LITERAL";
    }else if (tmp == kSTRING_LITERAL) {
        std::cout << "kSTRING_LITERAL";
    }else if (tmp == kRAW_STRING_LITERAL) {
        std::cout << "kRAW_STRING_LITERAL";
    }else if (tmp == kCSTRING_LITERAL) {
        std::cout << "kCSTRING_LITERAL";
    }else if (tmp == kRAW_CSTRING_LITERAL) {
        std::cout << "kRAW_CSTRING_LITERAL";
    }else if (tmp == kAS) {
        std::cout << "kAS";
    }else if (tmp == kBREAK) {
        std::cout << "kBREAK";
    }else if (tmp == kCONST) {
        std::cout << "kCONST";
    }else if(tmp == kCONTINUE){
        std::cout << "kCONTINUE";
    }else if (tmp == kCREATE) {
        std::cout << "kCREATE";
    }else if (tmp == kELSE) {
        std::cout << "kELSE";
    }else if (tmp == kENUM) {
        std::cout << "kENUM";
    }else if (tmp == kFALSE) {
        std::cout << "kFALSE";
    }else if (tmp == kFN) {
        std::cout << "kFN";
    }else if (tmp == kFOR) {
        std::cout << "kFOR";
    }else if (tmp == kIF) {
        std::cout << "kIF";
    }else if (tmp == kIMPL) {
        std::cout << "kIMPL";
    }else if (tmp == kIN) {
        std::cout << "kIN";
    }else if (tmp == kLET) {
        std::cout << "kLET";
    }else if (tmp == kLOOP) {
        std::cout << "kLOOP";
    }else if (tmp == kMATCH) {
        std::cout << "kMATCH";
    }else if (tmp == kMOD) {
        std::cout << "kMOD";
    }else if (tmp == kMOVE) {
        std::cout << "kMOVE";
    }else if (tmp == kMUT) {
        std::cout << "kMUT";
    }else if (tmp == kREF) {
        std::cout << "kREF";
    }else if (tmp == kRETURN) {
        std::cout << "kRETURN";
    }else if (tmp == kSELF) {
        std::cout << "kSELF";
    }else if (tmp == kSELF_TYPE) {
        std::cout << "kSELF_TYPE";
    }else if (tmp == kSTATIC) {
        std::cout << "kSTATIC";
    }else if (tmp == kSTRUCT) {
        std::cout << "kSTRUCT";
    }else if (tmp == kSUPER) {
        std::cout << "kSUPER";
    }else if (tmp == kTRAIT) {
        std::cout << "kTRAIT";
    }else if (tmp == kTRUE) {
        std::cout << "kTRUE";
    }else if (tmp == kTYPE) {
        std::cout << "kTYPE";
    }else if (tmp == kUNSAFE) {
        std::cout << "kUNSAFE";
    }else if (tmp == kUSE) {
        std::cout << "kUSE";
    }else if (tmp == kWHERE) {
        std::cout << "kWHERE";
    }else if (tmp == kWHILE) {
        std::cout << "kWHILE";
    }else if (tmp == kDYN) {
        std::cout << "kDYN";
    }else if (tmp == kPLUS) {
        std::cout << "kPLUS";
    }else if (tmp == kMINUS) {
        std::cout << "kMINUS";
    }else if (tmp == kSTAR) {
        std::cout << "kSTAR";
    }else if (tmp == kSLASH) {
        std::cout << "kSLASH";
    }else if (tmp == kPERCENT) {
        std::cout << "kPERCENT";
    }else if (tmp == kCARET) {
        std::cout << "kCARET";
    }else if (tmp == kNOT) {
        std::cout << "kNOT";
    }else if (tmp == kAND) {
        std::cout << "kAND";
    }else if (tmp == kOR) {
        std::cout << "kOR";
    }else if (tmp == kANDAND) {
        std::cout << "kANDAND";
    }else if (tmp == kOROR) {
        std::cout << "kOROR";
    }else if (tmp == kSHL) {
        std::cout << "kSHL";
    }else if (tmp == kSHR) {
        std::cout << "kSHR";
    }else if (tmp == kPLUSEQ) {
        std::cout << "kPLUSEQ";
    }else if (tmp == kMINUSEQ) {
        std::cout << "kMINUSEQ";
    }else if (tmp == kSTAREQ) {
        std::cout << "kSTAREQ";
    }else if (tmp == kSLASHEQ) {
        std::cout << "kSLASHEQ";
    }else if (tmp == kPERCENTEQ) {
        std::cout << "kPERCENTEQ";
    }else if (tmp == kCARETEQ) {
        std::cout << "kCARETEQ";
    }else if (tmp == kANDEQ) {
        std::cout << "kANDEQ";
    }else if (tmp == kOREQ) {
        std::cout << "kOREQ";
    }else if (tmp == kSHLEQ) {
        std::cout << "kSHLEQ";
    }else if(tmp == kSHREQ){
        std::cout << "kSHREQ";
    }else if(tmp == kEQ){
        std::cout << "kEQ";
    }else if(tmp == kEQEQ){
        std::cout << "kEQEQ";
    }else if(tmp == kNE){
        std::cout << "kNE";
    }else if(tmp == kGT){
        std::cout << "kGT";
    }else if(tmp == kLT){
        std::cout << "kLT";
    }else if(tmp == kGE){
        std::cout << "kGE";
    }else if(tmp == kLE){
        std::cout << "kLE";
    }else if(tmp == kPATHSEP){
        std::cout << "kPATHSEP";
    }else if(tmp == kRARROW){
        std::cout << "kRARROW";
    }else if(tmp == kFATARROW){
        std::cout << "kFATARROW";
    }else if(tmp == kQUESTION){
        std::cout << "kQUESTION";
    }else if(tmp == kCOMMA){
        std::cout << "kCOMMA";
    }else if(tmp == kSEMI){
        std::cout << "kSEMI";
    }else if(tmp == kCOLON){
        std::cout << "kCOLON";
    }else if(tmp == kDOT){
        std::cout << "kDOT";
    }else if(tmp == kL_PAREN){
        std::cout << "kL_PAREN";
    }else if(tmp == kR_PAREN){
        std::cout << "kR_PAREN";
    }else if(tmp == kL_BRACKET){
        std::cout << "kL_BRACKET";
    }else if(tmp == kR_BRACKET){
        std::cout << "kR_BRACKET";
    }else if(tmp == kL_BRACE){
        std::cout << "kL_BRACE";
    }else if(tmp == kR_BRACE){
        std::cout << "kR_BRACE";
    }else if(tmp == kEOF){
        std::cout << "kEOF";
    }else if(tmp == kUNKNOWN){
        std::cout << "kUNKNOWN";
    }
}

struct Token{
    tokenType type;
    std::string value;
};
}