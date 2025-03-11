#pragma once

#include "global.h"
#include <stdio.h>


namespace logger
{
    class Logger;
}

class UTILS2_SHARED ConfigReader : public QObject
{
    public:
        ConfigReader();
        ~ConfigReader();
        bool readConfig(const QString& configPathWithName, QJsonObject& obj);
        bool readConfig(const QString& configPathWithName, QJsonArray& obj);
        QJsonObject readObjectConfig(const QString& configPathWithName);
        QJsonArray readArrayConfig(const QString& configPathWithName);

    private:
        std::unique_ptr<logger::Logger> mLogger;

};
