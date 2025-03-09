#include "configreader.hpp"

#include "logger.hpp"

ConfigReader::ConfigReader()
{
    mLogger = std::make_unique<logger::Logger>(logger::LogType::CONFIG, logger::LogLevel::MEDIUM, logger::LogFunction::YES);
}

ConfigReader::~ConfigReader() {}

QJsonObject ConfigReader::readObjectConfig(const QString& configPathWithName)
{
    QJsonObject obj;
    readConfig(configPathWithName, obj);
    return obj;
}

bool ConfigReader::readConfig(const QString& configPathWithName, QJsonObject& obj) 
{
    mLogger->print(configPathWithName, logger::LogType::CONFIG, logger::LogLevel::LOW, __FUNCTION__);

    QFile jConfigFile{ configPathWithName };
    if (!jConfigFile.open(QIODevice::ReadOnly))
    {
        QString err = QString("Can not open json file:%1").arg(configPathWithName);
        mLogger->printError(err, __FUNCTION__);
        return false;
    }

    QJsonDocument jConfigDoc{ QJsonDocument::fromJson((jConfigFile.readAll())) };
    if (!jConfigDoc.isObject())
    {
        QString err = QString("Invalid json config file:%1").arg(configPathWithName);
        mLogger->printError(err, __FUNCTION__);
        return false;
    }
    
    obj = { jConfigDoc.object() };

    return true;
}

QJsonArray ConfigReader::readArrayConfig(const QString& configPathWithName)
{
    QJsonArray arr;
    readConfig(configPathWithName, arr);
    return arr;
}

bool ConfigReader::readConfig(const QString& configPathWithName, QJsonArray& obj) 
{
    mLogger->printStartFunction(__FUNCTION__);
    QFile jConfigFile{ configPathWithName };
    if (!jConfigFile.open(QIODevice::ReadOnly))
    {
        QString err = QString("Can not open json file:%1").arg(configPathWithName);
        mLogger->printError(err, __FUNCTION__);
        return false;
    }

    QJsonDocument jConfigDoc{ QJsonDocument::fromJson((jConfigFile.readAll())) };
    if (!jConfigDoc.isArray())
    {
        QString err = QString("Invalid json config file:%1").arg(configPathWithName);
        mLogger->printError(err, __FUNCTION__);
        return false;
    }
    
    obj = { jConfigDoc.array() };

    return true;
}
