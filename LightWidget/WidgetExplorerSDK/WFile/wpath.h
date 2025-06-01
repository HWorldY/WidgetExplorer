//Copyright 2025 HWorldY
//the Apache License, Version 2.0
//Author: HWorldY
#ifndef WPATH_H
#define WPATH_H
#include"../WDef/wedef.h"
#include"../WE/wbase.h"

#include <Windows.h>
#include <QString>
#include <QtGlobal>
#include <QObject>

class WPathPrivate;

class WE_NAMESPACE::WPath:public WBase
{
public:
    WPath(WEBase* we=nullptr);
    virtual~WPath();
    void setWEBase(WEBase* base);
    QString getModulePath();
    QString getModuleFolder();
    QString getModulePath(QUuid moduleId);
    QString getModuleFolder(QUuid moduleId);
    QString getModulePath(WPlugin* plugin);
    QString getModuleFolder(WPlugin* plugin);
    QString splitPath(QString path);
    QString transPath(QString cur,QString des);
    void ShellExe(QString lpFile,QString lpOperation="open",QString lpParameters="",QString lpDirectory="default");
private:
    WPathPrivate* d=nullptr;
};

Q_DECLARE_METATYPE(WE_NAMESPACE::WPath);
Q_DECLARE_METATYPE(WE_NAMESPACE::WPath*);
#endif // WPATH_H
