//Copyright 2025 HWorldY
//the Apache License, Version 2.0
//Author: HWorldY
#ifndef LIGHTWIDGET_H
#define LIGHTWIDGET_H
#include <QMap>
#include <QString>
#include"../WidgetExplorerSDK/WE/webase.h"

class LightWidget : public WEBase
{
public:
    LightWidget();
    bool sendMsgs(QString widgetName, QMap<QString, QVariant> map);
    WConfig* configManager();
    WPath pathManager();
    WPluginManager* pluginManager();
private:
    WConfig* config = nullptr;
    WPluginManager* pluginmanager=nullptr;
};

#endif // LIGHTWIDGET_H
