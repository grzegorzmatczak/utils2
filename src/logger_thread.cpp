#include "logger_thread.hpp"

#include <QDebug>
#include <QThread>
#include <QCoreApplication>
#include <stdio.h>
#include <stdlib.h>


namespace logger
{

LoggerThread::LoggerThread()
{}

LoggerThread::LoggerThread(LogType type, LogLevel level, LogFunction logFunction)
: logger::Logger(type, level, logFunction)
{}

void LoggerThread::showThreadIdThreaded(bool enabled)
{
    Logger::showThreadId(enabled);
}

void LoggerThread::printThreaded(const QString& msg, LogLevel level, const QString& functionStr)
{
    mutex.lock();
    print(msg, level, functionStr);
    mutex.unlock();
}

void LoggerThread::printThreadedError(const QString& msg, LogLevel level, const QString& functionStr)
{
    mutex.lock();
    printError(msg, level, functionStr);
    mutex.unlock();
}

void LoggerThread::printThreadedStartFunction(const LogLevel level, const QString& functionStr)
{
    mutex.lock();
    printStartFunction(level, functionStr);
    mutex.unlock();
}

void LoggerThread::printThreadedEndFunction(const LogLevel level, const QString& functionStr)
{
    mutex.lock();
    printEndFunction(level, functionStr);
    mutex.unlock();
}

} // namespace logger
