//Copyright 2025 HWorldY
//the Apache License, Version 2.0
//Author: HWorldY
#ifndef LIGHTWIDGET_H
#define LIGHTWIDGET_H
#include <QMap>
#include <QString>
#include"../WidgetExplorerSDK/WE/webase.h"

class WE_NAMESPACE::LightWidget : public WEBase
{
public:
    LightWidget();
    void initData(QSharedPointer<WEBaseData> data);
    bool sendMsgs(QString widgetName, QMap<QString, QVariant> map);
private:
};

#endif // LIGHTWIDGET_H
