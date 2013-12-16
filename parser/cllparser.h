#ifndef CLLPARSER_H
#define CLLPARSER_H

#include <stack>
#include <fstream>
#include <iostream>
#include <cstring>
#include "scanner/ctokensflow.h"
#include "parser.h"

namespace parser {
    class cLLParser{
    public:
        cLLParser(scanner::cTokensFlow* tokensFlow, std::string tableFname);
        void showTable();
        void initParser();
        void startParsing();
    private:
        void performProduction(int production);
        scanner::cTokensFlow* tokensFlow;
        std::stack<int> stack;
        table_of_parsing_t parsingTable;
        int numOfNonTerminals;
        enum {
            BUF_SIZE = 256
        };
        enum tableColumns {
            tSTRING, //8 CLASS_STRING
            tID, //5 CLASS_ID
            tEMPTY, //???
            tCOLOR, //7 CLASS_COLOR
            tINT, //6 CLASS_INT
            tEQUAL, //4 CLASS_EQUAL_SIGN
            tHtml, //1 1 CLASS_OPENING_TAGS
            tHead, //1 2 -/-
            tTitle, //1 3 -/-
            tMeta, //1 4 -/-
            tLink, //1 6 -/-
            tBase, //1 5 -/-
            tBasefont, //1 7 -/-
            tBody, //1 8 -/-
            tImg, //1 9 -/-
            tBr, //1 10 -/-
            tP, //1 11 -/-
            tH1, //1 12 -/-
            tH2, //1 13 -/-
            tH3 //1 14 -/-
        };
        enum nonTerminals {
            HTML,
            WebpageBody,
            Head,
            HeadItems,
            HeadItem,
            Body,
            Content,
            Parameters,
            Parameter1,
            Equal,
            Parameter,
            Tag,
            Word,
            BottomMarker
        };
        enum tokenClasses {
            CLASS_ERROR,
            CLASS_OPENING_TAGS,
            CLASS_CLOSING_TAGS,
            CLASS_CLOSING_BRACE,
            CLASS_EQUAL_SIGN,
            CLASS_ID,
            CLASS_INT,
            CLASS_COLOR,
            CLASS_STRING
        };
        enum openingTags {
            oHtml = 1,
            oHead,
            oTitle,
            oMeta,
            oBase,
            oLink,
            oBasefont,
            oBody,
            oImg,
            oBr,
            oP,
            oH1,
            oH2,
            oH3
        };
        enum closingTags {
            cHtml = 1,
            cHead,
            cTitle,
            cBody,
            cH1,
            cH2,
            cH3,
            cP
        };
    };
}

#endif // CLLPARSER_H
