#ifndef __PARSER_H__
#define __PARSER_H__

#include <nvmCore/Core.h>
#include "ParseError.h"
#include <vector>

namespace nvm {
    class Parser {
    public:
        static ParseResult<std::vector<uint8_t>> Parse(const char* program);
    };
}

#endif //__PARSER_H__
