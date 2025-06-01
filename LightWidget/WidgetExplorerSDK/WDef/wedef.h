//Copyright 2025 HWorldY
//the Apache License, Version 2.0
//Author: HWorldY
#ifndef WEDEF_H
#define WEDEF_H

//#define WE_VERSION_MAJOR 0
//#define WE_VERSION_MINOR 0
//#define WE_VERSION_REVISION 2
#define EX(a) a

#define _LS(a,b) a##b
#define LS(a,b) _LS(a,b)

#define _MS(a) #a
#define MS(a) _MS(a)

#define _WE_VERSION 1_1_0
#define WE_VERSION _WE_VERSION
#define _WE_VERSION_STRING 1.1.0
#define WE_VERSION_STRING MS(_WE_VERSION_STRING)
#define WE_NAMESPACE LS(WE_,WE_VERSION)

#define V2V(type,key) qvariant_cast<type>(var[key])

inline namespace WE_NAMESPACE {
class WE;
class WBase;
class WEBase;
class WEBaseData;
class LightWidget;
class WidgetExplorer;
class WPlugin;
class WidgetDebugger;
class WPath;
class WPluginManager;
class WConfigDocument;
class WWidgetManager;
class WWidget;
class WEClass;
class WVirtualPlugin;
template<class T>class WConfig;
}

template<typename funcType>
void* getMemberAddr(funcType func){
    union {
        void* pv;
        funcType pfn;
    } u;
    u.pfn = func;
    return u.pv;
}

#if defined(WIDGETEXPLORERSDK_LIBRARY)
#  define WIDGETEXPLORERSDK_EXPORT Q_DECL_EXPORT
#else
#  define WIDGETEXPLORERSDK_EXPORT Q_DECL_IMPORT
#endif
#define WApp (WE::inst())
#endif // WEDEF_H
