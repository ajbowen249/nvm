#include "nvmCore/Core.h"
#include "nvmCore/CoreMacros.h"
#include "nvmCore/RegisterTypes.h"
#include "nvmCore/JumpCode.h"

nvm::Error nvm::Core::initialize(nvm::Interface::Ptr machineInterface, nvm::Options::Ptr options) { 
    interface_ = machineInterface;
    options_ = options;
    auto validationError = options_->validate(interface_);
    if (validationError) return validationError;

    return nvm::Error();
}

void nvm::Core::reset() {
    instructionPointer_ = options_->getBootVector();
    stackPointer_ = interface_->getMaxMemory();

    negativeFlag_, positiveFlag_, zeroFlag_ = false;
}

nvm::Error nvm::Core::process() {
    uint8_t instruction[LONGESTINSTRUCTION];
    RETURN_IF_ERROR(fetchInstruction(instruction));

    auto opcode = instruction[0];
    Error instructionError;

    switch (opcode)
    {
    case nvm::Instruction::NoOp: instructionError = noOp(); break;
    case nvm::Instruction::Add: instructionError = add(instruction); break;
    case nvm::Instruction::Subtract: instructionError = subtract(instruction); break;
    case nvm::Instruction::Multiply: instructionError = multiply(instruction); break;
    case nvm::Instruction::Divide: instructionError = divide(instruction); break;
    case nvm::Instruction::SetLiteral: instructionError = setLiteral(instruction); break;
    case nvm::Instruction::Jump: instructionError = jump(instruction); break;
    default:
        break;
    }

    return instructionError;
}

nvm::Error nvm::Core::fetchInstruction(uint8_t instruction[]) {
    RETURN_IF_ERROR(fetchAndIncrement(instruction, 0, 1));

    //TODO:: As the instruction set matures, reallocate the opcodes
    //       to get an efficient pattern to denote instruction size.

    switch (instruction[0]) {
    case nvm::Instruction::Add:
    case nvm::Instruction::Subtract:
    case nvm::Instruction::Multiply:
    case nvm::Instruction::Divide:
        return fetchAndIncrement(instruction, 1, 2);
    case nvm::Instruction::SetLiteral:
        RETURN_IF_ERROR(fetchAndIncrement(instruction, 1, 1));
        return fetchAndIncrement(instruction, 2, nvm::RegisterUtils::getSize(nvm::RegisterUtils::typeFromLeftNibble(instruction[1])));
    case nvm::Instruction::Jump:
        RETURN_IF_ERROR(fetchAndIncrement(instruction, 1, 1));
        return fetchAndIncrement(instruction, 2, nvm::JumpCode::getSize(instruction[1]));
    case nvm::Instruction::NoOp:
        return nvm::Error();
    default:
        return nvm::Error(nvm::ErrorCategory::Instruction, nvm::ErrorDetail::InvalidOpcode);
    }
}

nvm::Error nvm::Core::fetchAndIncrement(uint8_t instruction[], nvm::address_t index, nvm::address_t toRead) {
    nvm::address_t i;
    for (nvm::address_t i = 0; i < toRead; i++) {
        auto byteOrError = interface_->read<uint8_t>(instructionPointer_++);
        if (byteOrError.error_) return byteOrError.error_;

        instruction[index + i] = byteOrError.data_;
    }

    return nvm::Error();
}

nvm::Error nvm::Core::getTripleRegister(uint8_t instruction[], uint8_t& regCategory, uint8_t& regType, uint8_t& arg1, uint8_t& arg2, uint8_t& arg3) {
    regCategory = nvm::RegisterUtils::categoryFromLeftNibble(instruction[1]);
    regType = nvm::RegisterUtils::typeFromLeftNibble(instruction[1]);
    arg1 = nvm::RegisterUtils::indexFromRightNibble(instruction[1]);
    arg2 = nvm::RegisterUtils::indexFromLeftNibble(instruction[2]);
    arg3 = nvm::RegisterUtils::indexFromRightNibble(instruction[2]);

    return nvm::Error();
}

