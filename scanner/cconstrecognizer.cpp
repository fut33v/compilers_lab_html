#include "cconstrecognizer.h"

namespace scanner{
    cConstRecognizer::cConstRecognizer(cCode *c){
        if(c != NULL)
            this->code = c;
        else{
            std::cout<<"Error Code"<<std::endl;
            exit(-1);
        }
        Token="";
        availableAfterNum.insert('>');
        availableAfterNum.insert(' ');
        availableAfterNum.insert('\n');
    }

    int cConstRecognizer::getClass(){
        Token="";
        char FirstCh = code->GiveCh();
        if(FirstCh == '\''){
            return String();
        } else if(FirstCh == '#'){
            return Color();
        } else {
            return Integer(FirstCh);
        }
    }

    int cConstRecognizer::String(){
        char ch;
        bool brk = false;
        while(!code->IsEnd() && (brk != true)){
            ch = code->GiveCh();
            if ((ch == '\'') /*|| (ch == ' ')*/ || (ch == '\n')){
                brk = true;
            }
            if (!brk){
                Token += ch;
            }
        }
        if (ch == '\''){
            return CLASS_STRING;
        } else {
            return CLASS_ERROR;
        }
    }

    int cConstRecognizer::Integer(char first){
        Token += first;
        char ch;
        int nextstate = S_LEX;
        int state = S_LEX;
        while (nextstate != S_END){
            ch = code->ShowCh();
            state = nextstate;
            if ((int)ch >= DIGIT_ASCII_LOWER_LIMIT && (int)ch <= DIGIT_ASCII_UPPER_LIMIT){
                nextstate = lexTable[state][C_DIGIT];
            } else {
                nextstate = S_END;
            } if(nextstate != S_END){
                Token += ch;
                state = nextstate;
                code->GiveCh();
            }
        }
        if(nextstate == S_END)
            if(availableAfterNum.find(ch) != availableAfterNum.end()){
                return CLASS_INTEGER;
            }
        while(ch!=' ' && ch!='\n'){
            ch = code->GiveCh();
            if(ch!=' ' && ch!='\n')
                Token+=ch;
        }
        return CLASS_ERROR;
    }

    int cConstRecognizer::Color(){
        Token += '#';
        char ch;
        int nextstate = S_LEX;
        int state = S_LEX;
        while (nextstate != S_END){
            ch = code->ShowCh();
            state = nextstate;
            if (((int)ch >= DIGIT_ASCII_LOWER_LIMIT && (int)ch <= DIGIT_ASCII_UPPER_LIMIT) ||
            ((int)ch >= LETTER_A_LOWERCASE_ASCII && (int)ch <= LETTER_F_LOWERCASE_ASCII) ||
            ((int)ch >= LETTER_A_UPPERCASE_ASCII && (int)ch <= LETTER_F_UPPERCASE_ASCII)){
                nextstate = lexTable[state][C_DIGIT];
            } else {
                nextstate = S_END;
            } if(nextstate != S_END){
                Token+=ch;
                state = nextstate;
                code->GiveCh();
            }
        }
        if(nextstate == S_END){
            if((availableAfterNum.find(ch) != availableAfterNum.end()) && (Token.length() == COLOR_LENGTH)){
                return CLASS_COLOR;
            }
        }
        while(ch!=' ' && ch!='\n'){
            ch = code->GiveCh();
            if(ch!=' ' && ch!='\n')
                Token+=ch;
        }
        return CLASS_ERROR;
    }

    std::string cConstRecognizer::getToken(){
        return Token;
    }
}
