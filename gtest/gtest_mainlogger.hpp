#include "gtest/gtest.h"
#include "gmock/gmock.h" 

#include <QDebug>



using ::testing::AtLeast;

namespace gtest_mainlogger
{
	class GTest_mainlogger : public ::testing::Test
	{
		protected:
			GTest_mainlogger(){}
			~GTest_mainlogger() override {}
			void SetUp() override{}
			void TearDown() override {}
	};
}  // namespace gtest_mainlogger
