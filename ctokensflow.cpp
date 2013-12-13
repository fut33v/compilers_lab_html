#include "ctokensflow.h"
#include <fstream>
#include <iostream>
#include <stdio.h>
#include <cstdlib>
#include <cstring>

namespace parser {
    cTokensFlow::cTokensFlow(std::string fileName){
        std::ifstream file (fileName.c_str(), std::ifstream::in);
        if (!file){
            std::cout<<"Error with opening file: "<<fileName<<std::endl;
            exit(-1);
        }
        char string[BUF_SIZE];
        numOfTokens = 0;
        while (file.getline(string, BUF_SIZE)){
            numOfTokens++;
            FlowOfTokens.push_back(string);
            memset(string, 0, BUF_SIZE);
        }
        currentToken = 0;
    }

    cToken cTokensFlow::getToken(){
        int stringN, classN, subClassN;
        char value[256];
        const char* string = FlowOfTokens[currentToken].c_str();
        sscanf(string, "%d %d ", &stringN, &classN);
        if (classN <= 3 || classN == 5){
            sscanf(string, "%d %d %d %s", &stringN, &classN, &subClassN, value);
            currentToken++;
            std::string Value = value;
            return cToken(stringN, classN, subClassN, Value);
        } else {
            sscanf(string, "%d %d %s", &stringN, &classN, value);
            currentToken++;
            std::string Value = value;
            return cToken(stringN, classN, Value);
        }
    }

    bool cTokensFlow::isEnd(){
        if (currentToken >= numOfTokens){
            return true;
        } else {
            return false;
        }
    }

}
