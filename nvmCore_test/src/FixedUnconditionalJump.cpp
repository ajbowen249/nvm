#include <nvmCore_test/TestMacros.h>

class FixUnconditionalJumpTest : public nvm::test::BasicTestFixture { };

TEST_F(FixUnconditionalJumpTest, BasicTest) {
    nvm::address_t address = 0;
    iface_->write(address++, nvm::Instruction::SetLiteral);
    iface_->write<uint8_t>(address++, (nvm::RegisterType::ui16 << 4) | 0x00);
    iface_->write(address, 0x02AA);
    address += 2;

    iface_->write(address++, nvm::Instruction::FixedUnconditionalJump);
    iface_->write<uint8_t>(address++, (nvm::RegisterType::ui16 << 4) | 0x00);

    processIterations(2);
    EXPECT_EQ(0x02AA, core_.getInstructionPointer());
}

TEST_F(FixUnconditionalJumpTest, Float32Error) {
    nvm::address_t address = 0;
    iface_->write(address++, nvm::Instruction::FixedUnconditionalJump);
    iface_->write<uint8_t>(address++, (nvm::RegisterType::f32 << 4) | 0x00);

    auto err = core_.process();
    EXPECT_TRUE((bool)err);
}

TEST_F(FixUnconditionalJumpTest, Float64Error) {
    nvm::address_t address = 0;
    iface_->write(address++, nvm::Instruction::FixedUnconditionalJump);
    iface_->write<uint8_t>(address++, (nvm::RegisterType::f64 << 4) | 0x00);

    auto err = core_.process();
    EXPECT_TRUE((bool)err);
}

TEST_F(FixUnconditionalJumpTest, NegativeToEnd) {
    nvm::address_t address = 0;
    iface_->write(address++, nvm::Instruction::SetLiteral);
    iface_->write<uint8_t>(address++, (nvm::RegisterType::i8 << 4) | 0x00);
    iface_->write<int8_t>(address++, -1);

    iface_->write(address++, nvm::Instruction::FixedUnconditionalJump);
    iface_->write<uint8_t>(address++, (nvm::RegisterType::i8 << 4) | 0x00);

    processIterations(2);
    EXPECT_EQ(iface_->getMaxMemory(), core_.getInstructionPointer());
}

TEST_F(FixUnconditionalJumpTest, Overflow1) {
    nvm::address_t address = 0;
    iface_->write(address++, nvm::Instruction::SetLiteral);
    iface_->write<uint8_t>(address++, (nvm::RegisterType::i16 << 4) | 0x00);
    iface_->write<int16_t>(address, 1024);
    address += 2;

    iface_->write(address++, nvm::Instruction::FixedUnconditionalJump);
    iface_->write<uint8_t>(address++, (nvm::RegisterType::i16 << 4) | 0x00);

    processIterations(2);
    EXPECT_EQ(0, core_.getInstructionPointer());
}

TEST_F(FixUnconditionalJumpTest, Overflow2) {
    nvm::address_t address = 0;
    iface_->write(address++, nvm::Instruction::SetLiteral);
    iface_->write<uint8_t>(address++, (nvm::RegisterType::ui32 << 4) | 0x00);
    iface_->write<int32_t>(address, 2123456789);
    address += 4;

    iface_->write(address++, nvm::Instruction::FixedUnconditionalJump);
    iface_->write<uint8_t>(address++, (nvm::RegisterType::ui32 << 4) | 0x00);

    processIterations(2);
    EXPECT_EQ(277, core_.getInstructionPointer());
}
