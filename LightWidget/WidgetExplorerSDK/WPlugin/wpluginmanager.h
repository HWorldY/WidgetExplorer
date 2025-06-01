//Copyright 2025 HWorldY
//the Apache License, Version 2.0
//Author: HWorldY
#ifndef PLUGINMANAGER_H
#define PLUGINMANAGER_H
#include <QObject>
#include <QPluginLoader>
#include <QVariant>
#include"../WDef/wedef.h"
#include "../WPlugin/wpluginmetadata.h"

class WPluginManagerPrivate;
class WE_NAMESPACE::WPluginManager : public QObject
{
    Q_OBJECT
public:
    WPluginManager();
    virtual ~WPluginManager();

    bool loadPlugin(WPlugin *plugin);
    bool unloadPlugin(WPlugin* plugin);
    void unloadAllPlugins();

    QVector<QUuid> getPluginByAttr(QString key,QVariant value);
    QUuid getPluginByName(QString name);
    WPlugin* getPluginById(QUuid id);
    QVector<QUuid> allPluginsId();
    QVector<WPlugin*> allPluginsInst();

    QVariant setPluginData(QUuid id,QString key,QVariant value);
    QUuid getUuid(WPlugin* plugin);

private:
    WPlugin* createPlugin(QString configPath,QString config);
    bool unloadPlugin(QMap<QUuid,WPlugin*>::Iterator it);
    WPluginManagerPrivate* d=nullptr;
public slots:
    void sendMsg(WMetaData&);
};
Q_DECLARE_METATYPE(WE_NAMESPACE::WPluginManager)
Q_DECLARE_METATYPE(WE_NAMESPACE::WPluginManager*)
#endif
