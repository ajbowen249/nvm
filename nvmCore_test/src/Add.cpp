#include "gtest/gtest.h"
#include <inMemoryInterface/InMemoryInterface.h>
#include <testSupport/ObservableCore.h>
#include <nvmCore/Core.h>
#include <tuple>

typedef std::tuple<uint8_t, uint8_t, uint8_t> UI8AddTestParams;
class AddTest : public ::testing::TestWithParam<UI8AddTestParams> {
protected:
    nvm::Interface::Ptr iface_;
    nvm::InMemoryInterface* inMemoryInterface_;
    nvm::ObservableCore core_;

    AddTest() : 
        iface_(new nvm::InMemoryInterface(1024)) {
        inMemoryInterface_ = (nvm::InMemoryInterface*)(iface_.get());

        UI8AddTestParams x(1, 2, 3);

        nvm::Options::Ptr options(new nvm::Options());
        core_.initialize(iface_, options);
    }

    virtual void SetUp() {
        core_.reset();
    }
};

TEST_P(AddTest, addui8) {
    auto param = GetParam();
    uint8_t program[] = {
        0x05, // set literal
        0x10, // ui8-0
        std::get<0>(param), // Operand 1

        0x05, // set literal
        0x11, // ui8-1
        std::get<1>(param), // Operand 1

        0x01, // add
        0x12, // ui8-2
        0x01, // 0|1
    };

    inMemoryInterface_->write(0, program, 9);

    //should take exactly 3 process cycles
    core_.process();
    core_.process();
    core_.process();

    auto result = core_.getUi8Register(2);

    EXPECT_EQ(std::get<2>(param), result);
}

INSTANTIATE_TEST_CASE_P(addui8,
    AddTest,
    ::testing::Values(
        UI8AddTestParams(1, 2, 3),
        UI8AddTestParams(58, 197, 255),
        UI8AddTestParams(1, 255, 0), //TODO:: Expect carry flag
        UI8AddTestParams(15, 255, 14) //TODO:: Expect carry flag
    )
);
