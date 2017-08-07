#include <nvmCore_test/TestMacros.h>

class FixedLiteralUnconditionalJumpTest : public nvm::test::BasicTestFixture { };

TEST_F(FixedLiteralUnconditionalJumpTest, BasicTest) {
    iface_->write(0, nvm::Instruction::FixedLiteralUnconditionalJump);
    iface_->write<nvm::address_t>(1, 0x1FF);

    processIterations(1);
    EXPECT_EQ(0x1FF, core_.getInstructionPointer());
}

TEST_F(FixedLiteralUnconditionalJumpTest, OutOfRange) {
    iface_->write(0, nvm::Instruction::FixedLiteralUnconditionalJump);
    iface_->write<nvm::address_t>(1, 1025);

    auto error = core_.process();
    EXPECT_TRUE((bool)error);
}
