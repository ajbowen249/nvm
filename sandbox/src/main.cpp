#include <iostream>
#include <inMemoryInterface/InMemoryInterface.h>
#include <nvmCore/Core.h>

int main(int argc, char** argv) {
    nvm::Interface::Ptr iface(new nvm::InMemoryInterface(12));
    nvm::Options::Ptr options(new nvm::Options());
    nvm::Core core;
    core.initialize(iface, options);

    std::cout << "hello!" << std::endl;
}
