#include <nvmCore_test/TestMacros.h>

class JumpTest : public nvm::test::BasicTestFixture { };

TEST_F(JumpTest, UnconditionalPositiveLiteral) {
    nvm::address_t address = 0;
    iface_->write(address++, nvm::Instruction::Jump);
    iface_->write(address++, 0x00);
    iface_->write<nvm::address_t>(address, 0x02FF);

    processIterations(1);
    EXPECT_EQ(0x02FF, core_.getInstructionPointer());
}

TEST_F(JumpTest, UnconditionalNegativeLiteral) {
    nvm::address_t address = 0;
    iface_->write(address++, nvm::Instruction::Jump);
    iface_->write(address++, 0x28);
    iface_->write<nvm::address_t>(address, 2);
    address += 2;

    processIterations(1);
    EXPECT_EQ(address - 2, core_.getInstructionPointer());
}

TEST_F(JumpTest, UnconditionalPositiveRelativeLiteral) {
    nvm::address_t address = 0;
    iface_->write(address++, nvm::Instruction::Jump);
    iface_->write(address++, 0x20);
    iface_->write<nvm::address_t>(address, 15);
    address += 2;

    processIterations(1);
    EXPECT_EQ(address + 15, core_.getInstructionPointer());
}

TEST_F(JumpTest, UnconditionalRegisterUi8) {
    auto ui80 = (nvm::RegisterType::ui8 << 4) | 0x00;

    nvm::address_t address = 0;
    iface_->write(address++, nvm::Instruction::SetLiteral);
    iface_->write<uint8_t>(address++, ui80);
    iface_->write<uint8_t>(address++, 0xFF);

    iface_->write(address++, nvm::Instruction::Jump);
    iface_->write(address++, 0x10);
    iface_->write<uint8_t>(address++, ui80);

    processIterations(2);
    EXPECT_EQ(0x00FF, core_.getInstructionPointer());
}

TEST_F(JumpTest, UnconditionalRegisterRelativeI8Negative) {
    auto i80 = (nvm::RegisterType::i8 << 4) | 0x00;

    nvm::address_t address = 0;
    iface_->write(address++, nvm::Instruction::SetLiteral);
    iface_->write<uint8_t>(address++, i80);
    iface_->write<int8_t>(address++, -3);

    iface_->write(address++, nvm::Instruction::Jump);
    iface_->write(address++, 0x30);
    iface_->write<uint8_t>(address++, i80);

    processIterations(2);
    EXPECT_EQ(address - 3, core_.getInstructionPointer());
}

TEST_F(JumpTest, UnconditionalRegisterI8NegativeError) {
    auto i80 = (nvm::RegisterType::i8 << 4) | 0x00;

    nvm::address_t address = 0;
    iface_->write(address++, nvm::Instruction::SetLiteral);
    iface_->write<uint8_t>(address++, i80);
    iface_->write<int8_t>(address++, -3);

    iface_->write(address++, nvm::Instruction::Jump);
    iface_->write(address++, 0x10);
    iface_->write<uint8_t>(address++, i80);

    core_.process();
    auto error = core_.process();
    EXPECT_TRUE((bool)error);
}

TEST_F(JumpTest, UnconditionalRegisterI32) {
    auto i325 = (nvm::RegisterType::i32 << 4) | 0x05;

    nvm::address_t address = 0;
    iface_->write(address++, nvm::Instruction::SetLiteral);
    iface_->write<uint8_t>(address++, i325);
    iface_->write<int32_t>(address, 1000);
    address += 4;

    iface_->write(address++, nvm::Instruction::Jump);
    iface_->write(address++, 0x10);
    iface_->write<uint8_t>(address++, i325);

    processIterations(2);
    EXPECT_EQ(1000, core_.getInstructionPointer());
}

TEST_F(JumpTest, F32Error) {
    nvm::address_t address = 0;
    iface_->write(address++, nvm::Instruction::Jump);
    iface_->write(address++, 0x10);
    iface_->write<uint8_t>(address++, (nvm::RegisterType::f32 << 4) | 0x05);

    auto error = core_.process();
    EXPECT_TRUE((bool)error);
}

