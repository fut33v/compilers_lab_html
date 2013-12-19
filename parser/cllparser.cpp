#include "cllparser.h"

namespace parser{
    cLLParser::cLLParser(scanner::cTokensFlow* tokensFlow){
        this->tokensFlow = tokensFlow;
        fillTable();
    }

    void cLLParser::initParser(){
        while(!stack.empty()){
            stack.pop();
        }
        stack.push(BottomMarker);
        stack.push(HTML);
        fillProductions();
        fillStackSymbolsString();
    }

    void cLLParser::startParsing(){
        while (!tokensFlow->isEnd()){
            scanner::cToken token;
            token = tokensFlow->showToken();
            std::cout<<"__________________________________"<<std::endl;
            std::cout<<"| Token: "<<token.getValue()<<std::endl;
            //sleep(1);
            if (token.getClassNum()== CLASS_ERROR){
                std::cout<<"String has NOT passed the validation (wrong token)!!!";
                return;
            }
            int top;
            top = stack.top();
            std::cout<<"| Top: "<<stackSymbolsString[top]<<std::endl;
            std::cout<<"|_________________________________"<<std::endl;
            if (top > BottomMarker){
                if (top == tokenToStackSymb(&token)){
                    stack.pop();
                    std::cout<<"Token \'"<<token.getValue()<<"\' has been deleted, stack.top: "
                            <<stackSymbolsString[stack.top()]<<std::endl;
                    if (stack.top() == BottomMarker){
                        std::cout<<"String has PASSED the validation!!!"<<std::endl;
                        return;
                    }
                    tokensFlow->getToken();                    
                } else {
                    std::cout<<"String has NOT passed the validation!!! " << top << " "
                            << token.getValue() << " " << tokenToStackSymb(&token);
                    return;
                }
            } else if (top != BottomMarker){
                int production = parsingTable[top][tokenToColumn(&token)];
                //std::cout<<"row:"<<top<<"column:"<<tokenToColumn(&token)<<"token:"<<token.getValue();
                std::cout<<"Production "<<production<<" for "<< stackSymbolsString[top] << ":" << std::endl;
                if ((production > 0) && (production < 33)){
                    for (auto it : productionsList){
                        if (it.getNumber() == production){
                            std::cout<<stackSymbolsString[top]<<" -> ";
                            for (auto it2 : it){
                                std::cout<<stackSymbolsString[it2]<<" ";
                            }
                            std::cout<<std::endl;
                            stack.pop();
                            std::vector<int>::reverse_iterator it2;
                            for (it2 = it.rbegin(); it2!= it.rend(); it2++){
                                stack.push(*it2);
                            }
                            break;
                        }
                    }
                } else {
                    if (parsingTable[top][EMPTY] != 0){
                        std::cout<<"Nullify production for "<< stackSymbolsString[top] <<std::endl;
                        stack.pop();
                    } else {
                        std::cout<<"String has NOT passed the validation!!! (no production)";
                        return;
                    }
                }
            }
        }
    }

