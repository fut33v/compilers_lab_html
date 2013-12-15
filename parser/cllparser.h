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
    private:
        scanner::cTokensFlow* tokensFlow;
        std::stack<int> stack;
        table_of_parsing_t parsingTable;
        int numOfProductions;
        enum {
            BUF_SIZE = 256
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
    };
}

#endif // CLLPARSER_H
