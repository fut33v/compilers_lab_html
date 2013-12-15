#ifndef CODE_H
#define CODE_H
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>

namespace scanner{
    class cCode{
    public:
        cCode(std::string FileName);
        char GiveCh();
        char ShowCh();
        int getStrNum();
        bool IsEnd();
    private:
        std::string text;
        std::vector<char> buf;
        int vectLen;
        int CurrentChNum;
        int NextStrNum;
        int CurrentStrNum;
    };
}
#endif // CODE_H