    void cLLParser::fillTable(){
        parsingTable = {
            //STRING	id	EMPTY	COLOR	INT	=	<html	<head	<title	<meta	<link	<base	<basefont	<body	<img	<br	<p	<h1	<h2	<h3	-|
            {0,	0,	0,	0,	0,	0,	1,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0}, //<HTML>
            {0,	0,	2,	0,	0,	0,	0,	2,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0}, //<WebpageBody>
            {0,	0,	4,	0,	0,	0,	0,	3,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0}, //<Head>
            {0,	0,	6,	0,	0,	0,	0,	0,	5,	5,	5,	5,	5,	0,	0,	0,	0,	0,	0,	0,	0}, //<HeadItems>
            {0,	0,	0,	0,	0,	0,	0,	0,	7,	8,	9,	10,	11,	0,	0,	0,	0,	0,	0,	0,	0}, //<HeadItem>
            {0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	12,	0,	0,	0,	0,	0,	0,	0}, //<Body>
            {14,0,	15,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	13,	13,	13,	13,	13,	13,	0}, //<Content>
            {16,16,	17,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0}, //<Parameters>
            {19,18,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0}, //<Parameter1>
            {0,	0,	21,	0,	0,	20,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0}, //<Parameter2>
            {22,24,	0,	23,	25,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0}, //<Parameter>
            {0,	0,	0,	0,	0,	0,  0,	0,	0,	0,	0,	0,	0,	0,	26,	27,	28,	29,	30,	31,	0}, //<Tag>
            {32,0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0}  //<Word>
        };
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
        //2) <WebpageBody> -> <Head><Body> {‘<head’, EMPTY}
        p.setNumber(2);
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

        //5) <HeadItems> -> <HeadItem><HeadItems> {‘<title’, ‘<meta’, ‘<link’, ‘<base’, ‘<basefont’}
        p.setNumber(5);
        p.push_back(HeadItem);
        p.push_back(HeadItems);
        productionsList.push_back(p);
        p.clear();

        //6) <HeadItems> -> EMPTY {EMPTY}

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

        //16) <Parameters> -> <Parameter1><Parameters> {id, STRING}
        p.setNumber(16);
        p.push_back(Parameter1);
        p.push_back(Parameters);
        productionsList.push_back(p);
        p.clear();

        //17) <Parameters> -> EMPTY {EMPTY}

        //18) <Parameter1> -> id <Parameter2> {id}
        p.setNumber(18);
        p.push_back(tId);
        p.push_back(Parameter2);
        productionsList.push_back(p);
        p.clear();
        //19) <Parameter1> -> STRING {STRING}
        p.setNumber(19);
        p.push_back(tString);
        productionsList.push_back(p);
        p.clear();
        //20) <Parameter2> -> = <Parameter> {=}
        p.setNumber(20);
        p.push_back(tEqual);
        p.push_back(Parameter);
        productionsList.push_back(p);
        p.clear();

        //21) <Parameter2> -> EMPTY {EMPTY}

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
        p.push_back(tInt);
        productionsList.push_back(p);
        p.clear();
        //26) <Tag> -> ‘<img’ <Parameters> ‘>’ {‘<img’}
        p.setNumber(26);
        p.push_back(oImg);
        p.push_back(Parameters);
        p.push_back(tAbove);
        productionsList.push_back(p);
        p.clear();
        //27) <Tag> -> ‘<br <Parameters> ‘>’ {‘<br’}
        p.setNumber(27);
        p.push_back(oBr);
        p.push_back(Parameters);
        p.push_back(tAbove);
        productionsList.push_back(p);
        p.clear();
        //28) <Tag> -> ‘<p <Parameters> ‘>’ {‘<p’}
        p.setNumber(28);
        p.push_back(oP);
        p.push_back(Parameters);
        p.push_back(tAbove);
        productionsList.push_back(p);
        p.clear();
        //29) <Tag> -> ‘<h1 <Parameters> ‘>’ <Content> ‘</h1>’ {‘<h1’}
        p.setNumber(29);
        p.push_back(oH1);
        p.push_back(Parameters);
        p.push_back(tAbove);
        p.push_back(Content);
        p.push_back(cH1);
        productionsList.push_back(p);
        p.clear();
        //30) <Tag> -> ‘<h2 <Parameters> ‘>’ <Content> ‘</h2>’ {‘<h2’}
        p.setNumber(30);
        p.push_back(oH2);
        p.push_back(Parameters);
        p.push_back(tAbove);
        p.push_back(Content);
        p.push_back(cH2);
        productionsList.push_back(p);
        p.clear();
        //31) <Tag> -> ‘<h3 <Parameters> ‘>’ <Content> ‘</h3>’ {‘<h3’}
        p.setNumber(31);
        p.push_back(oH3);
        p.push_back(Parameters);
        p.push_back(tAbove);
        p.push_back(Content);
        p.push_back(cH3);
        productionsList.push_back(p);
        p.clear();
        //32) <Word> -> STRING {STRING}
        p.setNumber(32);
        p.push_back(tString);
        productionsList.push_back(p);
        p.clear();
    }

    void cLLParser::fillStackSymbolsString(){
        stackSymbolsString = {
            "<HTML>",
            "<WebpageBody>",
            "<Head>",
            "<HeadItems>",
            "<HeadItem>",
            "<Body>",
            "<Content>",
            "<Parameters>",
            "<Parameter1>",
            "<Parameter2>",
            "<Parameter>",
            "<Tag>",
            "<Word>",
            "BottomMarker",
            "<html",
            "<head",
            "<title",
            "<meta",
            "<base",
            "<link",
            "<basefont",
            "<body",
            "<img",
            "<br",
            "<p",
            "<h1",
            "<h2",
            "<h3",
            "</html>",
            "</head>",
            "</title>",
            "</body>",
            "</h1>",
            "</h2>",
            "</h3>",
            "</p>",
            ">",
            "id",
            "=",
            "INT",
            "COLOR",
            "STRING"
        };
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
            case CLASS_CLOSING_TAGS: {
                return -1;
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
            case CLASS_CLOSING_BRACE: {
                return tAbove;
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
