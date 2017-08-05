#include "testSupport/ObservableCore.h"

int8_t nvm::ObservableCore::getI8Register(uint8_t index) const { return i8Registers_[index]; }
uint8_t nvm::ObservableCore::getUi8Register(uint8_t index) const { return ui8Registers_[index]; }
int16_t nvm::ObservableCore::getI16Register(uint8_t index) const { return i16Registers_[index]; }
uint16_t nvm::ObservableCore::getUi16Register(uint8_t index) const { return ui16Registers_[index]; }
int32_t nvm::ObservableCore::getI32Register(uint8_t index) const { return i32Registers_[index]; }
uint32_t nvm::ObservableCore::getUi32Register(uint8_t index) const { return ui32Registers_[index]; }
f32_t nvm::ObservableCore::getF32Register(uint8_t index) const { return f32Registers_[index]; }
f64_t nvm::ObservableCore::getF64Register(uint8_t index) const { return f64Registers_[index]; }

bool nvm::ObservableCore::getNegativeFlag() const { return  negativeFlag_; }
bool nvm::ObservableCore::getPositiveFlag() const { return  positiveFlag_; }
bool nvm::ObservableCore::getZeroFlag() const { return  zeroFlag_; }
bool nvm::ObservableCore::getCarryFlag() const { return  carryFlag_; }
bool nvm::ObservableCore::getBorrowFlag() const { return  borrowFlag_; }
