#ifndef WORDRECOGNIZER_H
#define WORDRECOGNIZER_H
#include <string>
#include <fstream>
#include <set>
#include <list>
#include <iostream>
#include <cstdlib>
#include "ccode.h"
#include "ctoken.h"

namespace scanner{
    class cWordRecognizer{
    public:
        cWordRecognizer(std::string, cCode*);
        cToken getToken();
    private:
        std::string Token;
        std::set<char> availableCh;
        int idCounter;
        cCode *code;
        int CharToInd(char);
        void addReserved(std::string, int, int);
        bool takeWord();
        enum digitsASCII {
            DIGIT_ASCII_LOWER_LIMIT = 48,
            DIGIT_ASCII_UPPER_LIMIT = 57
        };
        enum letterASCII {
            LETTER_UPPERCASE_ASCII_LOWER_LIMIT = 65,
            LETTER_UPPERCASE_ASCII_UPPER_LIMIT = 90,
            LETTER_LOWERCASE_ASCII_LOWER_LIMIT = 97,
            LETTER_LOWERCASE_ASCII_UPPER_LIMIT = 122
        };
        enum numberOf {
            NUMBER_OF_LETTERS = 26,
            NUMBER_OF_DIGITS = 10,
            NUMBER_OF_OTHER = 4
        };
        enum lexemeClasses{
            CLASS_TAG_NAMES = 1,
            CLASS_TAG_CLOSING = 2,
            CLASS_IDENTIFICATOR = 5,
            CLASS_BRACKET = 3,
            CLASS_ERROR = 0
        };
        enum magicNumbers {
            MAYBE_CLOSING_TAG = 666,
            MAYBE_NOT_CLOSING = 667,
            MAGIC_NUMBER = 10
        };
        enum {
            ERROR_INDEX = -1
        };
        struct state{
            int Class;
            int subClass;
            state *st[2*NUMBER_OF_LETTERS+NUMBER_OF_DIGITS+NUMBER_OF_OTHER];
            state(){
                int number = 2*NUMBER_OF_LETTERS+NUMBER_OF_DIGITS+NUMBER_OF_OTHER;
                Class = CLASS_ERROR;
                subClass = CLASS_ERROR;
                for(int i = 0; i < number; i++){
                    st[i] = NULL;
                }
            }
        };
        state *startState;
    };
}

#endif // WORDRECOGNIZER_H

