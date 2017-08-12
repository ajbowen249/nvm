#include <nvmCore_test/TestMacros.h>

class ReadTest : public nvm::test::BasicTestFixture { };

TEST_F(ReadTest, ReadI8FromLiteral) {
    nvm::address_t readFromAddress = 0x02AA;
    iface_->write<int8_t>(readFromAddress, -123);

    nvm::address_t address = 0;
    iface_->write(address++, nvm::Instruction::Read);
    iface_->write(address++, (nvm::RegisterType::i8 << 4) | 0x00);
    iface_->write(address++, 0x00);
    iface_->write<nvm::address_t>(address, readFromAddress);
    address += 2;

    processIterations(1);
    EXPECT_EQ(-123, core_.getI8Register(0));
}

TEST_F(ReadTest, ReadUI32FromRegister) {
    nvm::address_t readFromAddress = 0x0123;
    iface_->write<uint32_t>(readFromAddress, 2123456789);

    nvm::address_t address = 0;
    iface_->write(address++, nvm::Instruction::SetLiteral);
    iface_->write(address++, (nvm::RegisterType::ui16 << 4) | 0x00);
    iface_->write(address, readFromAddress);
    address += 2;

    iface_->write(address++, nvm::Instruction::Read);
    iface_->write(address++, (nvm::RegisterType::ui32 << 4) | 0x00);
    iface_->write(address++, 0x83);
    iface_->write(address++, 0x00);

    processIterations(2);
    EXPECT_EQ(-2123456789, core_.getUi32Register(0));
}

TEST_F(ReadTest, ReadF64FromAddedRegisters) {
    nvm::address_t readFromAddress1 = 0x0012;
    nvm::address_t readFromAddress2 = 0x0023;
    iface_->write<f64_t>(readFromAddress1 + readFromAddress2, 123.456);

    nvm::address_t address = 0;
    iface_->write(address++, nvm::Instruction::SetLiteral);
    iface_->write(address++, (nvm::RegisterType::ui16 << 4) | 0x01);
    iface_->write(address, readFromAddress1);
    address += 2;

    iface_->write(address++, nvm::Instruction::SetLiteral);
    iface_->write(address++, (nvm::RegisterType::ui16 << 4) | 0x02);
    iface_->write(address, readFromAddress2);
    address += 2;

    iface_->write(address++, nvm::Instruction::Read);
    iface_->write(address++, (nvm::RegisterType::f64 << 4) | 0x00);
    iface_->write(address++, 0xC3);
    iface_->write(address++, 0x12);

    processIterations(3);
    EXPECT_EQ(123.456, core_.getF64Register(0));
}

TEST_F(ReadTest, LiteralError) {
    nvm::address_t readFromAddress = 0xFFFF;

    nvm::address_t address = 0;
    iface_->write(address++, nvm::Instruction::Read);
    iface_->write(address++, (nvm::RegisterType::i8 << 4) | 0x00);
    iface_->write(address++, 0x00);
    iface_->write<nvm::address_t>(address, readFromAddress);
    address += 2;

    auto error = core_.process();
    EXPECT_TRUE((bool)error);
    EXPECT_EQ(nvm::ErrorDetail::AddressOutOfRange, error.detail_);
}

TEST_F(ReadTest, RegisterError1) {
    nvm::address_t readFromAddress = 0xFFFF;

    nvm::address_t address = 0;
    iface_->write(address++, nvm::Instruction::SetLiteral);
    iface_->write(address++, (nvm::RegisterType::ui16 << 4) | 0x00);
    iface_->write(address, readFromAddress);
    address += 2;

    iface_->write(address++, nvm::Instruction::Read);
    iface_->write(address++, (nvm::RegisterType::ui32 << 4) | 0x00);
    iface_->write(address++, 0x83);
    iface_->write(address++, 0x00);

    processIterations(1);
    auto error = core_.process();
    EXPECT_TRUE((bool)error);
    EXPECT_EQ(nvm::ErrorDetail::AddressOutOfRange, error.detail_);
}

TEST_F(ReadTest, RegisterError2) {
    nvm::address_t address = 0;
    iface_->write(address++, nvm::Instruction::Read);
    iface_->write(address++, (nvm::RegisterType::ui32 << 4) | 0x00);
    iface_->write(address++, 0x86);
    iface_->write(address++, 0x00);

    auto error = core_.process();
    EXPECT_TRUE((bool)error);
    EXPECT_EQ(nvm::ErrorDetail::UnsupportedRegister, error.detail_);
}

TEST_F(ReadTest, RegisterAddError) {
    nvm::address_t readFromAddress1 = 0x0200;
    nvm::address_t readFromAddress2 = 0x0201;
    iface_->write<f64_t>(readFromAddress1 + readFromAddress2, 123.456);

    nvm::address_t address = 0;
    iface_->write(address++, nvm::Instruction::SetLiteral);
    iface_->write(address++, (nvm::RegisterType::ui16 << 4) | 0x01);
    iface_->write(address, readFromAddress1);
    address += 2;

    iface_->write(address++, nvm::Instruction::SetLiteral);
    iface_->write(address++, (nvm::RegisterType::ui16 << 4) | 0x02);
    iface_->write(address, readFromAddress2);
    address += 2;

    iface_->write(address++, nvm::Instruction::Read);
    iface_->write(address++, (nvm::RegisterType::f64 << 4) | 0x00);
    iface_->write(address++, 0xC3);
    iface_->write(address++, 0x12);

    processIterations(2);
    auto error = core_.process();
    EXPECT_TRUE((bool)error);
    EXPECT_EQ(nvm::ErrorDetail::AddressOutOfRange, error.detail_);
}
