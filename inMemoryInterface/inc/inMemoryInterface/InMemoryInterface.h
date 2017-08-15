#ifndef __INMEMORYINTERFACE_H__
#define __INMEMORYINTERFACE_H__

#include <nvmCore/Interface.h>

#ifndef INMEM_SIZE
#define INMEM_SIZE 1024
#endif

namespace nvm {
    class InMemoryInterface: public Interface {
    public:
        InMemoryInterface();
        virtual address_t getMaxMemory() const override;

        //Publicised this for sake of large block-writes
        virtual Error write(address_t address, const uint8_t data[], address_t width) override;

    protected:
        address_t maxAddress_;
        //This used to be a vector, but Arduino doesn't like it.
        uint8_t memory_[INMEM_SIZE];

        virtual Error read(address_t address, uint8_t data[], address_t width) override;
    };
}

#endif //__INMEMORYINTERFACE_H__
