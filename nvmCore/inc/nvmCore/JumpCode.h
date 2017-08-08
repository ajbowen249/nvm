#ifndef __JUMPCODE_H__
#define __JUMPCODE_H__

#include "nvmCore/RegisterTypes.h"

namespace nvm {
    class JumpCode {
    public:
        static address_t getSize(uint8_t jumpCode);
        static bool isRegister(uint8_t jumpCode);
        static bool isSubroutine(uint8_t jumpCode);
        static bool isNegative(uint8_t jumpCode);
        static bool isRelative(uint8_t jumpCode);
        static bool shouldJump(uint8_t jumpCode, bool negativeFlag, bool positiveFlag, bool zeroFlag);
    };
}

#endif //__JUMPCODE_H__