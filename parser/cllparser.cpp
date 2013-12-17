#include "cllparser.h"

namespace parser{
    cLLParser::cLLParser(scanner::cTokensFlow* tokensFlow, std::string tableFname){
        this->tokensFlow = tokensFlow;
        this->tableFname = tableFname;
        fillTable();
    }

    void cLLParser::initParser(){
        while(!stack.empty()){
            stack.pop();
        }
        stack.push(cStackElement(BottomMarker, false));
        stack.push(cStackElement(HTML, false));
    }

    void cLLParser::startParsing(){
        while (!tokensFlow->isEnd()){
            scanner::cToken token;
            token = tokensFlow->showToken();
            cStackElement top = stack.top();
            if (top.isTerminal){

            } else {

            }
           // parsingTable[][];

            tokensFlow->getToken();

        }
    }

    void cLLParser::fillTable(){
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

    void cLLParser::fillProductions(){
        cProduction p(1);
        cStackElement sEl(oHtml, true);
        p.addStackElem(sEl);
        productionsList.push_back(sEl);
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

    int cLLParser::tokenToColumn(scanner::cToken* token){
        switch(token->getClassNum()){
            case CLASS_STRING: {
                return 0;
            }
            case CLASS_ID: {
                return 1;
            }
            case CLASS_COLOR: {
                return 3;
            }
            case CLASS_INT: {
                return 4;
            }
            case CLASS_EQUAL_SIGN: {
                return 5;
            }
            case CLASS_OPENING_TAGS: {
                switch(token->getSubClassNum()){
                    case html: {
                        return 6;
                    }
                    case head: {
                        return 7;
                    }
                    case title: {
                        return 8;
                    }
                    case meta: {
                        return 9;
                    }
                    case link: {
                        return 10;
                    }
                    case base: {
                        return 11;
                    }
                    case basefont: {
                        return 12;
                    }
                    case body: {
                        return 13;
                    }
                    case img: {
                        return 14;
                    }
                    case br: {
                        return 15;
                    }
                    case p: {
                        return 16;
                    }
                    case h1: {
                        return 17;
                    }
                    case h2: {
                        return 18;
                    }
                    case h3: {
                        return 19;
                    }
                }
            }
        }
    }
}
