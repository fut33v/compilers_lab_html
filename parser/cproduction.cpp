#include "cproduction.h"
namespace parser{
    cProduction::cProduction(int productionNumber){
        this->productionNumber = productionNumber;
    }

    void cProduction::setNumber(int number){
        this->productionNumber = number;
    }


    int cProduction::getNumber(){
        return this->productionNumber;
    }

    /*void cProduction::clearProduction(){
        for (auto it : this){
            it->pop_back();
        }
    }*/
}
