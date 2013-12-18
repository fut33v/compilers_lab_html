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
        std::cout<<token.getStringNum()<<" "<<token.getClassNum()<<" ";
        if (token.hasSubClass()){
            std::cout<<token.getSubClassNum()<<" ";
        }
        std::cout<<token.getValue()<<std::endl;
        tokensFlow.getToken();
    }
    tokensFlow.toStart();*/
    parser::cLLParser parser(&tokensFlow);
    parser.initParser();
    //parser.showTable();
    //parser.showProductions();
    //std::cout<<"Parsing..."<<std::endl;
    parser.startParsing();
    return 0;
}
