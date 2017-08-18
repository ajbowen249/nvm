#ifndef __LINE_H__
#define __LINE_H__

#include <nvmCore/Core.h>
#include <string>

namespace nvm {
    class Line {
    public:
        Line(std::string& code);
        address_t getSize();

    private:
        std::string code_;
    };
}

#endif //__LINE_H__
