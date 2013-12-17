#ifndef CPRODUCTION_H
#define CPRODUCTION_H
#include "scanner/ctoken.h"
#include "cstackelement.h"
#include "parser.h"

namespace parser{
    typedef std::vector<cStackElement> production_t;
    class cProduction
    {
    public:
        cProduction(int productionNumber);
        void addStackElem(cStackElement element);
        parser::production_t getProduction();
        void setNumber(int number);
    private:
        int productionNumber;
        production_t production;
    };
}
#endif // CPRODUCTION_H
