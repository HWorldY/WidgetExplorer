//Copyright 2025 HWorldY
//the Apache License, Version 2.0
//Author: HWorldY
#ifndef EXAMPLEPLUGIN_H
#define EXAMPLEPLUGIN_H
#include "exampledialog.h"
#include "examplewidget.h"
#include "../WidgetExplorerSDK/WPlugin/wplugininterface.h"
#include"../WidgetExplorerSDK/WPlugin/wpluginmanager.h"

#include <QObject>
#include <QtPlugin>

class ExamplePlugin :public QObject, public WPluginInterface
{
public:
    Q_OBJECT
    Q_PLUGIN_METADATA(IID PluginInterface_iid)
    Q_INTERFACES(WPluginInterface)
    W_DECLARE_PLUGIN(ExamplePlugin);
signals:
    void sendMsg(WMetaData&);
public:
    ExamplePlugin();
    ~ExamplePlugin();
    void init(QMap<QString,QVariant> &data) override;
    void recMsg(WMetaData &msg) override;
private:
    ExampleWidget* widget=nullptr;
};

#endif // EXAMPLEPLUGIN_H
