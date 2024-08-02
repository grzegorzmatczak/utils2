#pragma once

#include <QString>

class Logger
{
	public:
		static void start(QString& fileName, QString& fileNameDebug);
		friend void myMessageOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg);
	private:
		static QString Logger::mFileName;
		static QString Logger::mFileNameDebug;

};