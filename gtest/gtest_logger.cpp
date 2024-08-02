#include "gtest_logger.hpp"

#include "logger.hpp"

using ::testing::AtLeast;

namespace gtest_logger
{

	TEST_F(GTest_logger, test_1)
	{	
		QString name1{"myFile.log"};
		QString name2{"myFileD.log"};
		Logger::start(name1, name2);
		qDebug("[log] log to jest");
		qDebug("to jest log");
		qWarning("to jest log warn");
	}

}  // namespace gtest_logger
