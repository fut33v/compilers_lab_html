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
    };
}

#endif // CLLPARSER_H
