#include "nvmCore/JumpCode.h"

nvm::address_t nvm::JumpCode::getSize(uint8_t jumpCode) {
    return isRegister(jumpCode) ? 1 : sizeof(nvm::address_t);
}

bool nvm::JumpCode::isRegister(uint8_t jumpCode) {
    return jumpCode & 0x10;
}

bool nvm::JumpCode::isSubroutine(uint8_t jumpCode) {
    return jumpCode & 0x04;
}

bool nvm::JumpCode::isNegative(uint8_t jumpCode) {
    return jumpCode & 0x08;
}

bool nvm::JumpCode::isRelative(uint8_t jumpCode) {
    return jumpCode & 0x20;
}

bool nvm::JumpCode::shouldJump(uint8_t jumpCode, bool negativeFlag, bool positiveFlag, bool zeroFlag) {
    auto conditionCode = jumpCode & 0xC0;
    switch(conditionCode) {
        case 0x00: return true;
        case 0x40: return negativeFlag;
        case 0x80: return zeroFlag;
        case 0xC0: return positiveFlag;
    }
}