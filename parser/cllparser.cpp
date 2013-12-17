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
        stack.push(BottomMarker);
        stack.push(HTML);
        fillProductions();
    }

    void cLLParser::startParsing(){
        std::cout<<std::endl;
        while (!tokensFlow->isEnd()){
            scanner::cToken token;
            token = tokensFlow->showToken();
            int top = stack.top();

            if (top > BottomMarker){

            } else if (top != BottomMarker){
                int production = parsingTable[top][tokenToColumn(&token)];
                for (auto it : productionsList){
                    if (it.getNumber() == production){
                        std::cout<<"production:"<<it.getNumber()<<std::endl;
                        stack.pop();
                        for (auto it2 : it){
                            stack.push(it2);
                            std::cout<<it2<<" ";
                        }
                        std::cout<<std::endl;
                        break;
                    }

                }
            } else {
                std::cout<<"String has passed the validation!!!";
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
        //1) <HTML> -> ‘<html’ <Parameters> ‘>’ <WebpageBody> ‘</html>’  {‘<html’}
        cProduction p(1);
        p.push_back(oHtml);
        p.push_back(Parameters);
        p.push_back(tAbove);
        p.push_back(WebpageBody);
        p.push_back(cHtml);
        productionsList.push_back(p);
        p.clear();
        //2) <WebpageBody> -> <Head><Body> {‘<head’}
        p.setNumber(2);
        p.push_back(WebpageBody);
        p.push_back(Head);
        p.push_back(Body);
        productionsList.push_back(p);
        p.clear();
        //3) <Head> -> ‘<head’ <Parameters> ‘>’ <HeadItems> ‘</head>’ {‘<head’}
        p.setNumber(3);
        p.push_back(oHead);
        p.push_back(Parameters);
        p.push_back(tAbove);
        p.push_back(HeadItems);
        p.push_back(cHead);
        productionsList.push_back(p);
        p.clear();
        //4) <Head> -> EMPTY {EMPTY}
        p.setNumber(4);
        p.push_back(oHead);
        p.push_back(Parameters);
        p.push_back(tAbove);
        p.push_back(HeadItems);
        p.push_back(cHead);
        productionsList.push_back(p);
        p.clear();
        //5) <HeadItems> -> <HeadItem><HeadItems> {‘<title’, ‘<meta’, ‘<link’, ‘<base’, ‘<basefont’}
        p.setNumber(5);
        p.push_back(HeadItem);
        p.push_back(HeadItems);
        productionsList.push_back(p);
        p.clear();

        //6) <HeadItems> -> EMPTY {EMPTY}
        //???
        //productionsList.push_back(p);
        //p.clear();

        //7) <HeadItem> -> ‘<title’ <Parameters> ’>’ <Content> ‘</title>’ {‘<title’}
        p.setNumber(7);
        p.push_back(oTitle);
        p.push_back(Parameters);
        p.push_back(tAbove);
        p.push_back(Content);
        p.push_back(cTitle);
        productionsList.push_back(p);
        p.clear();
        //8) <HeadItem> -> ‘<meta’ <Parameters> ‘>’ {‘<meta’}
        p.setNumber(8);
        p.push_back(oMeta);
        p.push_back(Parameters);
        p.push_back(tAbove);
        productionsList.push_back(p);
        p.clear();
        //9) <HeadItem> -> ‘<link <Parameters> ‘>’ {‘<link’}
        p.setNumber(9);
        p.push_back(oLink);
        p.push_back(Parameters);
        p.push_back(tAbove);
        productionsList.push_back(p);
        p.clear();
        //10) <HeadItem> -> ‘<base <Parameters> ‘>’ {‘<base’}
        p.setNumber(10);
        p.push_back(oBase);
        p.push_back(Parameters);
        p.push_back(tAbove);
        productionsList.push_back(p);
        p.clear();
        //11) <HeadItem> -> ‘<basefont’ <Parameters> ‘>’ {‘<basefont’}
        p.setNumber(11);
        p.push_back(oBasefont);
        p.push_back(Parameters);
        p.push_back(tAbove);
        productionsList.push_back(p);
        p.clear();
        //12) <Body> -> ‘<body’ <Parameters> ‘>’ <Content> ‘</body>’ {‘<body’}
        p.setNumber(12);
        p.push_back(oBody);
        p.push_back(Parameters);
        p.push_back(tAbove);
        p.push_back(Content);
        p.push_back(cBody);
        productionsList.push_back(p);
        p.clear();
        //13) <Content> -> <Tag><Content> {‘<img’, ‘<br’, ‘<p’, ‘<h1’, ‘<h2’, ‘<h3’}
        p.setNumber(13);
        p.push_back(Tag);
        p.push_back(Content);
        productionsList.push_back(p);
        p.clear();
        //14) <Content> -> <Word><Content> {STRING}
        p.setNumber(14);
        p.push_back(Word);
        p.push_back(Content);
        productionsList.push_back(p);
        p.clear();

        //15) <Content> -> EMPTY {EMPTY}
        //???
        //productionsList.push_back(p);
        //p.clear();

        //16) <Parameters> -> <Parameter1><Parameters> {id, STRING}
        p.setNumber(16);
        p.push_back(Parameter1);
        p.push_back(Parameters);
        productionsList.push_back(p);
        p.clear();

        //17) <Parameters> -> EMPTY {EMPTY}
        //???

        //18) <Parameter1> -> id <Equal><Parameter> {id}
        p.setNumber(18);
        p.push_back(tId);
        p.push_back(Equal);
        p.push_back(Parameter);
        p.push_back(HeadItems);
        p.push_back(cHead);
        productionsList.push_back(p);
        p.clear();
        //19) <Parameter1> -> STRING {STRING}
        p.setNumber(19);
        p.push_back(tString);
        productionsList.push_back(p);
        p.clear();
        //20) <Equal> -> ‘=’ {‘=’}
        p.setNumber(20);
        p.push_back(tEqual);
        productionsList.push_back(p);
        p.clear();

        //21) <Equal> -> EMPTY {EMPTY}
        //???

        //22) <Parameter> -> STRING {STRING}
        p.setNumber(22);
        p.push_back(tString);
        productionsList.push_back(p);
        p.clear();
        //23) <Parameter> -> COLOR {COLOR}
        p.setNumber(23);
        p.push_back(tColor);
        productionsList.push_back(p);
        p.clear();
        //24) <Parameter> -> id {id}
        p.setNumber(24);
        p.push_back(tId);
        productionsList.push_back(p);
        p.clear();
        //25) <Parameter> -> INT {INT}
        p.setNumber(25);
        p.push_back(tId);
        productionsList.push_back(p);
        p.clear();

        //26) <Parameter> - > EMPTY {EMPTY}
        //???

        //27) <Tag> -> ‘<img’ <Parameters> ‘>’ {‘<img’}
        p.setNumber(27);
        p.push_back(oImg);
        p.push_back(Parameters);
        p.push_back(tAbove);
        productionsList.push_back(p);
        p.clear();
        //28) <Tag> -> ‘<br <Parameters> ‘>’ {‘<br’}
        p.setNumber(28);
        p.push_back(oBr);
        p.push_back(Parameters);
        p.push_back(tAbove);
        productionsList.push_back(p);
        p.clear();
        //29) <Tag> -> ‘<p <Parameters> ‘>’ {‘<p’}
        p.setNumber(29);
        p.push_back(oP);
        p.push_back(Parameters);
        p.push_back(tAbove);
        productionsList.push_back(p);
        p.clear();
        //30) <Tag> -> ‘<h1 <Parameters> ‘>’ <Content> ‘</h1>’ {‘<h1’}
        p.setNumber(30);
        p.push_back(oH1);
        p.push_back(Parameters);
        p.push_back(tAbove);
        p.push_back(Content);
        p.push_back(cH1);
        productionsList.push_back(p);
        p.clear();
        //31) <Tag> -> ‘<h2 <Parameters> ‘>’ <Content> ‘</h2>’ {‘<h2’}
        p.setNumber(31);
        p.push_back(oH2);
        p.push_back(Parameters);
        p.push_back(tAbove);
        p.push_back(Content);
        p.push_back(cH2);
        productionsList.push_back(p);
        p.clear();
        //32) <Tag> -> ‘<h3 <Parameters> ‘>’ <Content> ‘</h3>’ {‘<h3’}
        p.setNumber(32);
        p.push_back(oH3);
        p.push_back(Parameters);
        p.push_back(tAbove);
        p.push_back(Content);
        p.push_back(cH3);
        productionsList.push_back(p);
        p.clear();
        //33) <Word> -> STRING {STRING}
        p.setNumber(33);
        p.push_back(tString);
        productionsList.push_back(p);
        p.clear();
    }

    void cLLParser::showProductions(){
        for (auto it : productionsList){
            for (auto it2 : it){
                std::cout<<it2<<" ";
            }
            std::cout<<std::endl;
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
                return token->getSubClassNum()-8;
            }
        }
        return -1;
    }

    int cLLParser::tokenToStackSymb(scanner::cToken* token){
        switch(token->getClassNum()){
            case CLASS_STRING: {
                return tString;
            }
            case CLASS_ID: {
                return tId;
            }
            case CLASS_COLOR: {
                return tColor;
            }
            case CLASS_INT: {
                return tInt;
            }
            case CLASS_EQUAL_SIGN: {
                return tEqual;
            }
            case CLASS_OPENING_TAGS: {
                return token->getSubClassNum();
            }
            case CLASS_CLOSING_TAGS: {
                return token->getSubClassNum();
            }
        }
        return -1;
    }
}
