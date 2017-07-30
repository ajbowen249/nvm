#ifndef __OBSERVABLECORE_H__
#define __OBSERVABLECORE_H__

#include <nvmCore/Core.h>

namespace nvm {
    class ObservableCore : public Core {
    public:
        int8_t getI8Register(uint8_t index);
        uint8_t getUi8Register(uint8_t index);
        int16_t getI16Register(uint8_t index);
        uint16_t getUi16Register(uint8_t index);
        int32_t getI32Register(uint8_t index);
        uint32_t getUi32Register(uint8_t index);
        f32_t getF32Register(uint8_t index);
        f64_t getF64Register(uint8_t index);
    };
}

#endif //__OBSERVABLECORE_H__