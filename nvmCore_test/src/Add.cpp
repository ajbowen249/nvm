#include "gtest/gtest.h"
#include <inMemoryInterface/InMemoryInterface.h>
#include <nvmCore/Core.h>

TEST(Add, add1) {
    nvm::Interface::Ptr iface(new nvm::InMemoryInterface(1024));
    nvm::Options::Ptr options(new nvm::Options());
    nvm::Core core;
    core.initialize(iface, options);
    core.reset();

    //Set up for 112 + 58
    iface->write(0x0000, 0x05);// set literal
    iface->write(0x0001, 0x10);// ui8-0
    iface->write(0x0002, 0x70);// value 112

    iface->write(0x0003, 0x05);// set literal
    iface->write(0x0004, 0x11);// ui8-1
    iface->write(0x0005, 0x3A);// value 58

    iface->write(0x0006, 0x01);// add
    iface->write(0x0007, 0x12);// ui8-2
    iface->write(0x0008, 0x01);// 0|1

    //should take exactly 3 process cycles
    core.process();
    core.process();
    core.process();

    EXPECT_TRUE(false);
}
