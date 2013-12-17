#include "ctoken.h"

namespace scanner {
    cToken::cToken(){
        this->stringNum = 0;
        this->classNum = 0;
        this->subClassExist = false;
    }

    cToken::cToken(int stringNum, int classNum, int subClassNum, std::string value){
        this->stringNum = stringNum;
        this->classNum = classNum;
        this->subClassNum = subClassNum;
        this->value = value;
        this->subClassExist = true;
        //this->stackSymbol = stackSymbol;
    }

    cToken::cToken(int stringNum, int classNum, std::string value){
        this->stringNum = stringNum;
        this->classNum = classNum;
        this->value = value;
        this->subClassExist = false;
        //this->stackSymbol = stackSymbol;
    }

    int cToken::getStringNum(){
        return stringNum;
    }

    int cToken::getClassNum(){
        return classNum;
    }

    int cToken::getSubClassNum(){
        return subClassNum;
    }

    std::string cToken::getValue(){
        return value;
    }

    bool cToken::hasSubClass(){
        return subClassExist;
    }
}
