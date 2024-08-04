#pragma once

#include <QString>

enum LogType
{
	VIEW,
	SCENE,
	PAINTER
};

enum LogLevel
{
	NO_LOGS = 0,
	HIGH = 1,
	MEDIUM = 2,
	LOW = 3
};

class Logger
{
	public:
		Logger();
		Logger(LogType type);
		Logger(LogLevel level);
		Logger(LogType type, LogLevel level);

		void print(QString& msg);
		void print(QString& msg, LogLevel level);
		void print(QString& msg, LogType type);
		void print(QString& msg, LogType type, LogLevel level);

	private:
		QString fromType(LogType type);


	private:
		LogType mType{VIEW};
		LogLevel mLevel{LOW};
};

