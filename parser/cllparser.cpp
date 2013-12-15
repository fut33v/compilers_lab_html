#include "cllparser.h"

namespace parser{
    cLLParser::cLLParser(cTokensFlow* tokensFlow, std::string tableFname){
        this->tokensFlow = tokensFlow;
        numOfProductions = 0;
        std::ifstream file (tableFname.c_str(), std::ifstream::in);
        if (!file){
            std::cout<<"Error with opening file: "<<tableFname<<std::endl;
            exit(-1);
        }
        std::vector<int> lineVector;
        char string[BUF_SIZE];
        std::string String;
        while (file.getline(string, BUF_SIZE)){
            String = string;
            String.append(" ");
            memset(string, 0, BUF_SIZE);
            for (auto it : String){
                int n;
                if ((it) == ' ' || it =='\t'){
                    n = atoi(string);
                    lineVector.push_back(n);
                    memset(string, 0, BUF_SIZE);
                } else {
                    strncat(string, &it, 1);
                }
            }
            parsingTable.push_back(lineVector);
            lineVector.clear();
            numOfProductions++;
        }
    }

    void cLLParser::initParser(){
        while(!stack.empty()){
            stack.pop();
        }
        stack.push(BottomMarker);
        stack.push(HTML);
    }

    void cLLParser::showTable(){
        std::cout<<"Parsing Table"<<std::endl;
        std::cout<<"Number of nonterminals: "<<numOfProductions<<std::endl;
        for (auto it : parsingTable){
            for (auto it2 : it){
                std::cout<<it2<<" ";
            }
            std::cout<<std::endl;
        }

    }
}
