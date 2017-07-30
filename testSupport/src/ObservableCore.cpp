#include "testSupport/ObservableCore.h"

#define GET_REGISTER(TYPE, NAME, REGS)          \
TYPE nvm::ObservableCore::NAME(uint8_t index) { \
    return REGS[index];                         \
}                                               \


GET_REGISTER(int8_t, getI8Register, i8Registers_)
GET_REGISTER(uint8_t, getUi8Register, ui8Registers_)
GET_REGISTER(int16_t, getI16Register, i16Registers_)
GET_REGISTER(uint16_t, getUi16Register, ui16Registers_)
GET_REGISTER(int32_t, getI32Register, i32Registers_)
GET_REGISTER(uint32_t, getUi32Register, ui32Registers_)
GET_REGISTER(f32_t, getF32Register, f32Registers_)
GET_REGISTER(f64_t, getF64Register, f64Registers_)
