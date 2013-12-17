#include "cstackelement.h"

namespace parser{
    cStackElement::cStackElement(int stackSymbol, bool isTerminal){
        this->isterminal = isTerminal;
        this->stackSymbol = stackSymbol;
    }

    bool cStackElement::isTerminal(){
        return isterminal;
    }
    int cStackElement::getSymbol(){
        return stackSymbol;
    }

    void cStackElement::setSymbol(int symbol){
        this->stackSymbol = symbol;
    }

    void cStackElement::setIsTerminal(bool is){
        this->isterminal = is;
    }
}
