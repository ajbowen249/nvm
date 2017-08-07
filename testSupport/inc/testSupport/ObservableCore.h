#ifndef __OBSERVABLECORE_H__
#define __OBSERVABLECORE_H__

#include <nvmCore/Core.h>

namespace nvm {
    class ObservableCore : public Core {
    public:
        int8_t getI8Register(uint8_t index) const;
        uint8_t getUi8Register(uint8_t index) const;
        int16_t getI16Register(uint8_t index) const;
        uint16_t getUi16Register(uint8_t index) const;
        int32_t getI32Register(uint8_t index) const;
        uint32_t getUi32Register(uint8_t index) const;
        f32_t getF32Register(uint8_t index) const;
        f64_t getF64Register(uint8_t index) const;

        bool getNegativeFlag() const;
        bool getPositiveFlag() const;
        bool getZeroFlag() const;

        address_t getInstructionPointer() const;
    };
}

#endif //__OBSERVABLECORE_H__