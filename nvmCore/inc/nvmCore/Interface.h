#ifndef __INTERFACE_H__
#define __INTERFACE_H__

/*
Abstract interface for implementing  IO capabilities per-platform.
*/

#include "TargetConfig.h"
#include "Error.h"
#include <memory>

namespace nvm {
    class Interface {
    public:
        typedef std::shared_ptr<Interface> Ptr;

        template <typename tdata>
        Error write(address_t address, tdata data) {
            if (address > getMaxMemory()) {
                return nvm::Error(nvm::ErrorCategory::Memory, nvm::ErrorDetail::AddressOutOfRange);
            }

            return write(address, (uint8_t*)(&data), sizeof(data));
        }

        template <typename tdata>
        ErrorUnion<tdata> read(address_t address) {
            if (address > getMaxMemory()) {
                return nvm::Error(nvm::ErrorCategory::Memory, nvm::ErrorDetail::AddressOutOfRange);
            }

            uint8_t data[sizeof(tdata)];
            auto readError = read(address, data, sizeof(tdata));
            if (readError) return ErrorUnion<tdata>(readError);

            return ErrorUnion<tdata>(*(tdata*)(data));
        }

        virtual address_t getMaxMemory() const = 0;

    protected:
        virtual Error write(address_t address, const uint8_t data[], address_t width) = 0;
        virtual Error read(address_t address, uint8_t data[], address_t width) = 0;
    };
}

#endif //__INTERFACE_H__
