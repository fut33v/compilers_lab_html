#ifndef CSTACKELEMENT_H
#define CSTACKELEMENT_H

namespace parser{
    class cStackElement{
    public:
        cStackElement(int stackSymbol, bool isTerminal);
        bool isTerminal;
        int getSymbol();
        void setSymbol(int symbol);
        void setIsTerminal(bool is);
    private:
        int stackSymbol;
        bool isterminal;
    };
}

#endif // CSTACKELEMENT_H
