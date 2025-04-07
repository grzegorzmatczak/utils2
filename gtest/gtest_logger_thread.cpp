#include "gtest_logger_thread.hpp"

#include <QDebug>

#include "logger_thread.hpp"
#include "mainlogger.hpp"

using ::testing::AtLeast;

namespace gtest_loggerthread
{
    TEST_F(GTest_loggerthread, test_1)
    {	
        QString name1{"myFile.log"};
        QString name2{"myFileD.log"};
        MainLogger::start(name1, name2);
        logger::LoggerThread logger(logger::LogType::VIEW, logger::LogLevel::HIGH, logger::LogFunction::YES);
        logger.printThreaded(QString("test Logger"), logger::LogLevel::HIGH, __FUNCTION__);
        logger.printThreadedError(QString("test Logger error"), logger::LogLevel::HIGH, __FUNCTION__);
        logger.printThreadedStartFunction(logger::LogLevel::HIGH, __FUNCTION__);
        logger.printThreadedEndFunction(logger::LogLevel::HIGH, __FUNCTION__);
        QString str = QString("test Logger");
        logger::LoggerThread logger2(logger::LogType::VIEW, logger::LogLevel::NO_LOGS, logger::LogFunction::YES);
    }

}  // namespace gtest_loggerthread
