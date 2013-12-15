#ifndef CONSTRECOGNIZER_H
#define CONSTRECOGNIZER_H
#include "ccode.h"
#include <set>

namespace scanner{
    class cConstRecognizer{
    public:
        cConstRecognizer(cCode *);
        int getClass();
        std::string getToken();
    private:
        cCode *code;
        std::set<char> availableAfterNum;
        std::string Token;
        int String();
        int Integer(char);
        int Color();
        int lexTable[1][2] = {
            {S_LEX, S_END}
        };
        enum tableState{
            S_LEX,
            S_END
        };
        enum inputCharacter{
            C_DIGIT
        };
        enum lexemeClasses{
            CLASS_ERROR = 0,
            CLASS_INTEGER = 6,
            CLASS_COLOR = 7,
            CLASS_STRING = 8
        };
        enum {
            COLOR_LENGTH = 7
        };
        enum digitsASCII {
            DIGIT_ASCII_LOWER_LIMIT = 48,
            DIGIT_ASCII_UPPER_LIMIT = 57
        };
        enum letterASCII {
            LETTER_UPPERCASE_ASCII_LOWER_LIMIT = 65,
            LETTER_UPPERCASE_ASCII_UPPER_LIMIT = 90,
            LETTER_LOWERCASE_ASCII_LOWER_LIMIT = 97,
            LETTER_LOWERCASE_ASCII_UPPER_LIMIT = 122,
            LETTER_A_UPPERCASE_ASCII = 65,
            LETTER_F_UPPERCASE_ASCII = 70,
            LETTER_A_LOWERCASE_ASCII = 97,
            LETTER_F_LOWERCASE_ASCII = 102
        };
    };
}

#endif // CONSTRECOGNIZER_H
