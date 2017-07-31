#include "gtest/gtest.h"
#include <inMemoryInterface/InMemoryInterface.h>
#include <testSupport/ObservableCore.h>
#include <nvmCore/Core.h>
#include <nvmCore/RegisterTypes.h>
#include <tuple>

class BasicTestFixture : public ::testing::Test {
protected:
    nvm::Interface::Ptr iface_;
    nvm::InMemoryInterface* inMemoryInterface_;
    nvm::ObservableCore core_;

    BasicTestFixture() :
        iface_(new nvm::InMemoryInterface(1024)) {
        inMemoryInterface_ = (nvm::InMemoryInterface*)(iface_.get());

        nvm::Options::Ptr options(new nvm::Options());
        core_.initialize(iface_, options);
    }

    virtual void SetUp() {
        core_.reset();
    }

    void processIterations(int iterations) {
        for (int i = 0; i < iterations; i++) {
            core_.process();
        }
    }
};

#define ADD_TEST(CLASS, TNAME, REGTYPE, GETRESREG, TYPE, PARAMSNAME)                         \
typedef std::tuple<TYPE, TYPE, TYPE> PARAMSNAME;                                             \
class CLASS : public BasicTestFixture, public ::testing::WithParamInterface<PARAMSNAME> { }; \
TEST_P(CLASS, TNAME) {                                                                       \
    auto param = GetParam();                                                                 \
                                                                                             \
    nvm::address_t address = 0;                                                              \
    nvm::address_t size = sizeof(std::get<0>(param));                                        \
    iface_->write(address++, nvm::Instruction::SetLiteral);                                  \
    iface_->write<uint8_t>(address++, (REGTYPE << 4) | 0x00);                                \
    iface_->write(address, std::get<0>(param));                                              \
    address += size;                                                                         \
                                                                                             \
    iface_->write(address++, nvm::Instruction::SetLiteral);                                  \
    iface_->write<uint8_t>(address++, (REGTYPE << 4) | 0x01);                                \
    iface_->write(address, std::get<1>(param));                                              \
    address += size;                                                                         \
                                                                                             \
    iface_->write(address++, nvm::Instruction::Add);                                         \
    iface_->write<uint8_t>(address++, (REGTYPE << 4) | 0x02);                                \
    iface_->write<uint8_t>(address, 0x01);                                                   \
                                                                                             \
    processIterations(3);                                                                    \
    auto result = core_.GETRESREG(2);                                                        \
                                                                                             \
    EXPECT_EQ(std::get<2>(param), result);                                                   \
}                                                                                            \

ADD_TEST(AddUI8Test, addUI8, nvm::RegisterType::ui8, getUi8Register, uint8_t, UI8AddTestParams)
ADD_TEST(AddI8Test, addI8, nvm::RegisterType::i8, getI8Register, int8_t, I8AddTestParams)
ADD_TEST(AddUI16Test, addUI16, nvm::RegisterType::ui16, getUi16Register, uint16_t, UI16AddTestParams)
ADD_TEST(AddI16Test, addI16, nvm::RegisterType::i16, getI16Register, int16_t, I16AddTestParams)
ADD_TEST(AddUI32Test, addUI32, nvm::RegisterType::ui32, getUi32Register, uint32_t, UI32AddTestParams)
ADD_TEST(AddI32Test, addI32, nvm::RegisterType::i32, getI32Register, int32_t, I32AddTestParams)
ADD_TEST(AddF32Test, addF32, nvm::RegisterType::f32, getF32Register, f32_t, F32AddTestParams)
ADD_TEST(AddF64Test, addF64, nvm::RegisterType::f64, getF64Register, f64_t, F64AddTestParams)

INSTANTIATE_TEST_CASE_P(addUI8,
    AddUI8Test,
    ::testing::Values(
        UI8AddTestParams(1, 2, 3),
        UI8AddTestParams(58, 197, 255),
        UI8AddTestParams(1, 255, 0), //TODO:: Expect carry flag
        UI8AddTestParams(15, 255, 14) //TODO:: Expect carry flag
    )
);

INSTANTIATE_TEST_CASE_P(addI8,
    AddI8Test,
    ::testing::Values(
        UI8AddTestParams(1, 2, 3),
        UI8AddTestParams(1, -2, -1),
        UI8AddTestParams(127, -255, -128),
        UI8AddTestParams(127, 1, -128), //TODO:: Expect carry flag
        UI8AddTestParams(-128, -1, 127) //TODO:: Expect borrow flag
    )
);

//TODO:: Add test cases for remaining types

INSTANTIATE_TEST_CASE_P(addUI16,
    AddUI16Test,
    ::testing::Values(
        UI8AddTestParams(1, 2, 3)
    )
);
