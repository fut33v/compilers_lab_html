#ifndef TOKEN_H
#define TOKEN_H

#include <string>
#include <vector>

namespace parser{
    typedef std::vector<std::string> token_flow_t;
    typedef std::vector<std::vector<int>> table_of_parsing_t;
}

#endif // TOKEN_H
