#include <nvmCore_test/BasicTestFixture.h>
#include <nvmCore/RegisterTypes.h>
#include <tuple>

#define MATH_TEST(INST, REGCAM, REGLOW, REGTYPE)                                                \
typedef std::tuple<REGTYPE, REGTYPE, REGTYPE, nvm::test::ExpectFlags> INST ## REGCAM ## Params; \
class INST ## REGCAM :                                                                          \
    public nvm::test::BasicTestFixture,                                                         \
    public ::testing::WithParamInterface<INST ## REGCAM  ## Params> { };                        \
                                                                                                \
TEST_P(INST ## REGCAM, INST ## REGCAM) {                                                        \
    auto param = GetParam();                                                                    \
                                                                                                \
    nvm::address_t address = 0;                                                                 \
    nvm::address_t size = sizeof(std::get<0>(param));                                           \
    iface_->write(address++, nvm::Instruction::SetLiteral);                                     \
    iface_->write<uint8_t>(address++, (nvm::RegisterType::REGLOW << 4) | 0x00);                 \
    iface_->write(address, std::get<0>(param));                                                 \
    address += size;                                                                            \
                                                                                                \
    iface_->write(address++, nvm::Instruction::SetLiteral);                                     \
    iface_->write<uint8_t>(address++, (nvm::RegisterType::REGLOW << 4) | 0x01);                 \
    iface_->write(address, std::get<1>(param));                                                 \
    address += size;                                                                            \
                                                                                                \
    iface_->write(address++, nvm::Instruction::INST);                                           \
    iface_->write<uint8_t>(address++, (nvm::RegisterType::REGLOW << 4) | 0x02);                 \
    iface_->write<uint8_t>(address, 0x01);                                                      \
                                                                                                \
    processIterations(3);                                                                       \
    auto result = core_.get ## REGCAM ## Register(2);                                           \
                                                                                                \
    EXPECT_EQ(std::get<2>(param), result);                                                      \
    std::get<3>(param).verify(core_);                                                           \
}                                                                                               \

#define MATH_ALL(INST)                \
MATH_TEST(INST, Ui8, ui8, uint8_t)    \
MATH_TEST(INST, I8, i8, int8_t)       \
MATH_TEST(INST, Ui16, ui16, uint16_t) \
MATH_TEST(INST, I16, i16, int16_t)    \
MATH_TEST(INST, Ui32, ui32, uint32_t) \
MATH_TEST(INST, I32, i32, int32_t)    \
MATH_TEST(INST, F32, f32, f32_t)      \
MATH_TEST(INST, F64, f64, f64_t)      \

#define FLAGS(FL) nvm::test::ExpectFlags(#FL)
