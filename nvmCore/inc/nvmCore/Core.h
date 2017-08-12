#ifndef __CORE_H__
#define __CORE_H__

/*
The core implementation of the nvm
*/

#include "Options.h"
#include "Error.h"

#include <type_traits>

namespace nvm {
    enum Instruction {
        NoOp = 0x00,
        Add = 0x01,
        Subtract = 0x02,
        Multiply = 0x03,
        Divide = 0x04,
        SetLiteral = 0x05,
        Jump = 0x06,
        Return = 0x07,
        Increment = 0x08,
        Decrement = 0x09
    };

    class Core {
    public:
        Error initialize(Interface::Ptr machineInterface, Options::Ptr options);
        Error process();
        void reset();

    protected:
        int8_t i8Registers_[NUMGPREGS];
        uint8_t ui8Registers_[NUMGPREGS];
        int16_t i16Registers_[NUMGPREGS];
        uint16_t ui16Registers_[NUMGPREGS];
        int32_t i32Registers_[NUMGPREGS];
        uint32_t ui32Registers_[NUMGPREGS];
        f32_t f32Registers_[NUMGPREGS];
        f64_t f64Registers_[NUMGPREGS];

        bool negativeFlag_;
        bool positiveFlag_;
        bool zeroFlag_;

        address_t instructionPointer_;

        template <typename tdata>
        ErrorUnion<tdata> scrapeStack(bool pop) {
            auto newStackPointer = stackPointer_ + sizeof(tdata);

            if (newStackPointer > interface_->getMaxMemory()) {
                return Error(ErrorCategory::Memory, ErrorDetail::StackUnderflow);
            }

            auto readResult = interface_->read<tdata>(stackPointer_);

            if (pop) {
                stackPointer_ = newStackPointer;
            }

            return readResult;
        }

    private:
        Interface::Ptr interface_;
        Options::Ptr options_;

        address_t stackPointer_;

        Error fetchInstruction(uint8_t instruction[]);
        Error fetchAndIncrement(uint8_t instruction[], address_t index, address_t toRead);
        Error getTripleRegister(uint8_t instruction[], uint8_t& regCategory, uint8_t& regType, uint8_t& arg1, uint8_t& arg2, uint8_t& arg3);

        template <typename tdata>
        void setResultFlags(tdata resultValue) {
            tdata zero = 0;
            negativeFlag_ = resultValue < zero;
            positiveFlag_ = resultValue > zero;
            zeroFlag_ = resultValue == zero;
        }

        template <typename tdata>
        void add(tdata registers[], uint8_t destination, uint8_t operand1, uint8_t operand2) {
            registers[destination] = registers[operand1] + registers[operand2];

            setResultFlags(registers[destination]);
        }

        template <typename tdata>
        void subtract(tdata registers[], uint8_t destination, uint8_t operand1, uint8_t operand2) {
            registers[destination] = registers[operand1] - registers[operand2];
            setResultFlags(registers[destination]);
        }

        template <typename tdata>
        void multiply(tdata registers[], uint8_t destination, uint8_t operand1, uint8_t operand2) {
            registers[destination] = registers[operand1] * registers[operand2];
            setResultFlags(registers[destination]);
        }

        template <typename tdata>
        void divide(tdata registers[], uint8_t destination, uint8_t operand1, uint8_t operand2) {
            registers[destination] = registers[operand1] / registers[operand2];
            setResultFlags(registers[destination]);
        }

        template <typename tdata>
        void setLiteral(tdata registers[], uint8_t destination, tdata data) {
            registers[destination] = data;
            setResultFlags(registers[destination]);
        }

        template <typename tdata>
        Error pushStack(tdata value) {
            auto newStackPointer = stackPointer_ - sizeof(value);

            if(newStackPointer < interface_->getMaxMemory() - options_->getStackSize()) {
                return Error(ErrorCategory::Memory, ErrorDetail::StackOverflow);
            }

            stackPointer_ = newStackPointer;
            return interface_->write(stackPointer_, value);
        }

        template <typename tdata>
        ErrorUnion<tdata> popStack() {
            return scrapeStack<tdata>(true);
        }

        template <typename tdata>
        void increment(tdata registers[], uint8_t destination) {
            registers[destination]++;

            setResultFlags(registers[destination]);
        }

        template <typename tdata>
        void decrement(tdata registers[], uint8_t destination) {
            registers[destination]--;

            setResultFlags(registers[destination]);
        }

#pragma region instructions
        Error noOp();
        Error add(uint8_t instruction[]);
        Error subtract(uint8_t instruction[]);
        Error multiply(uint8_t instruction[]);
        Error divide(uint8_t instruction[]);
        Error setLiteral(uint8_t instruction[]);
        Error jump(uint8_t instruction[]);
        Error ret(uint8_t instruction[]);
        Error increment(uint8_t instruction[]);
        Error decrement(uint8_t instruction[]);
#pragma endregion instructions
    };
}

#endif //__CORE_H__