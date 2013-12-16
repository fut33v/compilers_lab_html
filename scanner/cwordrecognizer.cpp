#include "cwordrecognizer.h"

namespace scanner{
    cWordRecognizer::cWordRecognizer(std::string reserveredFile, cCode *c){
        idCounter = 0;
        startState = new state();
        if(c != NULL){
            this->code = c;
        } else {
            std::cout<<"Error Code"<<std::endl;
            exit(1);
        }
        std::ifstream file(reserveredFile.c_str(), std::ifstream::in);
        if(!file){
            std::cout<<"Error opening reserved file";
            exit(-1);
        }
        int resWordClass = 0;
        int resWordSubClass = 0;
        while(!file.eof()){
            std::string reserveredWord;
            file >> reserveredWord;
            file >> resWordClass;
            file >> resWordSubClass;
            if(reserveredWord.length() != 0){
                addReserved(reserveredWord, resWordClass, resWordSubClass);
           }
        }
        file.close();
    }

    void cWordRecognizer::addReserved(std::string reserved, int Class, int subClass){
        state *currState = startState;
        for(size_t i = 0; i < reserved.length(); i++){
            int ind = CharToInd(reserved[i]);
            if(ind == ERROR_INDEX){
                std::cout<<"Error in CharToInd"<<std::endl;
                exit(ERROR_INDEX);
            }
            if(currState->st[ind] == NULL){
                currState->st[ind] = new state();
            }
            currState = currState->st[ind];
        }
        currState->Class = Class;
        currState->subClass = subClass;
    }

    bool cWordRecognizer::takeWord(){
        char ch = 0;
        int it = 0;
        while(true){
            ch = code->ShowCh();
            int i = CharToInd(ch);
            if(i >= 0){
                if (((ch== '<' || (ch == ' ') || (ch == '>'))) && (it != 0)){
                    break;
                }
                Token += ch;
                code->GiveCh();
                it++;
            } else {
                break;
            }
        }
        return true;
    }

    cToken cWordRecognizer::getToken(){
        state *currState = startState;
        Token = "";
        if (takeWord()){
            if (Token[0] == '<'){
                if (Token[1] == '/'){
                    for(size_t i = 0; i < Token.length(); i++){
                        int ind = CharToInd(Token[i]);
                        if(currState->st[ind] == NULL){
                            return cToken(code->getStrNum(), CLASS_ERROR, Token);
                        }
                        currState = currState->st[ind];
                    }
                    if (code->ShowCh() == '>'){
                        code->GiveCh();
                        Token.push_back('>');
                        int ind = CharToInd('>');
                        currState = currState->st[ind];
                    }
                    //Closing TAG
                    return cToken(code->getStrNum(), currState->Class, currState->subClass, Token);
                } else {
                    for(size_t i = 1; i < Token.length();i++){
                        int ind = CharToInd(Token[i]);
                        if (((i != Token.length()-1) && (ind > 62) && (ind < 66))){
                            return cToken(code->getStrNum(), CLASS_ERROR, Token);
                        }
                        if(currState->st[ind] == NULL){
                            return cToken(code->getStrNum(), CLASS_ERROR, Token);
                        }
                        currState = currState->st[ind];
                        if (((i == Token.length()-1) && (currState->Class == CLASS_TAG_NAMES)) ||
                        (currState->Class == CLASS_TAG_CLOSING)){
                            return cToken(code->getStrNum(), currState->Class, currState->subClass, Token);
                        }
                    }
                }
            } else {
                for(size_t i = 0; i < Token.length(); i++){
                    int ind = CharToInd(Token[i]);
                    if ((i != Token.length()-1) && (ind > 62) && (ind < 66)){
                        return cToken(code->getStrNum(), CLASS_ERROR, Token);
                    }
                    if(currState->st[ind] == NULL){
                        currState->st[ind] = new state();
                    }
                    currState=currState->st[ind];
                }
                if(currState->Class == CLASS_ERROR){
                    currState->Class = CLASS_IDENTIFICATOR;
                }
                if(currState->Class == CLASS_IDENTIFICATOR){
                    currState->subClass = idCounter++;
                    return cToken(code->getStrNum(), CLASS_IDENTIFICATOR, idCounter, Token);
                }
            }
        }
        return cToken(code->getStrNum(), CLASS_ERROR, Token);
    }

    int cWordRecognizer::CharToInd(char ch){
        if((int)ch>=LETTER_LOWERCASE_ASCII_LOWER_LIMIT && (int)ch<=LETTER_LOWERCASE_ASCII_UPPER_LIMIT){
            return (int)ch - 97;//0..25
        } else if((int)ch>=LETTER_UPPERCASE_ASCII_LOWER_LIMIT && (int)ch<=LETTER_UPPERCASE_ASCII_UPPER_LIMIT){
            return (int)ch - 65;//0..25
        } else if((int)ch>=DIGIT_ASCII_LOWER_LIMIT && (int)ch<=DIGIT_ASCII_UPPER_LIMIT){
            return 52+(int)ch - 48;//52..61
        } else {
            switch(ch){
                case '_': {
                    return 62;
                    break;
                } case '<': {
                    return 63;
                    break;
                } case '>': {
                    return 64;
                    break;
                } case '/': {
                    return 65;
                    break;
                }
            }
        }
        return ERROR_INDEX;
    }
}
