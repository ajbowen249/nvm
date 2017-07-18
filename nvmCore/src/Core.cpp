#include "nvmCore/Core.h"
#include "nvmCore/RegisterTypes.h"

#define REGISTER_ARRAY_FUNC(REG_CAT, REG_TYPE, FUNC, ...)   \
{                                                           \
    if (REG_CAT == nvm::RegisterCategory::GeneralPurpose) { \
        switch (REG_TYPE) {                                 \
        case nvm::RegisterType::i8:                         \
            FUNC(i8Registers_, ##__VA_ARGS__);              \
            break;                                          \
        case nvm::RegisterType::ui8:                        \
            FUNC(ui8Registers_, ##__VA_ARGS__);             \
            break;                                          \
        case nvm::RegisterType::i16:                        \
            FUNC(i16Registers_, ##__VA_ARGS__);             \
            break;                                          \
        case nvm::RegisterType::ui16:                       \
            FUNC(ui16Registers_, ##__VA_ARGS__);            \
            break;                                          \
        case nvm::RegisterType::i32:                        \
            FUNC(i32Registers_, ##__VA_ARGS__);             \
            break;                                          \
        case nvm::RegisterType::ui32:                       \
            FUNC(ui32Registers_, ##__VA_ARGS__);            \
            break;                                          \
        case nvm::RegisterType::f32:                        \
            FUNC(f32Registers_, ##__VA_ARGS__);             \
            break;                                          \
        case nvm::RegisterType::f64:                        \
            FUNC(f64Registers_, ##__VA_ARGS__);             \
            break;                                          \
        }                                                   \
    }                                                       \
    else {                                                  \
                                                            \
    }                                                       \
}                                                           \

nvm::Error nvm::Core::initialize(nvm::Interface::Ptr machineInterface, nvm::Options::Ptr options) { 
    interface_ = machineInterface;
    auto validationError = options->validate(interface_);
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
    auto fetchError = fetchAndIncrement(instruction);
    if (fetchError) return fetchError;

    auto opcode = instruction[0];
    Error instructionError;

    switch (opcode)
    {
    case nvm::Instruction::NoOp: instructionError = noOp(); break;
    case nvm::Instruction::Add: instructionError = add(instruction); break;
    case nvm::Instruction::Subtract: instructionError = subtract(instruction); break;
    case nvm::Instruction::Multiply: instructionError = multiply(instruction); break;
    case nvm::Instruction::Divide: instructionError = divide(instruction); break;
    default:
        break;
    }

    return nvm::Error();
}

nvm::Error nvm::Core::fetchAndIncrement(uint8_t instruction[]) {
    auto opcodeOrError = interface_->read<uint8_t>(instructionPointer_++);
    if (opcodeOrError.error_) return opcodeOrError.error_;

    auto opcode = opcodeOrError.data_;
    instruction[0] = opcode;

    //TODO:: As the instruction set matures, reallocate the opcodes
    //       to get an efficient pattern to denote instruction size.

    address_t additionalBytes;

    switch (opcode) {
    case nvm::Instruction::Add:
    case nvm::Instruction::Subtract:
    case nvm::Instruction::Multiply:
    case nvm::Instruction::Divide:
        additionalBytes = 2;
        break;
    case nvm::Instruction::NoOp:
        additionalBytes = 0;
        break;
    default:
        return nvm::Error(nvm::ErrorCategory::Instruction, nvm::ErrorDetail::InvalidOpcode);
    }

    for (address_t i = 0; i < additionalBytes; i++) {
        auto byteOrError = interface_->read<uint8_t>(instructionPointer_++);
        if (byteOrError.error_) return byteOrError.error_;

        instruction[i + 1] = byteOrError.data_;
    }

    return nvm::Error();
}

nvm::Error nvm::Core::getTripleRegister(uint8_t instruction[], uint8_t& regCategory, uint8_t& regType, uint8_t& arg1, uint8_t& arg2, uint8_t& arg3) {
    regCategory = (instruction[1] & 0x80) >> 4;
    regType = (instruction[1] & 0x70) >> 4;
    arg1 = instruction[1] & 0x0F;
    arg2 = (instruction[2] & 0xF0) >> 4;
    arg3 = instruction[2] & 0x0F;

    return nvm::Error();
}

#pragma region instructions
nvm::Error nvm::Core::noOp() {
    return nvm::Error();
}

#define MATH_INSTRUCTION(OPERATION)                                                                             \
nvm::Error nvm::Core::OPERATION(uint8_t instruction[]) {                                                        \
    uint8_t regCategory, regType, destination, operand1, operand2;                                              \
    auto registerError = getTripleRegister(instruction, regCategory, regType, destination, operand1, operand2); \
    if (registerError) return registerError;                                                                    \
    REGISTER_ARRAY_FUNC(regCategory, regType, OPERATION, destination, operand1, operand2);                      \
    return nvm::Error();                                                                                        \
}                                                                                                               \

MATH_INSTRUCTION(add)
MATH_INSTRUCTION(subtract)
MATH_INSTRUCTION(multiply)
MATH_INSTRUCTION(divide)

#pragma endregion instructions
