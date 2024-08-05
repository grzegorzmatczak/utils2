#pragma once

#include <stdio.h>
#include <QJsonObject>
#include <QJsonArray>
#include <QFile>
#include <QJsonDocument>

class Logger;


class ConfigReader : public QObject
{
	public:
		ConfigReader();
		~ConfigReader();
		bool readConfig(const QString& configPathWithName, QJsonObject& obj);
		bool readConfig(const QString& configPathWithName, QJsonArray& obj);

	private:
		std::unique_ptr<Logger> mLogger;

};
