#ifndef TOKEN_H
#define TOKEN_H

#include <string>
#include <vector>
#include "cproduction.h"
#include "cstackelement.h"

namespace parser{
    typedef std::vector<std::vector<int>> table_of_parsing_t;
    typedef std::vector<cProduction> productions_list_t;
//    typedef std::vector<cStackElement> production_t;
}

#endif // TOKEN_H
