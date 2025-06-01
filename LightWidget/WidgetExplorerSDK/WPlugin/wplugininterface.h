//Copyright 2025 HWorldY
//the Apache License, Version 2.0
//Author: HWorldY
#ifndef WPLUGININTERFACE_H
#define WPLUGININTERFACE_H
#include"../WPlugin/wpluginmetadata.h"
#include"../WPlugin/wpluginmanager.h"
#include"../WDef/wedef.h"

#define W_DECLARE_PLUGIN(ClassType)\
public:\
bool connectManager(WPluginManager *manager, bool isConnect) const Q_DECL_OVERRIDE{\
    if(isConnect)\
    return connect(this, &ClassType::sendMsg, manager, &WPluginManager::sendMsg);\
    else\
        return disconnect(this, &ClassType::sendMsg, manager, &WPluginManager::sendMsg);\
};

class WPluginInterface
{
public:
    virtual ~WPluginInterface() {}
public:
    virtual void init(QMap<QString,QVariant> &data) = 0;
    virtual void recMsg(WMetaData &msg) = 0;
    virtual bool connectManager(WPluginManager *receiver, bool isConnect = true) const = 0;
};

#define PluginInterface_iid "QPlugins.WPluginManager.WPluginInterface"
Q_DECLARE_INTERFACE(WPluginInterface, PluginInterface_iid)

#endif // WPLUGININTERFACE_H
