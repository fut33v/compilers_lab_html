#include "cllparser.h"

namespace parser{
    cLLParser::cLLParser(scanner::cTokensFlow* tokensFlow, std::string tableFname){
        this->tokensFlow = tokensFlow;
        numOfNonTerminals = 0;
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
            numOfNonTerminals++;
        }
    }

    void cLLParser::initParser(){
        while(!stack.empty()){
            stack.pop();
        }
        stack.push(BottomMarker);
        stack.push(HTML);
    }

    void cLLParser::startParsing(){
        while (!tokensFlow->isEnd()){
            scanner::cToken token;
            int production;
            token = tokensFlow->showToken();
            switch(token.getClassNum()){
                case CLASS_STRING: {
                    production = parsingTable[stack.top()][tSTRING];
                    break;
                }
                case CLASS_OPENING_TAGS: {
                switch(token.getSubClassNum())
                    case oHtml: {
                        production = parsingTable[stack.top()][tHtml];
                        break;
                    }
                    case oHead: {
                        production = parsingTable[stack.top()][tHead];
                        break;
                    }
                    case oTitle: {
                        production = parsingTable[stack.top()][tTitle];
                        break;
                    }
                    case oMeta: {
                        production = parsingTable[stack.top()][tMeta];
                        break;
                    }
                    case oBase: {
                        production = parsingTable[stack.top()][tBase];
                        break;
                    }
                    case oLink: {
                        production = parsingTable[stack.top()][tLink];
                        break;
                    }
                    case oBasefont: {
                        production = parsingTable[stack.top()][tBasefont];
                        break;
                    }
                    case oBody: {
                        production = parsingTable[stack.top()][tBody];
                        break;
                    }/*
                    case oHead: {
                        production = parsingTable[stack.top()][tHead];
                    }*/ // @TODO other opening tags, shiiit

                }

            }
            tokensFlow->getToken();

        }
    }

    void cLLParser::performProduction(int production){
        switch (production){
            case 1:{

            }
            case 2:{

            }
            case 3:{

            }
        }
    }

    void cLLParser::showTable(){
        std::cout<<"Parsing Table"<<std::endl;
        std::cout<<"Number of nonterminals: "<<numOfNonTerminals<<std::endl;
        for (auto it : parsingTable){
            for (auto it2 : it){
                std::cout<<it2<<" ";
            }
            std::cout<<std::endl;
        }

    }
}
