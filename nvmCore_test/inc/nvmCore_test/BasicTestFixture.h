#ifndef __BASICTESTFIXTURE_H__
#define __BASICTESTFIXTURE_H__

#include "gtest/gtest.h"
#include <inMemoryInterface/InMemoryInterface.h>
#include <testSupport/ObservableCore.h>

namespace nvm {
    namespace test {
        class BasicTestFixture : public ::testing::Test {
        protected:
            Interface::Ptr iface_;
            InMemoryInterface* inMemoryInterface_;
            ObservableCore core_;

            BasicTestFixture();
            virtual void SetUp();
            void processIterations(int iterations);
        };
    }
}

#endif //__BASICTESTFIXTURE_H__