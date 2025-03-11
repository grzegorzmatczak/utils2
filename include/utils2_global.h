#pragma once
#include <QtCore/QtGlobal>
#include <QJsonObject>
#include <QJsonArray>
#include <QFile>
#include <QJsonDocument>
#include <QString>

#if defined(UTILS2_SHARED_ON)
#  define UTILS2_SHARED Q_DECL_EXPORT
#else
#  define UTILS2_SHARED Q_DECL_IMPORT
#endif