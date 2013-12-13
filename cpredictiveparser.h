#ifndef CPREDICTIVEPARSER_H
#define CPREDICTIVEPARSER_H

#include "ctokensflow.h"

namespace parser {
    class cPredictiveParser{
    public:
        cPredictiveParser(cTokensFlow *tokenFlow);
    private:
        cTokensFlow *tokenFlow;
    };
}

#endif // CPREDICTIVEPARSER_H
