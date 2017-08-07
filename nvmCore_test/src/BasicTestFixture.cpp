#include <nvmCore_test/BasicTestFixture.h>

nvm::test::BasicTestFixture::BasicTestFixture() :
    iface_(new nvm::InMemoryInterface(1024)) {
    inMemoryInterface_ = (nvm::InMemoryInterface*)(iface_.get());

    nvm::Options::Ptr options(new nvm::Options());
    core_.initialize(iface_, options);
}

void nvm::test::BasicTestFixture::SetUp() {
    core_.reset();
}

void nvm::test::BasicTestFixture::processIterations(int iterations) {
    for (int i = 0; i < iterations; i++) {
        core_.process();
    }
}

nvm::test::ExpectFlags::ExpectFlags(const std::string& flags) :
    n_(false),
    z_(false),
    p_(false) {
   for(auto c : flags) {
       switch (c){
       case 'N':
           n_ = true;
           break;
       case 'Z':
           z_ = true;
           break;
       case 'P':
           p_ = true;
           break;
       default:
           break;
       }
   }
}

void nvm::test::ExpectFlags::verify(const ObservableCore& core) {
    EXPECT_EQ(n_, core.getNegativeFlag());
    EXPECT_EQ(z_, core.getZeroFlag());
    EXPECT_EQ(p_, core.getPositiveFlag());
}
