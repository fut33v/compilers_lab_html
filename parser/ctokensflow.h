#ifndef TOKENSFLOW_H
#define TOKENSFLOW_H

#include "parser.h"
#include "ctoken.h"

namespace parser {
    class cTokensFlow{
        public:
            cTokensFlow(std::string fileName);
            cToken getToken();
            cToken showToken();
            bool isEnd();
        private:
            token_flow_t FlowOfTokens;
            int currentToken;
            int numOfTokens;
        enum {
            BUF_SIZE = 256
        };

    };
}
#endif // TOKENSFLOW_H
