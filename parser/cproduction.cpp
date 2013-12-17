#include "cproduction.h"
namespace parser{
    cProduction::cProduction(int productionNumber){
        this->productionNumber = productionNumber;
    }

    cProduction::addStackElem(cStackElement element){
        production.push_back(element);
    }

    production_t cProduction::getProduction(){
        return production;
    }

    void cProduction::setNumber(int number){
        this->productionNumber = number;
    }
}
