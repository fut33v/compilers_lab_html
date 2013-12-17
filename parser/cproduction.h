#ifndef CPRODUCTION_H
#define CPRODUCTION_H
#include "scanner/ctoken.h"
#include "parser.h"

namespace parser{
    //typedef std::vector<int> production_t;
    class cProduction : public std::vector<int>{
    public:
        cProduction(int productionNumber);
        void setNumber(int number);
        int getNumber();
    private:
        int productionNumber;
    };
}
#endif // CPRODUCTION_H
