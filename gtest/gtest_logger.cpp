#include "gtest_logger.hpp"

#include "logger.hpp"
#include "mainlogger.hpp"

using ::testing::AtLeast;

namespace gtest_logger
{
	TEST_F(GTest_logger, test_1)
	{	
		QString name1{"myFile.log"};
		QString name2{"myFileD.log"};
		MainLogger::start(name1, name2);
		logger::Logger logger(LogType::VIEW, LogLevel::HIGH, LogFunction::YES);
		logger.print(QString("test Logger"));
		QString str = QString("test Logger");
		logger.print(str);
		logger.print(str, LogType::VIEW);

		Logger logger2(LogType::VIEW, LogLevel::NO_LOGS, LogFunction::YES);
		logger2.printStartFunction(__FUNCTION__);
		logger2.printEndFunction(__FUNCTION__);
		logger2.print(QString("NOLOGS"), LogLevel::NO_LOGS);
		logger2.print(QString("ERROR - SHOULD NOT BE LOGED"), LogLevel::HIGH);
	}

}  // namespace gtest_logger
