#include "cscanner.h"

namespace scanner{
    cScanner::cScanner(std::string codeFile, cTokensFlow* tokensFlow){
        this->codeFile = codeFile;
        this->tokensFlow = tokensFlow;
    }

    void cScanner::startScanning(){
        cCode code(codeFile);
        cConstRecognizer Const(&code);
        cWordRecognizer Word("reserved.words", &code);
        std::string Token;
        while(!code.IsEnd()){
            char ch = code.ShowCh();
            if(((int)ch >= DIGIT_ASCII_LOWER_LIMIT && (int)ch <= DIGIT_ASCII_UPPER_LIMIT) || (ch == '\'') || (ch == '#')){
                int Class = Const.getClass();
                Token = Const.getToken();
                tokensFlow->addToken(cToken(code.getStrNum(), Class, Token));
            } else if(((int)ch >= LETTER_LOWERCASE_ASCII_LOWER_LIMIT && (int)ch <= LETTER_LOWERCASE_ASCII_UPPER_LIMIT) ||
            ((int)ch >= LETTER_UPPERCASE_ASCII_LOWER_LIMIT && (int)ch <= LETTER_UPPERCASE_ASCII_UPPER_LIMIT) || (ch == '_') || (ch == '<')){
                std::list<std::pair<std::pair<int,int>, std::string> > classAndToken;
                Word.getClass(&classAndToken);
                for (auto it : classAndToken){
                    tokensFlow->addToken(cToken(code.getStrNum(), it.first.first, it.first.second, it.second));
                }
                while (!classAndToken.empty()){
                    classAndToken.pop_back();
                }
            } else if(ch == ' ' || ch == '\n' || ch == '\t'){
                code.GiveCh();
            }
            else if(ch == '>' || ch == '=' || ch == '/'){
                code.GiveCh();
                switch (ch){
                    case '=': {
                        Token = "=";
                        tokensFlow->addToken(cToken(code.getStrNum(), CLASS_OPERATION_SIGN, Token));
                        break;
                    }
                    case '>': {
                        Token = ">";
                        tokensFlow->addToken(cToken(code.getStrNum(), CLASS_BRACKET, Token));
                        break;
                    }
                    case '/': {
                        Token = "/";
                        tokensFlow->addToken(cToken(code.getStrNum(), CLASS_ERROR, Token));
                        break;
                    }
                }
            }
        }
    }
}
