#include <antlr4-runtime.h>
#include "NVMParser.h"
#include <string>

namespace nvm {
    class Parser{
    public:
        static void parse(const std::string& program);
    };
}
