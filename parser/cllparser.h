#ifndef CLLPARSER_H
#define CLLPARSER_H

#include <stack>
#include <fstream>
#include <iostream>
//#include <cstring>
//#include <cstdlib>
#include "unistd.h"
#include "scanner/ctoken.h"
#include "scanner/ctokensflow.h"
#include "parser.h"

namespace parser {
    typedef std::vector<cProduction> productions_list_t;
    typedef std::vector<std::vector<int>> table_of_parsing_t;

    class cLLParser{
    public:
        cLLParser(scanner::cTokensFlow* tokensFlow);
        void initParser();
        void startParsing();
    private:
        scanner::cTokensFlow* tokensFlow;
        std::stack<int> stack;
        table_of_parsing_t parsingTable;
        productions_list_t productionsList;
        std::vector<std::string> stackSymbolsString;

        void fillTable();
        void fillProductions();
        void fillStackSymbolsString();
        int tokenToColumn(scanner::cToken* token);
        int tokenToStackSymb(scanner::cToken* token);

        enum tableColumn{
            EMPTY = 2
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
