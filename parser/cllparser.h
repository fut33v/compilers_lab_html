#ifndef CLLPARSER_H
#define CLLPARSER_H

#include <stack>
#include <fstream>
#include <iostream>
#include <cstring>
#include "scanner/ctoken.h"
#include "scanner/ctokensflow.h"
#include "parser.h"

namespace parser {
    typedef std::vector<cProduction> productions_list_t;
    class cLLParser{
    public:
        cLLParser(scanner::cTokensFlow* tokensFlow, std::string tableFname);
        void initParser();
        void startParsing();
        void showTable();
        void showProductions();
    private:
        scanner::cTokensFlow* tokensFlow;
        std::stack<int> stack;
        table_of_parsing_t parsingTable;
        productions_list_t productionsList;
        int numOfNonTerminals;
        std::string tableFname;
        void fillTable();
        void fillProductions();
        int tokenToColumn(scanner::cToken* token);
        int tokenToStackSymb(scanner::cToken* token);
        enum {
            BUF_SIZE = 256,
            NUM_OF_PRODUCTIONS = 33,
            MAGIC_NUMBER = 8,
            tEmpty = 2
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
            html = 1,
            head,
            title,
            meta,
            base,
            link,
            basefont,
            body,
            img,
            br,
            p,
            h1,
            h2,
            h3
        };
    };
}

#endif // CLLPARSER_H
