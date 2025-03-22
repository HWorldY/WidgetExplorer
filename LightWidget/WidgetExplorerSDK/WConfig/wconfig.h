//Copyright 2025 HWorldY
//the Apache License, Version 2.0
//Author: HWorldY
#ifndef WCONFIG_H
#define WCONFIG_H
#include<QString>
#include<QMap>
#include<QVariant>
#include<QFile>
#include<QJsonDocument>
#include<QJsonObject>
#include<QJsonArray>
#include<QJsonValue>
#include<QTextStream>
#include<QDir>
class WConfig
{
	public:
	WConfig();
	~WConfig();
	void readConfig();
	void setConfig(QString key,QVariant value);
	QVariant getConfig(QString key);
	private:
		QMap<QString,QVariant> config;
};

#endif // WCONFIG_H
