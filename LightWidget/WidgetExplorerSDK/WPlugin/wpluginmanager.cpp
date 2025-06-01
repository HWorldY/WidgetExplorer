//Copyright 2025 HWorldY
//the Apache License, Version 2.0
//Author: HWorldY
#include "../WPlugin/wpluginmanager.h"
#include "../WPlugin/wplugininterface.h"
#include"../WPlugin/wplugin.h"

#include <QDir>
#include <QCoreApplication>
#include <QJsonArray>
#include <QHash>
#include <QVariant>
#include <QPluginLoader>
///
/// \brief The WPluginManagerPrivate class
///
class WPluginManagerPrivate
{
public:
    QMap<QUuid,WPlugin*>plugins;
};
///
/// \brief WPluginManager::WPluginManager
///
WPluginManager::WPluginManager()
{
    d=new WPluginManagerPrivate;
}
///
/// \brief WPluginManager::~WPluginManager
///
WPluginManager::~WPluginManager()
{
    delete d;
    d=nullptr;
}
///
/// \brief WPluginManager::createPlugin
/// \param configPath
/// \param config
/// \return
///
WPlugin* WPluginManager::createPlugin(QString configPath,QString config){
    auto plugin=new WPlugin(this);
    plugin->readConfig(configPath,config);
    return plugin;
}
///
/// \brief WPluginManager::loadPlugin
/// \param plugin
/// \return
///
bool WPluginManager::loadPlugin(WPlugin* plugin){
    if(plugin->available()){
        QString name=qvariant_cast<QString>(plugin->getMetaData("name"));
        while(getPluginById(getPluginByName(name))){
            name+="#";
        }
        plugin->setMetaData("name",name);
        d->plugins.insert(QUuid::createUuid(),plugin);
        return true;
    }
    return false;
}
///
/// \brief WPluginManager::unloadPlugin
/// \param plugin
/// \return
///
bool WPluginManager::unloadPlugin(WPlugin* plugin){
    auto it=d->plugins.begin();
    for(;it!=d->plugins.end();it++){
        if(*it==plugin)break;
    }
    if(it==d->plugins.end())return false;
    return unloadPlugin(it);
}
///
/// \brief WPluginManager::unloadAllPlugins
///
void WPluginManager::unloadAllPlugins()
{
    for(auto it=d->plugins.begin();it!=d->plugins.end();it++){
        unloadPlugin(it);
    }
}
///
/// \brief WPluginManager::unloadPlugin
/// \param it
/// \return
///
bool WPluginManager::unloadPlugin(QMap<QUuid,WPlugin*>::Iterator it){
    if(!(*it)->unload())return false;
    d->plugins.erase(it);
    return true;
}
///
/// \brief WPluginManager::getPluginByAttr
/// \param key
/// \param value
/// \return
///
QVector<QUuid> WPluginManager::getPluginByAttr(QString key,QVariant value){
    QVector<QUuid> res;
    for(auto it=d->plugins.begin();it!=d->plugins.end();it++){
        if(it.value()->getMetaData(key)==value)res.push_back(it.key());
    }
    return res;
}
///
/// \brief WPluginManager::getPluginByName
/// \param name
/// \return
///
QUuid WPluginManager::getPluginByName(QString name){
    auto list=getPluginByAttr("name",name);
    if(!list.isEmpty())return list[0];
    return QUuid();
}
//
/// \brief WPluginManager::getPlugin
/// \param id
/// \return
///
WPlugin* WPluginManager::getPluginById(QUuid id){
    if(d->plugins.contains(id))return d->plugins[id];
    return nullptr;
}
///
/// \brief WPluginManager::setPluginData
/// \param id
/// \param key
/// \param value
/// \return
///
QVariant WPluginManager::setPluginData(QUuid id,QString key,QVariant value){
    if(!d->plugins.contains(id))return value;
    auto plugin=d->plugins[id];
    if(key=="name"){
        QString name=qvariant_cast<QString>(value);
        while(getPluginById(getPluginByName(name))){
            if(getPluginByAttr("name",name).length()==1&&plugin->getMetaData("name")==name)return name;
            name+="#";
        }
        value=name;
    }
    return value;
}
///
/// \brief WPluginManager::getUuid
/// \param plugin
/// \return
///
QUuid WPluginManager::getUuid(WPlugin* plugin){
    for(auto it=d->plugins.begin();it!=d->plugins.end();it++){
        if(it.value()==plugin)return it.key();
    }
    return QUuid();
}
///
/// \brief WPluginManager::allPluginsId
/// \return
///
QVector<QUuid> WPluginManager::allPluginsId(){
    return d->plugins.keys();
}
///
/// \brief WPluginManager::allPluginsInst
/// \return
///
QVector<WPlugin*> WPluginManager::allPluginsInst(){
    return d->plugins.values();
}
///
/// \brief WPluginManager::sendMsg
/// \param msg
///
void WPluginManager::sendMsg(WMetaData &msg)
{
    auto loader =getPluginById(getPluginByName(msg.dest));
    if(loader)
    {
        auto plugin = loader->inst();
        if(plugin)plugin->recMsg(msg);
    }
}
