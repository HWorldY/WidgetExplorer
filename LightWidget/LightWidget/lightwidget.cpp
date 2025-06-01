//Copyright 2025 HWorldY
//the Apache License, Version 2.0
//Author: HWorldY
#include "lightwidget.h"
#include"../WidgetExplorerSDK/wplugin.h"
#include "../WidgetExplorerSDK/we.h"
#include "../WidgetExplorerSDK/wfile.h"
#include"../WidgetExplorerSDK/WConfig/wconfigdocument.h"
#include"../WidgetExplorerSDK/WPlugin/wwidgetmanager.h"
#include"../WidgetExplorerSDK/WPlugin/wplugin.h"


void LightWidget::initData(QSharedPointer<WEBaseData> data){
    QVariant config;
    config.setValue(new WConfigDocument);
    data->addData("configManager",config);

    QVariant path;
    path.setValue(new WPath);
    data->addData("pathManager",path);

    QVariant pluginManager;
    pluginManager.setValue(new WPluginManager);
    data->addData("pluginManager",pluginManager);

    QVariant widgetManager;
    widgetManager.setValue(new WWidgetManager);
    data->addData("widgetManager",widgetManager);
};

LightWidget::LightWidget():WEBase() {
    auto data=WEBase::getWEBaseData();
    initData(data);
    return;
}
bool LightWidget::sendMsgs(QString widgetName,QMap<QString, QVariant> map){
    auto widgetId=WE::inst()->getWEClass()->pluginManager()->getPluginByName(widgetName);
    //auto list=WE::inst()->getWEClass()->pluginManager()->getPlugin("name",widgetName);
    //auto pls=WE::inst()->getWEClass()->pluginManager()->allPlugins();
    //auto n1=pls[0]->getMetaData("name");
    //auto n2=pls[1]->getMetaData("name");
    //auto n3=pls[2]->getMetaData("name");
    if(widgetId.isNull())return 0;
    WPluginInterface *app = WE::inst()->getWEClass()->pluginManager()->getPluginById(widgetId)->inst();

    if (app)
    {
        WMetaData data;
        data.from="WE";
        data.dest=widgetName;
        data.map=map;
        //qDebug()<<app<<widget->getMetaData("name");
        app->recMsg(data);
    }
    return 1;
}

