#include "ccode.h"
namespace scanner{
    cCode::cCode(std::string FileName){
        std::ifstream file(FileName.c_str(), std::ifstream::in);
        if(!file){
            std::cout<<"Error opening file";
            exit(1);
        }
        file.seekg(0, std::ios::end);
        std::streampos length = file.tellg();
        file.seekg(0, std::ios::beg);
        vectLen = length;
        buf.reserve(length);
        file.read(&buf[0], length);
        CurrentChNum = NextStrNum = CurrentStrNum = 0;
    }

    char cCode::GiveCh(){
        if(CurrentStrNum != NextStrNum){
            CurrentStrNum = NextStrNum;
        }
        if(buf[CurrentChNum]=='\n'){
            NextStrNum++;
        }
        return buf[CurrentChNum++];
    }

    char cCode::ShowCh(){
        return buf[CurrentChNum];
    }

    bool cCode::IsEnd(){
        if(CurrentChNum == vectLen){
            return true;
        } else {
            return false;
        }
    }
    int cCode::getStrNum(){
        return CurrentStrNum;
    }
}

