//Copyright 2025 HWorldY
//the Apache License, Version 2.0
//Author: HWorldY
#ifndef PLUGINMANAGER_H
#define PLUGINMANAGER_H
#include "wpluginmanager_global.h"
#include "wpluginmetadata.h"
#include <QObject>
#include <QPluginLoader>
#include <QVariant>

class WPluginManagerPrivate;
class WPLUGINMANAGERSHARED_EXPORT WPluginManager : public QObject
{
    Q_OBJECT
public:

    WPluginManager();
    ~WPluginManager();

    static WPluginManager *instance();

    //加载所有插件
    void loadAllPlugins();

    //扫描JSON文件中的插件元数据
    void scanMetaData(const QString &filepath);
    //加载其中某个插件
    void loadPlugin(const QString &filepath);
    //卸载所有插件
    void unloadAllPlugins();
    //卸载某个插件
    void unloadPlugin(const QString &filepath);
    //获取所有插件
    QList<QPluginLoader *> allPlugins();
    //获取某个插件
    QPluginLoader* getPlugin(const QString &name);
    //获取所有插件名称
    QList<QString> allPluginsName();
    //获取某个插件名称
    QVariant getPluginName(QPluginLoader *loader);

    QVariant getMetaData(QPluginLoader *loader, QString item);
private:
    static WPluginManager *m_instance;
    WPluginManagerPrivate *d;

private slots:
    void recMsgFromManager(WPluginMetaData&);

};

#endif
