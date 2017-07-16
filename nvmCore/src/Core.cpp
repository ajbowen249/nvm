#include "nvmCore/Core.h"

nvm::Error nvm::Core::initialize(nvm::Interface::Ptr machineInterface, nvm::Options::Ptr options) { 
	interface_ = machineInterface;
	auto validationError = options->validate(interface_);
	if (validationError) {
		return validationError;
	}



	return nvm::Error();
}

nvm::Error nvm::Core::process() {
    //do nothing yet
	return nvm::Error();
}
