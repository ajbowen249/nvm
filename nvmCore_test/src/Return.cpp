#include <nvmCore_test/TestMacros.h>

class ReturnTest : public nvm::test::BasicTestFixture { };

TEST_F(ReturnTest, JumpAndReturn) {
    nvm::address_t address = 0;
    iface_->write(address++, nvm::Instruction::Jump);
    iface_->write(address++, 0x04);
    iface_->write<nvm::address_t>(address, 0x02FF);
    address += 2;

    iface_->write(0x02FF, nvm::Instruction::Return);
    
    processIterations(2);
    EXPECT_EQ(address, core_.getInstructionPointer());
}

TEST_F(ReturnTest, EmptyStack) {
    iface_->write(0, nvm::Instruction::Return);

    auto error = core_.process();
    EXPECT_TRUE((bool)error);
    EXPECT_EQ(error.detail_, nvm::ErrorDetail::StackUnderflow);
}
