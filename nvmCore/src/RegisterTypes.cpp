#include "nvmCore/RegisterTypes.h"

nvm::address_t nvm::RegisterUtils::getSize(nvm::RegisterType type) {
    switch (type) {
    case nvm::RegisterType::i8:
    case nvm::RegisterType::ui8:
        return 1;
    case nvm::RegisterType::i16:
    case nvm::RegisterType::ui16:
        return 2;
    case nvm::RegisterType::i32:
    case nvm::RegisterType::ui32:
    case nvm::RegisterType::f32:
        return 4;
    case nvm::RegisterType::f64:
        return 8;
    }

    return 0;
}

nvm::RegisterType nvm::RegisterUtils::typeFromLeftNibble(uint8_t byte) {
    return (nvm::RegisterType)((byte & 0x70) >> 4);
}

nvm::RegisterCategory nvm::RegisterUtils::categoryFromLeftNibble(uint8_t byte) {
    return (nvm::RegisterCategory)((byte & 0x80) >> 4);
}

uint8_t nvm::RegisterUtils::indexFromRightNibble(uint8_t byte) {
    return byte & 0x0F;
}

uint8_t nvm::RegisterUtils::indexFromLeftNibble(uint8_t byte) {
    return (byte & 0xF0) >> 4;
}
