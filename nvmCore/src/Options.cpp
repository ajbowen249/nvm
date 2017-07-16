#include "nvmCore/Options.h"
#include <functional>

nvm::Options::Options() :
    stackSize_(512),
	bootVector_(0) { }

nvm::address_t nvm::Options::getStackSize() const { return stackSize_; }
void nvm::Options::setStackSize(nvm::address_t stackSize) { stackSize_ = stackSize; }

nvm::address_t nvm::Options::getBootVector() const { return bootVector_; }
void nvm::Options::setBootVector(nvm::address_t bootVector) { bootVector_ = bootVector; }

nvm::Error nvm::Options::validate(nvm::Interface::Ptr interface) const {
	auto maxMemory = interface->getMaxMemory();
	auto configurationError = std::function<nvm::Error(nvm::ErrorDetail)>([](nvm::ErrorDetail detail) {
		return nvm::Error(nvm::ErrorCategory::Configuration, detail);
	});

	if (stackSize_ > maxMemory) {
		return configurationError(nvm::ErrorDetail::StackSizeGreaterThanMemorySpace);
	}

	if (bootVector_ > maxMemory) {
		return configurationError(nvm::ErrorDetail::BootVectorGreaterThanMemorySpace);
	}

	if (bootVector_ > maxMemory - stackSize_) {
		return configurationError(nvm::ErrorDetail::BootVectorInsideStack);
	}

	return nvm::Error();
}