#pragma region instructions
nvm::Error nvm::Core::noOp() {
    return nvm::Error();
}

MATH_INSTRUCTION(add)
MATH_INSTRUCTION(subtract)
MATH_INSTRUCTION(multiply)
MATH_INSTRUCTION(divide)

nvm::Error nvm::Core::setLiteral(uint8_t instruction[]) {
    auto regCategory = nvm::RegisterUtils::categoryFromLeftNibble(instruction[1]);
    auto regType = nvm::RegisterUtils::typeFromLeftNibble(instruction[1]);
    auto dest = nvm::RegisterUtils::indexFromRightNibble(instruction[1]);

    switch (regType)
    {
    case nvm::RegisterType::i8:
        setLiteral(i8Registers_, dest, *((int8_t*)&instruction[2]));
        break;
    case nvm::RegisterType::ui8:
        setLiteral(ui8Registers_, dest, *((uint8_t*)&instruction[2]));
        break;
    case nvm::RegisterType::i16:
        setLiteral(i16Registers_, dest, *((int16_t*)&instruction[2]));
        break;
    case nvm::RegisterType::ui16:
        setLiteral(ui16Registers_, dest, *((uint16_t*)&instruction[2]));
        break;
    case nvm::RegisterType::i32:
        setLiteral(i32Registers_, dest, *((int32_t*)&instruction[2]));
        break;
    case nvm::RegisterType::ui32:
        setLiteral(ui32Registers_, dest, *((uint32_t*)&instruction[2]));
        break;
    case nvm::RegisterType::f32:
        setLiteral(f32Registers_, dest, *((f32_t*)&instruction[2]));
        break;
    case nvm::RegisterType::f64:
        setLiteral(f64Registers_, dest, *((f64_t*)&instruction[2]));
        break;
    }

    return nvm::Error();
}

nvm::Error nvm::Core::jump(uint8_t instruction[]) {
    //TODO: Push IP to stack if necessary
    auto jumpCode = instruction[1];
    if(nvm::JumpCode::shouldJump(jumpCode, negativeFlag_, positiveFlag_, zeroFlag_)) {
        long addressOffset;
        auto isRelative = nvm::JumpCode::isRelative(jumpCode);
        if(nvm::JumpCode::isRegister(jumpCode)) {
            auto registerID = instruction[2];
            auto regCategory = nvm::RegisterUtils::categoryFromLeftNibble(registerID);
            auto regType = nvm::RegisterUtils::typeFromLeftNibble(registerID);
            auto address = nvm::RegisterUtils::indexFromRightNibble(registerID);

            switch (regType)
            {
            case nvm::RegisterType::i8: addressOffset = (long)i8Registers_[address]; break;
            case nvm::RegisterType::ui8: addressOffset = (long)ui8Registers_[address]; break;
            case nvm::RegisterType::i16: addressOffset = (long)i16Registers_[address]; break;
            case nvm::RegisterType::ui16: addressOffset = (long)ui16Registers_[address]; break;
            case nvm::RegisterType::i32: addressOffset = (long)i32Registers_[address]; break;
            case nvm::RegisterType::ui32: addressOffset = (long)ui32Registers_[address]; break;
            case nvm::RegisterType::f32:
            case nvm::RegisterType::f64:
                return nvm::Error(nvm::ErrorCategory::Instruction, nvm::ErrorDetail::UnsupportedRegister);
            }
        } else {
            nvm::address_t literalAddress = *((nvm::address_t*)&instruction[2]);
            addressOffset = (long)literalAddress;
            if(isRelative && nvm::JumpCode::isNegative(jumpCode)) addressOffset *= -1;
        }

        long finalAddress = isRelative ?
            ((long)instructionPointer_) + addressOffset :
            addressOffset;

        if(finalAddress > interface_->getMaxMemory() || finalAddress < 0) {
            return nvm::Error(nvm::ErrorCategory::Memory, nvm::ErrorDetail::AddressOutOfRange);
        } else {
            instructionPointer_ = (nvm::address_t)finalAddress;
        }
    }

    return nvm::Error();
}
#pragma endregion instructions
