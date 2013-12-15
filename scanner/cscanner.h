#ifndef CSCANNER_H
#define CSCANNER_H

#include <string>
#include "ccode.h"
#include "cconstrecognizer.h"
#include "cwordrecognizer.h"
#include "ctokensflow.h"

namespace scanner{
    class cScanner{
    public:
        cScanner(std::string codeFile, cTokensFlow* tokensFlow);
        void startScanning();
    private:
        cTokensFlow* tokensFlow;
        std::string codeFile;
        cWordRecognizer* Word;
        cConstRecognizer* Const;
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
        enum lexemeClasses {
            CLASS_OPERATION_SIGN = 4,
            CLASS_BRACKET = 3,
            CLASS_ERROR = 0
        };
    };
}

#endif // CSCANNER_H
