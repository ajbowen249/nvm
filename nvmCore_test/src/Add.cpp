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

//TODO:: Add expectations for flags

INSTANTIATE_TEST_CASE_P(addUI8,
    AddUI8Test,
    ::testing::Values(
        UI8AddTestParams(1, 2, 3),
        UI8AddTestParams(58, 197, 255),
        UI8AddTestParams(1, 255, 0),
        UI8AddTestParams(15, 255, 14)
    )
);

INSTANTIATE_TEST_CASE_P(addI8,
    AddI8Test,
    ::testing::Values(
        I8AddTestParams(1, 2, 3),
        I8AddTestParams(1, -2, -1),
        I8AddTestParams(127, -255, -128),
        I8AddTestParams(127, 1, -128),
        I8AddTestParams(-128, -1, 127)
    )
);

INSTANTIATE_TEST_CASE_P(addUI16,
    AddUI16Test,
    ::testing::Values(
        UI16AddTestParams(1, 2, 3),
        UI16AddTestParams(65535, 1, 0),
        UI16AddTestParams(65279, 512, 255)
    )
);

INSTANTIATE_TEST_CASE_P(addI16,
    AddI16Test,
    ::testing::Values(
        I16AddTestParams(1, 2, 3),
        I16AddTestParams(123, -23, 100),
        I16AddTestParams(-15, 16, 1),
        I16AddTestParams(32767, 1, -32768),
        I16AddTestParams(-32768, -1, 32767)
    )
);

INSTANTIATE_TEST_CASE_P(addUI32,
    AddUI32Test,
    ::testing::Values(
        UI32AddTestParams(1, 2, 3),
        UI32AddTestParams(4294967295, 1, 0),
        UI32AddTestParams(4294967039, 512, 255)
    )
);

INSTANTIATE_TEST_CASE_P(addI32,
    AddI32Test,
    ::testing::Values(
        I32AddTestParams(1, 2, 3),
        I32AddTestParams(123, -23, 100),
        I32AddTestParams(2147483647, 1, -2147483648),
        I32AddTestParams(-2147483648, -1, 2147483647)
    )
);

INSTANTIATE_TEST_CASE_P(addF32,
    AddF32Test,
    ::testing::Values(
        F32AddTestParams(1, 2, 3),
        F32AddTestParams(1.5, 1.5, 3),
        F32AddTestParams(10, -20, -10),
        F32AddTestParams(0, 0, 0)
    )
);

INSTANTIATE_TEST_CASE_P(addF64,
    AddF64Test,
    ::testing::Values(
        F64AddTestParams(1, 2, 3),
        F64AddTestParams(9007199254740991, -1234, 9007199254739757),
        F64AddTestParams(1.5, -3, -1.5),
        F64AddTestParams(0, 0, 0)
    )
);
