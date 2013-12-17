#include <iostream>
#include "scanner/ctokensflow.h"
#include "scanner/ctoken.h"
#include "scanner/ccode.h"
#include "scanner/cscanner.h"
#include "cllparser.h"
#include "parser.h"

int main(){
    scanner::cTokensFlow tokensFlow;
    scanner::cScanner scanner("test.html", &tokensFlow);
    scanner.startScanning();
    /*while (!tokensFlow.isEnd()){
        scanner::cToken token;
        token = tokensFlow.showToken();
        tokensFlow.getToken();
        std::cout<<token.getStringNum()<<" "<<token.getClassNum()<<" ";
        if (token.hasSubClass()){
            std::cout<<token.getSubClassNum()<<" ";
        }
        std::cout<<token.getValue()<<std::endl;
    }*/
    parser::cLLParser parser (&tokensFlow, "table");
    //parser.showTable();
    parser.initParser();
    //parser.showProductions();
    std::cout<<"Parsing..."<<std::endl;
    parser.startParsing();
    return 0;
}
