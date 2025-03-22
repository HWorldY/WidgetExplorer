//Copyright 2025 HWorldY
//the Apache License, Version 2.0
//Author: HWorldY
#ifndef EXAMPLEPLUGIN_H
#define EXAMPLEPLUGIN_H

#include <QObject>
#include <QtPlugin>
#include "../WidgetExplorerSDK/WPlugin/wplugininterface.h"
#include "exampledialog.h"
#include "../WidgetExplorerSDK/we.h"

class ExamplePlugin :public QObject, public WPluginInterface
{
public:
    Q_OBJECT
    Q_PLUGIN_METADATA(IID PluginInterface_iid FILE "ExamplePlugin.json")
    Q_INTERFACES(WPluginInterface)
    DECLARE_CONNECT_TO_MANAGER;
signals:
    void sendMsgToManager(WPluginMetaData&);
public:
    ExamplePlugin();
    ~ExamplePlugin();
    void init(QMap<QString,QVariant> &data) override;
    void recMsgFromManager(WPluginMetaData &msg) override;
    QMap<QString,QVariant> data;
    ExampleDialog widget;
private:
    WEBase* we;
};

#endif // EXAMPLEPLUGIN_H
