#ifndef __IXFlags_H__
#define __IXFlags_H__

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

    class RWCode {
    public:
        static address_t getSize(uint8_t rwCode);
        static bool isRegisterSource(uint8_t rwCode);
        static bool addRegisters(uint8_t rwCode);
        static RegisterType getSourceRegisterType(uint8_t rwCode);
    };
}

#endif //__IXFlags_H__