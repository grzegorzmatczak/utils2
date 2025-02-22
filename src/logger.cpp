#include "logger.hpp"

#include <QDebug>
#include <QThread>
#include <QCoreApplication>
#include <stdio.h>
#include <stdlib.h>


namespace logger
{
Logger::Logger()
{}

Logger::Logger(LogType type, LogLevel level, LogFunction logFunction)
: mType(type), mLevel(level), isLogFunction(logFunction)
{}

void Logger::showThreadId(bool enabled)
{
    isShowThreadId = enabled;
}

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

void Logger::print(const QString& msg, LogLevel level, const QString& functionStr)
{
    print(msg, mType, level, functionStr);
}

void Logger::print(const QString& msg, LogType type, LogLevel level)
{
    if(level <= mLevel)
        qDebug("[%s] %s", qPrintable(fromType(type)), qPrintable(msg));
}

void Logger::print(const QString& msg, LogType type, LogLevel level, const QString& functionStr)
{
    if(isLogFunction == LogFunction::YES && level <= mLevel)
        qDebug("[%s][%s()] %s", qPrintable(fromType(type)), qPrintable(functionStr), qPrintable(msg));
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
        qCritical("\033[1;31m[%s] %s\033[0m", qPrintable(fromType(type)), qPrintable(msg));
}

void Logger::printError(const QString& msg, LogType type, LogLevel level, const QString& functionStr)
{
    if(isLogFunction == LogFunction::YES && level <= mLevel)
        qCritical("\033[1;31m[%s][%s()] %s\033[0m", qPrintable(fromType(type)), qPrintable(functionStr), qPrintable(msg));
    else if(level <= mLevel)
        qCritical("\033[1;31m[%s] %s\033[0m", qPrintable(fromType(type)), qPrintable(msg));
}

void Logger::printStartFunction(const QString& functionStr)
{
    printStartFunction(mType, mLevel, functionStr);
}

void Logger::printStartFunction(const QString& functionStr, LogLevel level)
{
    printStartFunction(mType, level, functionStr);
}

void Logger::printStartFunction(LogType type, LogLevel level, const QString& functionStr)
{
    if (isLogFunction == LogFunction::YES && level <= mLevel && isShowThreadId == true)
        qDebug() << QString("[%1][").arg(qPrintable(fromType(type))) << QThread::currentThreadId() << QString("][%1()]").arg(qPrintable(functionStr));
    if(isLogFunction == LogFunction::YES && level <= mLevel)
        qDebug("[%s][%s()]", qPrintable(fromType(type)), qPrintable(functionStr));
    else if(level <= mLevel)
        qDebug("[%s]", qPrintable(fromType(type)));
}

void Logger::printEndFunction(const QString& functionStr)
{
    printEndFunction(mType, mLevel, functionStr);
}

void Logger::printEndFunction(const QString& functionStr, LogLevel level)
{
    printEndFunction(mType, level, functionStr);
}

void Logger::printEndFunction(LogType type, LogLevel level, const QString& functionStr)
{
    if (isLogFunction == LogFunction::YES && level <= mLevel && isShowThreadId == true)
        qDebug() << QString("[%1][").arg(qPrintable(fromType(type))) << QThread::currentThreadId() << QString("][%1()] done").arg(qPrintable(functionStr));
    if(isLogFunction == LogFunction::YES && level <= mLevel)
        qDebug("[%s][%s()] done", qPrintable(fromType(type)), qPrintable(functionStr));
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
        case LogType::CAMERA_CAPTURE:
            return "CAMERA_CAPTURE";
        case LogType::SERVICE:
            return "SERVICE";
        case LogType::CAMERA_THREAD:
            return "CAMERA_THREAD";
        case LogType::FRAME_PROCESSING:
            return "FRAME_PROCESSING";
        case LogType::FRAME_MEDIAN:
            return "FRAME_MEDIAN";
        case LogType::FRAME_SOURCE:
            return "FRAME_SOURCE";
        case LogType::FRAME_READER:
            return "FRAME_READER";
        default:
            return "";
    }
    return "";
}

} // namespace logger
