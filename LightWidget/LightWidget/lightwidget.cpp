//Copyright 2025 HWorldY
//the Apache License, Version 2.0
//Author: HWorldY
#include "lightwidget.h"
#include"../WidgetExplorerSDK/wplugin.h"
#include "../WidgetExplorerSDK/we.h"
#include "../WidgetExplorerSDK/wfile.h"

LightWidget::LightWidget():WEBase() {
    return;
}
bool LightWidget::sendMsgs(QString widgetName,QMap<QString, QVariant> map){
    auto widget=WPluginManager::instance()->getPlugin(widgetName);
    if(!widget)return 0;
    WPluginInterface *app = qobject_cast<WPluginInterface*>(widget->instance());
    if (app)
    {
        WPluginMetaData data;
        data.from="WE";
        data.dest=widgetName;
        data.map=map;
        app->recMsgFromManager(data);
    }
    return 1;
}

WConfig* LightWidget::configManager()
{
    if(config==nullptr)
    {
        config=new WConfig();
    }
    return config;
}
WPath LightWidget::pathManager(){
    return WPath(this);
}

WPluginManager* LightWidget::pluginManager(){
    return WPluginManager::instance();
}
