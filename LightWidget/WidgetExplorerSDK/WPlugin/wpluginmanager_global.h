//Copyright 2025 HWorldY
//the Apache License, Version 2.0
//Author: HWorldY
#ifndef WPLUGINMANAGER_GLOBAL_H
#define WPLUGINMANAGER_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(WIDGETEXPLORERSDK_LIBRARY)
#  define WPLUGINMANAGERSHARED_EXPORT Q_DECL_EXPORT
#else
#  define WPLUGINMANAGERSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // WPLUGINMANAGER_GLOBAL_H
