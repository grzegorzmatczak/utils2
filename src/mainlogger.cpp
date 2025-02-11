#include "mainlogger.hpp"

#include <QtGlobal>

#include <QDateTime>
#include <QByteArray>
#include <QFile>

#include <stdio.h>
#include <stdlib.h>
QString MainLogger::mFileName;
QString MainLogger::mFileNameDebug;

void myMessageOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    
    QTime time = QTime::currentTime();
    QString formattedTime = time.toString("hh:mm:ss.zzz");
    QByteArray formattedTimeMsg = formattedTime.toLocal8Bit();

    QByteArray msgData = ("[" + formattedTimeMsg + "]" + msg + "\r\n").toStdString().c_str();
    if(!MainLogger::mFileName.isEmpty())
    {
        QFile file(MainLogger::mFileName);
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

void MainLogger::start(QString& fileName, QString& fileNameDebug)
{
    MainLogger::mFileName = fileName;
    MainLogger::mFileNameDebug = fileNameDebug;
    
    //QString messagePattern = QStringLiteral("%{message}");
    //messagePattern.prepend(QStringLiteral("[%{time hh:mm:ss.zzz}][%{threadid}]"));
    //qSetMessagePattern(messagePattern);
    qInstallMessageHandler(myMessageOutput); // Install the handler
}