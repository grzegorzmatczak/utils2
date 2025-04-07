#include "gtest/gtest.h"
#include "gmock/gmock.h" 

using ::testing::AtLeast;

namespace gtest_loggerthread
{
    class GTest_loggerthread : public ::testing::Test
    {
        protected:
            GTest_loggerthread(){}
            ~GTest_loggerthread() override {}
            void SetUp() override{}
            void TearDown() override {}
    };
}  // namespace gtest_loggerthread
