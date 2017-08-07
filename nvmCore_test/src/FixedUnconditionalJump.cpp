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
