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
        logger::Logger logger(logger::LogType::VIEW, logger::LogLevel::HIGH, logger::LogFunction::YES);
        logger.print(QString("test Logger"));
        QString str = QString("test Logger");
        logger.print(str);
        logger.print(str, logger::LogType::VIEW);

        logger::Logger logger2(logger::LogType::VIEW, logger::LogLevel::NO_LOGS, logger::LogFunction::YES);
        logger2.printStartFunction(__FUNCTION__);
        logger2.printEndFunction(__FUNCTION__);
        logger2.print(QString("NOLOGS"), logger::LogLevel::NO_LOGS);
        logger2.print(QString("ERROR - SHOULD NOT BE LOGED"), logger::LogLevel::HIGH);
    }

}  // namespace gtest_logger
