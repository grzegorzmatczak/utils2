#include "logger.hpp"

#include <QtGlobal>

#include <QDateTime>
#include <QByteArray>
#include <QFile>

#include <stdio.h>
#include <stdlib.h>

QString Logger::mFileName;
QString Logger::mFileNameDebug;

void myMessageOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    QTime time = QTime::currentTime();
    QString formattedTime = time.toString("hh:mm:ss.zzz");
    QByteArray formattedTimeMsg = formattedTime.toLocal8Bit();

    QByteArray msgData = formattedTimeMsg + (" " + msg + "\r\n").toStdString().c_str();
    if(!Logger::mFileName.isEmpty())
    {
        QFile file(Logger::mFileName);
        if(file.open(QIODevice::Append| QIODevice::WriteOnly))
        {
            file.write(msgData.constData(), msgData.length());
        }
        file.close();
    }

    #ifdef _WIN32
    fprintf(stderr, "%s", msgData.constData());
    fflush(stderr);
    #else   
    //linux
    #endif
}

void Logger::start(QString& fileName, QString& fileNameDebug)
{
    Logger::mFileName = fileName;
    Logger::mFileNameDebug = fileNameDebug;
    qInstallMessageHandler(myMessageOutput); // Install the handler
}