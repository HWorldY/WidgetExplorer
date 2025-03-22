//Copyright 2025 HWorldY
//the Apache License, Version 2.0
//Author: HWorldY
#include "wpluginmanager.h"
#include "wpluginmanagerprivate.h"
#include "wplugininterface.h"
#include <QDir>
#include <QCoreApplication>
#include <QJsonArray>
#include <QDebug>

WPluginManager* WPluginManager::m_instance=nullptr;

WPluginManager::WPluginManager()
{
    d = new WPluginManagerPrivate();
}

WPluginManager::~WPluginManager()
{
    if(d)
        delete d;
}
WPluginManager* WPluginManager::instance(){{
        if(m_instance==nullptr)
            m_instance=new WPluginManager();
        return m_instance;
    }}
void WPluginManager::loadAllPlugins()
{
    QDir pluginsdir = QDir(qApp->applicationDirPath());
    pluginsdir.cd("widget");

    QFileInfoList pluginsInfo = pluginsdir.entryInfoList(QDir::Files | QDir::NoDotAndDotDot);
    //初始化插件中的元数据
    for(QFileInfo fileinfo : pluginsInfo)
        scanMetaData(fileinfo.absoluteFilePath());

    //加载插件
    for(QFileInfo fileinfo : pluginsInfo)
        loadPlugin(fileinfo.absoluteFilePath());
}

void WPluginManager::scanMetaData(const QString &filepath)
{
    //判断是否为库（后缀有效性）
    if(!QLibrary::isLibrary(filepath))
        return ;
    //获取元数据
    QPluginLoader *loader = new QPluginLoader(filepath);
    QJsonObject json = loader->metaData().value("MetaData").toObject();

    QVariant var = json.value("name").toVariant();
    d->m_names.insert(filepath, json.value("name").toVariant());
    d->m_authors.insert(filepath, json.value("author").toVariant());
    d->m_versions.insert(filepath, json.value("version").toVariant());
    d->m_dependencies.insert(filepath, json.value("dependencies").toArray().toVariantList());

    delete loader;
    loader = nullptr;
}

void WPluginManager::loadPlugin(const QString &filepath)
{
    if(!QLibrary::isLibrary(filepath))
        return;

    //检测依赖
    if(!d->check(filepath))
        return;

    //加载插件
    QPluginLoader *loader = new QPluginLoader(filepath);
    if(loader->load())
    {
        // 如果继承自 Plugin，则认为是自己的插件（防止外部插件注入）。
        WPluginInterface *plugin = qobject_cast<WPluginInterface *>(loader->instance());
        if(plugin)
        {
            d->m_loaders.insert(filepath, loader);
            plugin->connectTosendMsgToManager(this, SLOT(recMsgFromManager(WPluginMetaData&)), true);
        }
        else
        {
            delete loader;
            loader = nullptr;
        }
    }
}

void WPluginManager::unloadAllPlugins()
{
    for(QString filepath : d->m_loaders.keys())
        unloadPlugin(filepath);
}

void WPluginManager::unloadPlugin(const QString &filepath)
{
    QPluginLoader *loader = d->m_loaders.value(filepath);
    //卸载插件，并从内部数据结构中移除
    if(loader->unload())
    {
        d->m_loaders.remove(filepath);
        delete loader;
        loader = nullptr;
    }
}

QList<QPluginLoader *> WPluginManager::allPlugins()
{
    return d->m_loaders.values();
}

QPluginLoader* WPluginManager::getPlugin(const QString &name)
{
    return d->m_loaders.value(d->m_names.key(name));
}

QVariant WPluginManager::getPluginName(QPluginLoader *loader)
{
    if(loader)
        return d->m_names.value(d->m_loaders.key(loader));
    else
        return "";
}
QVariant WPluginManager::getMetaData(QPluginLoader *loader, QString item){
    if(loader){
        if(item=="name")return d->m_names.value(d->m_loaders.key(loader));
        else if(item=="author")return d->m_authors.value(d->m_loaders.key(loader));
        else if(item=="version")return d->m_versions.value(d->m_loaders.key(loader));
        else if(item=="path")return loader->fileName();
    }
    return "";
}
QList<QString> WPluginManager::allPluginsName(){
    auto l=allPlugins();
    QStringList list;
    for(auto it=l.begin();it!=l.end();it++){
        list+=getPluginName(*it).toString();
    }
    return list;
}
void WPluginManager:: recMsgFromManager(WPluginMetaData &msg)
{
     qDebug()  <<"WPluginManager::recMsgFromManager..."<< msg.dest;
     auto loader = getPlugin(msg.dest);
     if(loader)
     {
         auto plugin = qobject_cast<WPluginInterface*>(loader->instance());;
         if(plugin)
         {
             plugin->recMsgFromManager(msg);
         }
     }
}
