//Copyright 2025 HWorldY
//the Apache License, Version 2.0
//Author: HWorldY
#ifndef WPLUGINMETADATA_H
#define WPLUGINMETADATA_H

#include <QObject>
#include <QVariant>
#include <QMap>
#include <QString>
/**
 * 插件间消息封装体
 **/
struct WPluginMetaData
{
    QString from;
    QString dest;
    int type;
    QMap<QString,QVariant> map;
    QObject *object = nullptr;
};
Q_DECLARE_METATYPE(WPluginMetaData);

#endif
