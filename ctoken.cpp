#include "ctoken.h"

namespace parser {
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
    }

    cToken::cToken(int stringNum, int classNum, std::string value){
        this->stringNum = stringNum;
        this->classNum = classNum;
        this->value = value;
        this->subClassExist = false;
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
