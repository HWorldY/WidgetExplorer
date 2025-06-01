//Copyright 2025 HWorldY
//the Apache License, Version 2.0
//Author: HWorldY
#include "examplewidget.h"
#include "../WidgetExplorerSDK/we.h"
#include"../WidgetExplorerSDK/wfile.h"
#include"../WidgetExplorerSDK/WPlugin/wplugin.h"
#include"../WidgetExplorerSDK/WPlugin/wwidgetmanager.h"
#include "exampleplugin.h"
#include <QWidget>
#include<windows.h>
#include "exampledialog.h"

ExamplePlugin::ExamplePlugin() {}

ExamplePlugin::~ExamplePlugin()
{

}

void ExamplePlugin::init(QMap<QString,QVariant> &data) {
    PluginData::setData(qvariant_cast<WEBase*>(data["WE"]));
    PluginData::setPlugin(qvariant_cast<WPlugin*>(data["Plugin"]));

    auto widgetManager=PClass->widgetManager();
    widget=new ExampleWidget(PData);
    widgetManager->addWidget(QUuid::createUuid(),widget);

    WPlugin* plugin=qvariant_cast<WPlugin*>(data["Plugin"]);
    plugin->setMetaData("name","Example");
}

void ExamplePlugin::recMsg(WMetaData &msg) {
    widget->sendMessageCallback(msg);
}
