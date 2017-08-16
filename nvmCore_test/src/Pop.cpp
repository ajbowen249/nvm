#include <nvmCore_test/TestMacros.h>

class PopTest : public nvm::test::BasicTestFixture { };

TEST_F(PopTest, PopI8) {
    nvm::address_t address = 0;
    iface_->write(address++, nvm::Instruction::SetLiteral);
    iface_->write(address++, (nvm::RegisterType::i8 << 4) | 0x00);
    iface_->write<int8_t>(address++, -123);

    iface_->write(address++, nvm::Instruction::Push);
    iface_->write(address++, (nvm::RegisterType::i8 << 4) | 0x00);

    iface_->write(address++, nvm::Instruction::Pop);
    iface_->write(address++, (nvm::RegisterType::i8 << 4) | 0x01);

    processIterations(3);

    EXPECT_EQ(-123, core_.getI8Register(1));
    FLAGS(N).verify(core_);
}

TEST_F(PopTest, PopF64) {
    nvm::address_t address = 0;
    iface_->write(address++, nvm::Instruction::SetLiteral);
    iface_->write(address++, (nvm::RegisterType::f64 << 4) | 0x00);
    iface_->write<f64_t>(address, 1.2345);
    address += 8;

    iface_->write(address++, nvm::Instruction::Push);
    iface_->write(address++, (nvm::RegisterType::f64 << 4) | 0x00);

    iface_->write(address++, nvm::Instruction::Pop);
    iface_->write(address++, (nvm::RegisterType::f64 << 4) | 0x01);

    processIterations(3);

    EXPECT_EQ(1.2345, core_.getF64Register(1));
    FLAGS(P).verify(core_);
}

TEST_F(PopTest, PopError1) {
    nvm::address_t address = 0;
    iface_->write(address++, nvm::Instruction::Pop);
    iface_->write(address++, (nvm::RegisterType::i8 << 4) | 0x00);

    auto processError = core_.process();
    EXPECT_TRUE((bool)processError);
    EXPECT_EQ(nvm::ErrorDetail::StackUnderflow, processError.detail_);
}

TEST_F(PopTest, PopError2) {
    nvm::address_t address = 0;
    iface_->write(address++, nvm::Instruction::Push);
    iface_->write(address++, (nvm::RegisterType::i8 << 4) | 0x00);

    //There's an I8 on the stack, but not enough bytes for an F64.
    iface_->write(address++, nvm::Instruction::Pop);
    iface_->write(address++, (nvm::RegisterType::f64 << 4) | 0x00);

    core_.process();
    auto processError = core_.process();
    EXPECT_TRUE((bool)processError);
    EXPECT_EQ(nvm::ErrorDetail::StackUnderflow, processError.detail_);
}