TEST_F(JumpTest, JumpPositive) {
    nvm::address_t address = 0;
    iface_->write(address++, nvm::Instruction::SetLiteral);
    iface_->write<uint8_t>(address++, (nvm::RegisterType::ui8 << 4) | 0x00);
    iface_->write<uint8_t>(address++, 0x01);

    iface_->write(address++, nvm::Instruction::Jump);
    iface_->write(address++, 0xC0);
    iface_->write<nvm::address_t>(address, 0x02FF);
    address += 2;

    processIterations(2);
    EXPECT_EQ(0x02FF, core_.getInstructionPointer());
}

TEST_F(JumpTest, DontJumpPositive) {
    nvm::address_t address = 0;
    iface_->write(address++, nvm::Instruction::SetLiteral);
    iface_->write<uint8_t>(address++, (nvm::RegisterType::ui8 << 4) | 0x00);
    iface_->write<uint8_t>(address++, 0x00);

    iface_->write(address++, nvm::Instruction::Jump);
    iface_->write(address++, 0xC0);
    iface_->write<nvm::address_t>(address, 0x02FF);
    address += 2;

    processIterations(2);
    EXPECT_EQ(address, core_.getInstructionPointer());
}

TEST_F(JumpTest, JumpNegative) {
    nvm::address_t address = 0;
    iface_->write(address++, nvm::Instruction::SetLiteral);
    iface_->write<uint8_t>(address++, (nvm::RegisterType::i8 << 4) | 0x00);
    iface_->write<int8_t>(address++, -1);

    iface_->write(address++, nvm::Instruction::Jump);
    iface_->write(address++, 0x40);
    iface_->write<nvm::address_t>(address, 0x02FF);
    address += 2;

    processIterations(2);
    EXPECT_EQ(0x02FF, core_.getInstructionPointer());
}

TEST_F(JumpTest, DontJumpNegative) {
    nvm::address_t address = 0;
    iface_->write(address++, nvm::Instruction::SetLiteral);
    iface_->write<uint8_t>(address++, (nvm::RegisterType::i8 << 4) | 0x00);
    iface_->write<int8_t>(address++, 0x00);

    iface_->write(address++, nvm::Instruction::Jump);
    iface_->write(address++, 0x40);
    iface_->write<nvm::address_t>(address, 0x02FF);
    address += 2;

    processIterations(2);
    EXPECT_EQ(address, core_.getInstructionPointer());
}

TEST_F(JumpTest, JumpZero) {
    nvm::address_t address = 0;
    iface_->write(address++, nvm::Instruction::SetLiteral);
    iface_->write<uint8_t>(address++, (nvm::RegisterType::i8 << 4) | 0x00);
    iface_->write<int8_t>(address++, 0);

    iface_->write(address++, nvm::Instruction::Jump);
    iface_->write(address++, 0x80);
    iface_->write<nvm::address_t>(address, 0x02FF);
    address += 2;

    processIterations(2);
    EXPECT_EQ(0x02FF, core_.getInstructionPointer());
}

TEST_F(JumpTest, DontJumpZero) {
    nvm::address_t address = 0;
    iface_->write(address++, nvm::Instruction::SetLiteral);
    iface_->write<uint8_t>(address++, (nvm::RegisterType::i8 << 4) | 0x00);
    iface_->write<int8_t>(address++, 1);

    iface_->write(address++, nvm::Instruction::Jump);
    iface_->write(address++, 0x80);
    iface_->write<nvm::address_t>(address, 0x02FF);
    address += 2;

    processIterations(2);
    EXPECT_EQ(address, core_.getInstructionPointer());
}

TEST_F(JumpTest, UnconditionalSubroutine) {
    nvm::address_t address = 0;
    iface_->write(address++, nvm::Instruction::Jump);
    iface_->write(address++, 0x04);
    iface_->write<nvm::address_t>(address, 0x02FF);
    address += 2;

    processIterations(1);
    EXPECT_EQ(0x02FF, core_.getInstructionPointer());

    auto stackPeek = core_.peekStack<nvm::address_t>();
    EXPECT_FALSE(stackPeek.error_);
    EXPECT_EQ(stackPeek.data_, address);
}
