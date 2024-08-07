#include "logger.hpp"


#include <stdio.h>
#include <stdlib.h>

Logger::Logger()
{}

Logger::Logger(LogType type, LogLevel level, LogFunction logFunction)
: mType(type), mLevel(level), isLogFunction(logFunction)
{}

void Logger::print(const QString& msg)
{
    print(msg, mType, mLevel);
}

void Logger::print(const QString& msg, LogType type)
{
    print(msg, type, mLevel);
}

void Logger::print(const QString& msg, LogLevel level)
{
    print(msg, mType, level);
}

void Logger::print(const QString& msg, const QString& functionStr)
{
    print(msg, mType, mLevel, functionStr);
}

void Logger::print(const QString& msg, LogType type, LogLevel level)
{
    if(level <= mLevel)
        qDebug("[%s] %s", qPrintable(fromType(type)), qPrintable(msg));
}

void Logger::print(const QString& msg, LogType type, LogLevel level, const QString& functionStr)
{
    if(isLogFunction == LogFunction::YES && level <= mLevel)
        qDebug("[%s][%s]() %s", qPrintable(fromType(type)), qPrintable(functionStr), qPrintable(msg));
    else if(level <= mLevel)
        qDebug("[%s] %s", qPrintable(fromType(type)), qPrintable(msg));
}

void Logger::printError(const QString& msg)
{
    printError(msg, mType, mLevel);
}

void Logger::printError(const QString& msg, const QString& functionStr)
{
    printError(msg, mType, mLevel, functionStr);
}

void Logger::printError(const QString& msg, LogType type, LogLevel level)
{
    if(level <= mLevel)
        qDebug("[%s] %s", qPrintable(fromType(type)), qPrintable(msg));
}

void Logger::printError(const QString& msg, LogType type, LogLevel level, const QString& functionStr)
{
    if(isLogFunction == LogFunction::YES && level <= mLevel)
        qDebug("[%s][%s]() ", qPrintable(fromType(type)), qPrintable(functionStr));
    else if(level <= mLevel)
        qDebug("[%s] ", qPrintable(fromType(type)));
}



void Logger::printStartFunction(const QString& functionStr)
{
    printStartFunction(mType, mLevel, functionStr);
}

void Logger::printStartFunction(LogType type, LogLevel level, const QString& functionStr)
{
    if(isLogFunction == LogFunction::YES && level <= mLevel)
        qDebug("[%s][%s]()", qPrintable(fromType(type)), qPrintable(functionStr));
    else if(level <= mLevel)
        qDebug("[%s]", qPrintable(fromType(type)));
}

void Logger::printEndFunction(const QString& functionStr)
{
    printEndFunction(mType, mLevel, functionStr);
}

void Logger::printEndFunction(LogType type, LogLevel level, const QString& functionStr)
{
    if(isLogFunction == LogFunction::YES && level <= mLevel)
        qDebug("[%s][%s]() done", qPrintable(fromType(type)), qPrintable(functionStr));
    else if(level <= mLevel)
        qDebug("[%s] done", qPrintable(fromType(type)));
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
            return "";
    }
    return "";
}