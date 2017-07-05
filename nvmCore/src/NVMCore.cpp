#include "nvmCore/NVMCore.h"

nvm::NVMCore::NVMCore(nvm::NVMInterface::Ptr machineInterface) :
    interface_(machineInterface) { }

void nvm::NVMCore::process() {
    //do nothing yet
}
