#pragma once

#include "global.h"

namespace logger
{
    enum LogType
    {
        VIEW,
        SCENE,
        CONFIG,
        PAINTER,
        PAINTER_SETTINGS,
        CAMERA_CAPTURE,
        CAMERA_THREAD,
        FRAME_PROCESSING,
        FRAME_MEDIAN,
        FRAME_SOURCE,
        FRAME_READER,
        SERVICE,
        PROCESSING,
        GRAPH
    };

    enum LogLevel
    {
        NO_LOGS = 0,
        HIGH = 1,
        MEDIUM = 2,
        LOW = 3
    };

    enum LogFunction
    {
        YES,
        NO
    };

    class UTILS2_SHARED Logger
    {
    public:
        Logger();
        Logger(LogType type, LogLevel level, LogFunction logFunction);

        void showThreadId(bool enabled = true);

        void print(const QString& msg);
        void print(const QString& msg, LogLevel level);
        void print(const QString& msg, LogType type);
        void print(const QString& msg, const QString& functionStr);
        void print(const QString& msg, LogLevel level, const QString& functionStr);
        void print(const QString& msg, LogType type, LogLevel level);
        void print(const QString& msg, LogType type, LogLevel level, const QString& functionStr);

        void printError(const QString& msg);
        void printError(const QString& msg, const QString& functionStr);
        void printError(const QString& msg, LogType type, LogLevel level);
        void printError(const QString& msg, LogType type, LogLevel level, const QString& functionStr);

        void printStartFunction(const QString& functionStr);
        void printStartFunction(const QString& functionStr, LogLevel level);
        void printStartFunction(LogType type, LogLevel level, const QString& functionStr);

        void printEndFunction(const QString& functionStr);
        void printEndFunction(const QString& functionStr, LogLevel level);
        void printEndFunction(LogType type, LogLevel level, const QString& functionStr);

    private:
        QString fromType(LogType type);


    private:
        LogType mType{ VIEW };
        LogLevel mLevel{ LOW };
        LogFunction isLogFunction{ NO };
        bool isShowThreadId{ false };
    };

} // namespace logger
