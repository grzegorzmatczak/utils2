#pragma once

#include <QString>

class MainLogger
{
	public:
		static void start(QString& fileName, QString& fileNameDebug);
		friend void myMessageOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg);
	private:
		static QString mFileName;
		static QString mFileNameDebug;

};