//Copyright 2025 HWorldY
//the Apache License, Version 2.0
//Author: HWorldY
#ifndef WPLUGININTERFACE_H
#define WPLUGININTERFACE_H
#include "wpluginmetadata.h"
#define DECLARE_CONNECT_TO_MANAGER \
public:\
bool connectTosendMsgToManager(QObject *receiver, const char *pszSlot, bool isConnect) const Q_DECL_OVERRIDE{\
    if(isConnect)\
        return connect(this, SIGNAL(sendMsgToManager(WPluginMetaData&)), receiver, pszSlot);\
    else\
        return disconnect(this, SIGNAL(sendMsgToManager(WPluginMetaData&)), receiver, pszSlot);\
};


class WPluginInterface
{
public:
    virtual ~WPluginInterface() {}

public:

    virtual void init(QMap<QString,QVariant> &data) = 0;
    virtual void callAFunction(QString call){
        call="";
        return;
    };

    virtual void recMsgFromManager(WPluginMetaData &msg) = 0;

    //connect to signals sendMsgToManager
    //virtual void sendMsgToManager(WPluginMetaData &msg) = 0;
    virtual bool connectTosendMsgToManager(QObject *receiver, const char* pszSlot, bool isConnect = true) const = 0;
    QWidget* widget=nullptr;
};
#define PluginInterface_iid "QPlugins.WPluginManager.WPluginInterface"

Q_DECLARE_INTERFACE(WPluginInterface, PluginInterface_iid)

#endif // WPLUGININTERFACE_H
