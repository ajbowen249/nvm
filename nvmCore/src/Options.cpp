#include "nvmCore/Options.h"

nvm::Options::Options() :
    stackSize_(512),
    bootVector_(0) { }

nvm::address_t nvm::Options::getStackSize() const { return stackSize_; }
void nvm::Options::setStackSize(nvm::address_t stackSize) { stackSize_ = stackSize; }

nvm::address_t nvm::Options::getBootVector() const { return bootVector_; }
void nvm::Options::setBootVector(nvm::address_t bootVector) { bootVector_ = bootVector; }

nvm::Error nvm::Options::validate(nvm::Interface::Ptr interface) const {
    auto maxMemory = interface->getMaxMemory();

    if (stackSize_ > maxMemory) {
        return nvm::Error(nvm::ErrorCategory::Configuration, nvm::ErrorDetail::StackSizeGreaterThanMemorySpace);
    }

    if (bootVector_ > maxMemory) {
        return nvm::Error(nvm::ErrorCategory::Configuration, nvm::ErrorDetail::BootVectorGreaterThanMemorySpace);
    }

    if (bootVector_ > maxMemory - stackSize_) {
        return nvm::Error(nvm::ErrorCategory::Configuration, nvm::ErrorDetail::BootVectorInsideStack);
    }

    return nvm::Error();
}
