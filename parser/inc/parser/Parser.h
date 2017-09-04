#ifndef __PARSER_H__
#define __PARSER_H__

#include <iostream>

namespace nvm {
    class Parser {
    public:
        static void parse(std::ifstream& programStream);
    };
}

#endif //__PARSER_H__
