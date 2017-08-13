#include <nvmCore_test/TestMacros.h>

class WriteTest : public nvm::test::BasicTestFixture { };

TEST_F(WriteTest, WriteI8ToLiteral) {
    nvm::address_t writeToAddress = 0x02AA;

    nvm::address_t address = 0;
    iface_->write(address++, nvm::Instruction::SetLiteral);
    iface_->write(address++, (nvm::RegisterType::i8 << 4) | 0x00);
    iface_->write<int8_t>(address++, -123);

    iface_->write(address++, nvm::Instruction::Write);
    iface_->write(address++, (nvm::RegisterType::i8 << 4) | 0x00);
    iface_->write(address++, 0x00);
    iface_->write<nvm::address_t>(address, writeToAddress);
    address += 2;

    processIterations(2);
    EXPECT_EQ(-123, iface_->read<int8_t>(writeToAddress).data_);
}

TEST_F(WriteTest, WriteUI32ToRegister) {
    nvm::address_t writeToAddress = 0x0123;

    nvm::address_t address = 0;
    iface_->write(address++, nvm::Instruction::SetLiteral);
    iface_->write(address++, (nvm::RegisterType::ui16 << 4) | 0x00);
    iface_->write(address, writeToAddress);
    address += 2;

    iface_->write(address++, nvm::Instruction::SetLiteral);
    iface_->write(address++, (nvm::RegisterType::ui32 << 4) | 0x00);
    iface_->write<uint32_t>(address, 2123456789);
    address += 4;

    iface_->write(address++, nvm::Instruction::Write);
    iface_->write(address++, (nvm::RegisterType::ui32 << 4) | 0x00);
    iface_->write(address++, 0x83);
    iface_->write(address++, 0x00);

    processIterations(3);
    EXPECT_EQ(2123456789, iface_->read<uint32_t>(writeToAddress).data_);
}

TEST_F(WriteTest, WriteF64ToAddedRegisters) {
    nvm::address_t writeToAddress1 = 0x0012;
    nvm::address_t writeToAddress2 = 0x0023;

    nvm::address_t address = 0;
    iface_->write(address++, nvm::Instruction::SetLiteral);
    iface_->write(address++, (nvm::RegisterType::ui16 << 4) | 0x01);
    iface_->write(address, writeToAddress1);
    address += 2;

    iface_->write(address++, nvm::Instruction::SetLiteral);
    iface_->write(address++, (nvm::RegisterType::ui16 << 4) | 0x02);
    iface_->write(address, writeToAddress2);
    address += 2;

    iface_->write(address++, nvm::Instruction::SetLiteral);
    iface_->write(address++, (nvm::RegisterType::f64 << 4) | 0x00);
    iface_->write<f64_t>(address, 123.456);
    address += 8;

    iface_->write(address++, nvm::Instruction::Write);
    iface_->write(address++, (nvm::RegisterType::f64 << 4) | 0x00);
    iface_->write(address++, 0xC3);
    iface_->write(address++, 0x12);

    processIterations(4);
    EXPECT_EQ(123.456, iface_->read<f64_t>(writeToAddress1 + writeToAddress2).data_);
}

TEST_F(WriteTest, LiteralError1) {
    nvm::address_t writeToAddress = 0xFFFF;

    nvm::address_t address = 0;
    iface_->write(address++, nvm::Instruction::Write);
    iface_->write(address++, (nvm::RegisterType::i8 << 4) | 0x00);
    iface_->write(address++, 0x00);
    iface_->write<nvm::address_t>(address, writeToAddress);
    address += 2;

    auto error = core_.process();
    EXPECT_TRUE((bool)error);
    EXPECT_EQ(nvm::ErrorDetail::AddressOutOfRange, error.detail_);
}

TEST_F(WriteTest, LiteralError2) {
    nvm::address_t writeToAddress = 0x03FD;

    nvm::address_t address = 0;
    iface_->write(address++, nvm::Instruction::Write);
    iface_->write(address++, (nvm::RegisterType::ui32 << 4) | 0x00);
    iface_->write(address++, 0x00);
    iface_->write<nvm::address_t>(address, writeToAddress);
    address += 2;

    auto error = core_.process();
    EXPECT_TRUE((bool)error);
    EXPECT_EQ(nvm::ErrorDetail::AddressOutOfRange, error.detail_);
}

TEST_F(WriteTest, RegisterError1) {
    nvm::address_t writeToAddress = 0xFFFF;

    nvm::address_t address = 0;
    iface_->write(address++, nvm::Instruction::SetLiteral);
    iface_->write(address++, (nvm::RegisterType::ui16 << 4) | 0x00);
    iface_->write(address, writeToAddress);
    address += 2;

    iface_->write(address++, nvm::Instruction::Write);
    iface_->write(address++, (nvm::RegisterType::ui32 << 4) | 0x00);
    iface_->write(address++, 0x83);
    iface_->write(address++, 0x00);

    processIterations(1);
    auto error = core_.process();
    EXPECT_TRUE((bool)error);
    EXPECT_EQ(nvm::ErrorDetail::AddressOutOfRange, error.detail_);
}

TEST_F(WriteTest, RegisterError2) {
    nvm::address_t address = 0;
    iface_->write(address++, nvm::Instruction::Write);
    iface_->write(address++, (nvm::RegisterType::ui32 << 4) | 0x00);
    iface_->write(address++, 0x86);
    iface_->write(address++, 0x00);

    auto error = core_.process();
    EXPECT_TRUE((bool)error);
    EXPECT_EQ(nvm::ErrorDetail::UnsupportedRegister, error.detail_);
}

TEST_F(WriteTest, RegisterAddError) {
    nvm::address_t writeToAddress1 = 0x0200;
    nvm::address_t writeToAddress2 = 0x0201;
    iface_->write<f64_t>(writeToAddress1 + writeToAddress2, 123.456);

    nvm::address_t address = 0;
    iface_->write(address++, nvm::Instruction::SetLiteral);
    iface_->write(address++, (nvm::RegisterType::ui16 << 4) | 0x01);
    iface_->write(address, writeToAddress1);
    address += 2;

    iface_->write(address++, nvm::Instruction::SetLiteral);
    iface_->write(address++, (nvm::RegisterType::ui16 << 4) | 0x02);
    iface_->write(address, writeToAddress2);
    address += 2;

    iface_->write(address++, nvm::Instruction::Write);
    iface_->write(address++, (nvm::RegisterType::f64 << 4) | 0x00);
    iface_->write(address++, 0xC3);
    iface_->write(address++, 0x12);

    processIterations(2);
    auto error = core_.process();
    EXPECT_TRUE((bool)error);
    EXPECT_EQ(nvm::ErrorDetail::AddressOutOfRange, error.detail_);
}
