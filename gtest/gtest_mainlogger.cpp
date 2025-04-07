#include "gtest_mainlogger.hpp"

#include <QDebug>

#include "mainlogger.hpp"

using ::testing::AtLeast;

namespace gtest_mainlogger
{

    TEST_F(GTest_mainlogger, test_1)
    {	
        QString name1{"myFile.log"};
        QString name2{"myFileD.log"};
        MainLogger::start(name1, name2);
        qDebug("test MainLogger");
        qWarning("test MainLogger warning");
    }

}  // namespace gtest_mainlogger
