#include "inMemoryInterface/InMemoryInterface.h"

nvm::InMemoryInterface::InMemoryInterface(nvm::address_t memorySize) :
    maxAddress_(memorySize - 1),
    memory_(memorySize) { }

nvm::address_t nvm::InMemoryInterface::getMaxMemory() const {
    return maxAddress_;
}

nvm::Error nvm::InMemoryInterface::write(nvm::address_t address, const uint8_t data[], nvm::address_t width) {
    if(address > maxAddress_ || address + width > maxAddress_) {
        return nvm::Error(nvm::ErrorCategory::Memory, nvm::ErrorDetail::AddressOutOfRange);
    }

    for(nvm::address_t i = 0; i < width; i++) {
        memory_[i + address] = data[i];
    }

    return nvm::Error();
}

nvm::Error nvm::InMemoryInterface::read(nvm::address_t address, uint8_t data[], nvm::address_t width) {
    if(address > maxAddress_ || address + width > maxAddress_) {
        return nvm::Error(nvm::ErrorCategory::Memory, nvm::ErrorDetail::AddressOutOfRange);
    }

    for(nvm::address_t i = 0; i < width; i++) {
        data[i] = memory_[i + address];
    }

    return nvm::Error();
}
