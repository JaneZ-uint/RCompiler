# pragma once

#include <string>
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
    kSELF,
    kSELF_TYPE,
    kSTATIC,
    kSTRUCT,
    KSUPER,
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

struct Token{
    tokenType type;
    std::string value;
};
}