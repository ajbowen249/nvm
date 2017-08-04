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
