#include <nvmCore_test/TestMacros.h>

class PushTest : public nvm::test::BasicTestFixture { };

TEST_F(PushTest, PushI8) {
    nvm::address_t address = 0;
    iface_->write(address++, nvm::Instruction::SetLiteral);
    iface_->write(address++, (nvm::RegisterType::i8 << 4) | 0x00);
    iface_->write<int8_t>(address++, -123);

    iface_->write(address++, nvm::Instruction::Push);
    iface_->write(address++, (nvm::RegisterType::i8 << 4) | 0x00);

    processIterations(2);

    auto stackPeek = core_.peekStack<int8_t>();
    EXPECT_FALSE(stackPeek.error_);
    EXPECT_EQ(stackPeek.data_, -123);
}

TEST_F(PushTest, PushF64) {
    nvm::address_t address = 0;
    iface_->write(address++, nvm::Instruction::SetLiteral);
    iface_->write(address++, (nvm::RegisterType::f64 << 4) | 0x00);
    iface_->write<f64_t>(address, 1.2345);
    address += 8;

    iface_->write(address++, nvm::Instruction::Push);
    iface_->write(address++, (nvm::RegisterType::f64 << 4) | 0x00);

    processIterations(2);

    auto stackPeek = core_.peekStack<f64_t>();
    EXPECT_FALSE(stackPeek.error_);
    EXPECT_EQ(stackPeek.data_, 1.2345);
}
