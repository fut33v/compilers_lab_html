#include <iostream>
#include "ctokensflow.h"
#include "ctoken.h"
#include "parser.h"

int main(){
    parser::cTokensFlow tknFlow("tokens");
    while (!tknFlow.isEnd()){
        parser::cToken token;
        token = tknFlow.getToken();
        std::cout<<token.getStringNum()<<" "<<token.getClassNum()<<" ";
        if (token.hasSubClass()){
            std::cout<<token.getSubClassNum()<<" ";
        }
        std::cout<<token.getValue()<<std::endl;
    }
    return 0;
}
