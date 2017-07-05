#ifndef __NVMINTERFACE_H__
#define __NVMINTERFACE_H__

/*
Abstract interface for implementing NVM IO capabilities per-platform.
*/

#include "nvmCore/TargetConfig.h"
#include <memory>

namespace nvm {
    class NVMInterface {
    public:
        typedef std::shared_ptr<NVMInterface> Ptr;

        virtual void writeWord(_address_t address, _uword_t word) = 0;
        virtual void writeWord(_address_t address, _word_t word) = 0;

        virtual void writeByte(_address_t address, _ui8_t byte) = 0;
        virtual void writeByte(_address_t address, _i8_t byte) = 0;

        virtual _uword_t readUWord(_address_t address) = 0;
        virtual _word_t readWord(_address_t address) = 0;

        virtual _ui8_t readUByte(_address_t address) = 0;
        virtual _i8_t readByte(_address_t address) = 0;
    };
}

#endif //__NVMINTERFACE_H__