//Copyright 2025 HWorldY
//the Apache License, Version 2.0
//Author: HWorldY
#ifndef WE_H
#define WE_H
#include "../wdef.h"
#include <QtGlobal>
#include <QObject>

#if defined(WIDGETEXPLORERSDK_LIBRARY)
#  define WIDGETEXPLORERSDKSHARED_EXPORT Q_DECL_EXPORT
#else
#  define WIDGETEXPLORERSDKSHARED_EXPORT Q_DECL_IMPORT
#endif

class WIDGETEXPLORERSDKSHARED_EXPORT WE{
public:
    enum WETYPE {WE_NONE,WE_WE,WE_LW,WE_DBG};
    static bool init(WEBase* base,WETYPE type);
    static WEBase *inst();
private:
    static WETYPE t;
    static WEBase* m_instance;
};

#endif
