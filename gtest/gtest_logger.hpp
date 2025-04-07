#include "gtest/gtest.h"
#include "gmock/gmock.h" 

using ::testing::AtLeast;

namespace gtest_logger
{
    class GTest_logger : public ::testing::Test
    {
        protected:
            GTest_logger(){}
            ~GTest_logger() override {}
            void SetUp() override{}
            void TearDown() override {}
    };
}  // namespace gtest_logger
