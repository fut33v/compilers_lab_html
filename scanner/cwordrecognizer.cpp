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
                if (((i == 63) || (ch == ' ')) && (it != 0)){
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

    void cWordRecognizer::getClass(std::list<std::pair<std::pair<int,int>, std::string>> * classAndToken){
        state *currState = startState;
        Token = "";
        if (takeWord()){
            if (Token[0] == '<'){
                if (Token[1] == '/'){
                    for(size_t i = 0; i < Token.length(); i++){
                        int ind = CharToInd(Token[i]);
                        if(currState->st[ind] == NULL){
                            classAndToken->push_back(std::pair<std::pair<int, int>, std::string>
                            (std::pair<int, int>(CLASS_ERROR, 0), Token));
                            return;
                        }
                        currState = currState->st[ind];
                    }
                    classAndToken->push_back(std::pair<std::pair<int, int>, std::string>
                    ( std::pair<int, int>(currState->Class, currState->subClass), Token));
                    return;
                } else {
                    for (size_t i = 0; i < Token.length()-1; i++){
                        Token[i] = Token[i+1];
                    }
                    Token.pop_back();
                    classAndToken->push_back(std::pair<std::pair<int, int>, std::string>
                    (std::pair<int, int>(CLASS_BRACKET, 1), "<"));
                    for(size_t i = 0; i < Token.length();i++){
                        int ind = CharToInd(Token[i]);
                        if (((i != Token.length()-1) && (ind > 62) && (ind < 66))){
                            classAndToken->push_back(std::pair<std::pair<int, int>, std::string>
                            (std::pair<int, int>(CLASS_ERROR, 0), Token));
                            return;
                        }
                        if ((i == Token.length()-1) && (currState->Class == 1) || (currState->Class == 2)){
                            if (ind == 64){
                                Token.pop_back();
                            }
                            classAndToken->push_back(std::pair<std::pair<int, int>, std::string>
                            ( std::pair<int, int>(currState->Class, currState->subClass), Token));
                            classAndToken->push_back(std::pair<std::pair<int, int>, std::string>
                            ( std::pair<int, int>(CLASS_BRACKET, 2), ">"));
                            return;
                        }
                        if(currState->st[ind] == NULL){
                            classAndToken->push_back(std::pair<std::pair<int, int>, std::string>
                            (std::pair<int, int>(CLASS_ERROR, 0), Token));
                            return;
                        }
                        currState = currState->st[ind];
                        if ((i == Token.length()-1) && (currState->Class == 1) || (currState->Class == 2)){
                            classAndToken->push_back(std::pair<std::pair<int, int>, std::string>
                            ( std::pair<int, int>(currState->Class, currState->subClass), Token));
                            return;
                        }
                    }
                }
            } else {
                for(size_t i = 0; i < Token.length(); i++){
                    int ind = CharToInd(Token[i]);
                    if ((i != Token.length()-1) && (ind > 62) && (ind < 66)){
                        classAndToken->push_back(std::pair<std::pair<int, int>, std::string>
                        ( std::pair<int, int>(CLASS_ERROR, 0), Token));
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
                    classAndToken->push_back(std::pair<std::pair<int, int>, std::string>
                    (std::pair<int, int>(CLASS_IDENTIFICATOR, idCounter), Token));
                }
            }
        } else {
            return;
        }
    }

    std::string cWordRecognizer::getToken(){
        return Token;
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
