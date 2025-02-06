#include "gtest_configreader.hpp"

#include <QDir>

using ::testing::AtLeast;

namespace gtest_configreader {

    constexpr auto CONFIG{ "/gtest/test.json" };
    constexpr auto TEST_DATA{ "TestData" };

    TEST_F(GTest_configreader, test_readConfig)
    {
        ConfigReader * _configreader = new ConfigReader();
        QJsonObject obj{};
        QString path = QDir::currentPath() + CONFIG;
        _configreader->readConfig(path, obj);
        EXPECT_EQ (obj[TEST_DATA], 123);
    }

    TEST_F(GTest_configreader, test2)
    {
        QJsonObject _objReference{{TEST_DATA,123}};
        ConfigReader * _configreader = new ConfigReader();
        EXPECT_EQ (_objReference[TEST_DATA], 123);
    }
}  // namespace gtest_configreader
