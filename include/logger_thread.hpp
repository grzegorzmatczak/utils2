#pragma once

#include "logger.hpp"
#include "utils2_global.h"

#include <mutex>

namespace logger
{
    using namespace logger;
    class UTILS2_SHARED LoggerThread : private Logger
    {
    public:
        LoggerThread();
        LoggerThread(LogType type, LogLevel level, LogFunction logFunction);
        void showThreadIdThreaded(bool enabled = true);
        void printThreaded(const QString& msg, LogLevel level, const QString& functionStr);
        void printThreadedError(const QString& msg, LogLevel level, const QString& functionStr);
        void printThreadedStartFunction(LogLevel level, const QString& functionStr);
        void printThreadedEndFunction(LogLevel level, const QString& functionStr);
    private:
        std::mutex mutex;
    };

} // namespace logger
