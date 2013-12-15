#include <iostream>
#include "ctokensflow.h"
#include "ctoken.h"
#include "parser.h"
#include "cllparser.h"
#include "scanner/ccode.h"

int main(){
    /*parser::cTokensFlow tokensFlow("tokens");
    while (!tknFlow.isEnd()){
        parser::cToken token;
        token = tknFlow.showToken();
        tknFlow.getToken();
        std::cout<<token.getStringNum()<<" "<<token.getClassNum()<<" ";
        if (token.hasSubClass()){
            std::cout<<token.getSubClassNum()<<" ";
        }
        std::cout<<token.getValue()<<std::endl;
    }*/

    parser::cTokensFlow tokensFlow("tokens");
    parser::cLLParser parser (&tokensFlow, "table");
    parser.showTable();

    return 0;
}
