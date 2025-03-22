//Copyright 2025 HWorldY
//the Apache License, Version 2.0
//Author: HWorldY
#ifndef WPATH_H
#define WPATH_H
#include <QString>
#include <windows.h>
#include <QtGlobal>
#include <QObject>
#include "../wdef.h"

#if defined(WIDGETEXPLORERSDK_LIBRARY)
#  define FILEPATHSHARED_EXPORT Q_DECL_EXPORT
#else
#  define FILEPATHSHARED_EXPORT Q_DECL_IMPORT
#endif
class FILEPATHSHARED_EXPORT WPath
{
public:
    WPath(WEBase* we=nullptr);
    static QString getModulePath();
    static QString getModuleFolder();
    static void ShellExe(QString lpFile,QString lpOperation="open",QString lpParameters="",QString lpDirectory="default");
    QString getModulePath(QString moduleName);
    QString getModuleFolder(QString moduleName);
    static QString splitPath(QString path);
private:
    WEBase* webase=nullptr;
    QString moduleName="";
};

#endif // WPATH_H
