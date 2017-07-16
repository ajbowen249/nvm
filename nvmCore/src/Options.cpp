#include "nvmCore/Options.h"

nvm::Options::Options() :
    stackSize_(512) { }

nvm::address_t nvm::Options::getStackSize() { return stackSize_; }
void nvm::Options::setStackSize(nvm::address_t stackSize) { stackSize_ = stackSize; }

nvm::Error nvm::Options::validate(nvm::Interface::Ptr interface) {
	if (stackSize_ > interface->getMaxMemory()) {
		return nvm::Error(nvm::ErrorCategory::Configuration, nvm::ErrorDetail::StackSizeGreaterThanMemorySpace);
	}

	return nvm::Error();
}
