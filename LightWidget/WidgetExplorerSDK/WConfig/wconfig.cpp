//Copyright 2025 HWorldY
//the Apache License, Version 2.0
//Author: HWorldY
#include "wconfig.h"
#include"../WFile/wpath.h"
#include"../we.h"

WConfig::WConfig()
{
}

WConfig::~WConfig()
{
}

void WConfig::readConfig()
{
    QFile file(WPath::getModuleFolder() + "config\\config.json");
    QString json="";
    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream in(&file);
        in.setEncoding(QStringConverter::Utf8);
        json=in.readAll();
        file.close();
	}
    QJsonParseError jsonError;
    QJsonDocument doc;
    doc = QJsonDocument::fromJson(json.toUtf8(), &jsonError);
    if (jsonError.error != QJsonParseError::NoError && !doc.isNull()) {
        qDebug() << "Json格式错误！" << jsonError.error;
        return;
    }
    QJsonObject obj = doc.object();
    // 根据键获取值
    for (auto it = obj.begin(); it != obj.end(); it++)
    {
        config[it.key()] = it.value().toVariant();
    }
    return;
}

void WConfig::setConfig(QString key, QVariant value)
{
	config[key] = value;
}

QVariant WConfig::getConfig(QString key)
{
	return config[key];
}
