#ifndef __INMEMORYINTERFACE_H__
#define __INMEMORYINTERFACE_H__

#include <nvmCore/Interface.h>
#include <vector>

namespace nvm {
    class InMemoryInterface: public Interface {
    public:
        InMemoryInterface(address_t memorySize);
        virtual address_t getMaxMemory() const override;

        //Publicised this for sake of large block-writes
        virtual Error write(address_t address, const uint8_t data[], address_t width) override;

    protected:
        address_t maxAddress_;
        std::vector<uint8_t> memory_;

        virtual Error read(address_t address, uint8_t data[], address_t width) override;
    };
}

#endif //__INMEMORYINTERFACE_H__
