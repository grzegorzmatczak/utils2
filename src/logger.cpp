#include "logger.hpp"


#include <stdio.h>
#include <stdlib.h>

Logger::Logger()
{}

Logger::Logger(LogType type)
: mType(type)
{}

Logger::Logger(LogLevel level)
: mLevel(level)
{}

Logger::Logger(LogType type, LogLevel level)
: mType(type), mLevel(level)
{}

void Logger::print(QString& msg)
{
    print(msg, mType, mLevel);
}

void Logger::print(QString& msg, LogType type)
{
    print(msg, type, mLevel);
}

void Logger::print(QString& msg, LogLevel level)
{
    print(msg, mType, level);
}

void Logger::print(QString& msg, LogType type, LogLevel level)
{
    if(level <= mLevel)
        qDebug("[%s] %s", qPrintable(fromType(type)), qPrintable(msg));
}

QString Logger::fromType(LogType type)
{
    switch (type)
    {
        case LogType::VIEW :
            return "view";
        case LogType::SCENE :
            return "scene";
        case LogType::PAINTER :
            return "painter";
        
        default:
            break;
    }
}