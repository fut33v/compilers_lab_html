#ifndef TOKENSFLOW_H
#define TOKENSFLOW_H

#include <fstream>
#include <iostream>
#include <vector>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include "ctoken.h"

namespace scanner {
    typedef std::vector<cToken> token_flow_t;
    class cTokensFlow{
    public:
        cTokensFlow();
        void addToken(cToken token);
        cToken getToken();
        cToken showToken();
        bool isEnd();
    private:
        token_flow_t FlowOfTokens;
        int currentToken;
        int numOfTokens;
    };
}
#endif // TOKENSFLOW_H
