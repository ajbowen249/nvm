#include "nvmCore/Core.h"

nvm::Error nvm::Core::initialize(nvm::Interface::Ptr machineInterface, nvm::Options::Ptr options) { 
	interface_ = machineInterface;
	auto validationError = options->validate(interface_);
	if (validationError) return validationError;


	return nvm::Error();
}

void nvm::Core::reset() {
	instructionPointer_ = options_->getBootVector();
	stackPointer_ = interface_->getMaxMemory();
}

nvm::Error nvm::Core::process() {
	uint8_t instruction[LONGESTINSTRUCTION];
	auto fetchError = fetchAndIncrement(instruction);
	if (fetchError) return fetchError;

	return nvm::Error();
}

nvm::Error nvm::Core::fetchAndIncrement(uint8_t instruction[]) {
	auto opcode = interface_->read<uint8_t>(instructionPointer_++);
	instruction[0] = opcode;

	//TODO:: As the instruction set matures, reallocate the opcodes
	//       to get an efficient pattern to denote instruction size.

	address_t additionalBytes = 0;

	switch (opcode) {
	case nvm::Instruction::Add:
	case nvm::Instruction::Subtract:
	case nvm::Instruction::Multiply:
	case nvm::Instruction::Divide:
		additionalBytes = 2;
		break;
	default:
		break;
	}

	for (address_t i = 0; i < additionalBytes; i++) {
		instruction[i + 1] = interface_->read<uint8_t>(instructionPointer_++);
	}

	return nvm::Error();
}
