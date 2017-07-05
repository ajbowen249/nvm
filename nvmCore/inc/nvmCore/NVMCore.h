#ifndef __NVMCORE_H__
#define __NVMCORE_H__

/*
The core implementation of the NVM
*/

#include "nvmCore/NVMInterface.h"

namespace nvm {
    class NVMCore {
    public:
        NVMCore(NVMInterface::Ptr machineInterface);
        void process();
    private:
        NVMInterface::Ptr interface_;
    };
}

#endif //__NVMCORE_H__