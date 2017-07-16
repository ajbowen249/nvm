#ifndef __CORE_H__
#define __CORE_H__

/*
The core implementation of the 
*/

#include "Options.h"
#include "Error.h"

namespace nvm {
    class Core {
    public:
        Error initialize(Interface::Ptr machineInterface, Options::Ptr options);
        Error process();

    private:
        Interface::Ptr interface_;

		int8_t i8Registers_[NUMGPREGS];
		uint8_t ui8Registers_[NUMGPREGS];
		int16_t i16Registers_[NUMGPREGS];
		uint16_t ui16Registers_[NUMGPREGS];
		int32_t i32Registers_[NUMGPREGS];
		uint32_t ui32Registers_[NUMGPREGS];
		f32_t f32Registers_[NUMGPREGS];
		f64_t f64Registers_[NUMGPREGS];

		address_t instructionPointer_;
		address_t stackPointer_;
    };
}

#endif //__CORE_H__