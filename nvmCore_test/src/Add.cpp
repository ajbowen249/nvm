#include "gtest/gtest.h"
#include <inMemoryInterface/InMemoryInterface.h>
#include <testSupport/ObservableCore.h>
#include <nvmCore/Core.h>

TEST(Add, add1) {
    nvm::Interface::Ptr iface(new nvm::InMemoryInterface(1024));
    auto inMemoryInterface = (nvm::InMemoryInterface*)(iface.get());

    nvm::Options::Ptr options(new nvm::Options());
    nvm::ObservableCore core;
    core.initialize(iface, options);
    core.reset();

    //112 + 58
    uint8_t program[] = {
        0x05, // set literal
        0x10, // ui8-0
        0x70, // value 112

        0x05, // set literal
        0x11, // ui8-1
        0x3A, // value 58

        0x01, // add
        0x12, // ui8-2
        0x01, // 0|1
    };

    inMemoryInterface->write(0, program, 9);

    //should take exactly 3 process cycles
    core.process();
    core.process();
    core.process();

    auto result = core.getUi8Register(2);

    EXPECT_EQ(170, result);
}
