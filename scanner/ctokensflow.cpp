#include "ctokensflow.h"

namespace scanner {
    cTokensFlow::cTokensFlow(){
        numOfTokens = 0;
        currentToken = 0;
        while(!FlowOfTokens.empty()){
            FlowOfTokens.pop_back();
        }
    }

    void cTokensFlow::addToken(cToken token){
        FlowOfTokens.push_back(token);
        numOfTokens++;
    }

    cToken cTokensFlow::getToken(){
        currentToken++;
        return FlowOfTokens[currentToken];
    }

    cToken cTokensFlow::showToken(){
        return FlowOfTokens[currentToken];
    }

    bool cTokensFlow::isEnd(){
        if (currentToken >= numOfTokens){
            return true;
        } else {
            return false;
        }
    }

}
