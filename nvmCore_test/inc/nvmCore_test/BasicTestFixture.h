#ifndef __BASICTESTFIXTURE_H__
#define __BASICTESTFIXTURE_H__

#include "gtest/gtest.h"
#include <inMemoryInterface/InMemoryInterface.h>
#include <testSupport/ObservableCore.h>
#include <string>

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

        class ExpectFlags {
        public:
           ExpectFlags(const std::string& flags);
           void verify(const ObservableCore& core);

        private:
           bool n_;
           bool z_;
           bool p_;
           bool c_;
           bool b_;
        };
    }
}

#endif //__BASICTESTFIXTURE_H__