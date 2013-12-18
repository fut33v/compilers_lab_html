#ifndef CTOKEN_H
#define CTOKEN_H

#include <string>

namespace scanner {
    class cToken{
    public:
        cToken();
        cToken(int stringNum, int classNum, int subClassNum, std::string value);
        cToken(int stringNum, int classNum, std::string value);
        int getStringNum();
        int getClassNum();
        int getSubClassNum();
        std::string getValue();
        bool hasSubClass();
    private:
        int stringNum;
        int classNum;
        int subClassNum;
        std::string value;
        bool subClassExist;
    };
}
#endif // CTOKEN_H
