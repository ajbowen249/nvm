#include <nvmCore_test/TestMacros.h>

class FixedLiteralJumpNegativeTest : public nvm::test::BasicTestFixture { };

TEST_F(FixedLiteralJumpNegativeTest, BasicTestJump) {
    nvm::address_t address = 0;
    iface_->write(address++, nvm::Instruction::SetLiteral);
    iface_->write<uint8_t>(address++, (nvm::RegisterType::i8 << 4) | 0x00);
    iface_->write<int8_t>(address++, -1);

    iface_->write(address++, nvm::Instruction::FixedLiteralJumpNegative);
    iface_->write<nvm::address_t>(address++, 0x1FF);

    processIterations(2);
    EXPECT_EQ(0x1FF, core_.getInstructionPointer());
}

TEST_F(FixedLiteralJumpNegativeTest, BasicTestNoJump1) {
    nvm::address_t address = 0;
    iface_->write(address++, nvm::Instruction::SetLiteral);
    iface_->write<uint8_t>(address++, (nvm::RegisterType::i8 << 4) | 0x00);
    iface_->write<int8_t>(address++, 0);

    iface_->write(address++, nvm::Instruction::FixedLiteralJumpNegative);
    iface_->write<nvm::address_t>(address++, 0x1FF);

    processIterations(2);
    EXPECT_EQ(6, core_.getInstructionPointer());
}

TEST_F(FixedLiteralJumpNegativeTest, BasicTestNoJump2) {
    nvm::address_t address = 0;
    iface_->write(address++, nvm::Instruction::SetLiteral);
    iface_->write<uint8_t>(address++, (nvm::RegisterType::i8 << 4) | 0x00);
    iface_->write<int8_t>(address++, 0);

    iface_->write(address++, nvm::Instruction::FixedLiteralJumpNegative);
    iface_->write<nvm::address_t>(address++, 0x1FF);

    processIterations(2);
    EXPECT_EQ(6, core_.getInstructionPointer());
}

TEST_F(FixedLiteralJumpNegativeTest, OutOfRange) {
    nvm::address_t address = 0;
    iface_->write(address++, nvm::Instruction::SetLiteral);
    iface_->write<uint8_t>(address++, (nvm::RegisterType::i8 << 4) | 0x00);
    iface_->write<int8_t>(address++, -1);

    iface_->write(address++, nvm::Instruction::FixedLiteralJumpNegative);
    iface_->write<nvm::address_t>(address++, 1025);

    core_.process();
    auto error = core_.process();
    EXPECT_TRUE((bool)error);
}
