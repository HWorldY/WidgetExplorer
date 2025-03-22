//Copyright 2025 HWorldY
//the Apache License, Version 2.0
//Author: HWorldY
#ifndef WEBASE_H
#define WEBASE_H
#include <QObject>
#include"../wdef.h"
#include"../WidgetExplorerSDK/WConfig/wconfig.h"
class WEBase
{
public:
    WEBase();
	virtual WConfig* configManager()=0;
    virtual WPath pathManager()=0;
    virtual WPluginManager* pluginManager()=0;
};
typedef WEBase* WEBasePtr;
Q_DECLARE_METATYPE(WEBase);
Q_DECLARE_METATYPE(WEBasePtr);
#endif // WEBASE_H
