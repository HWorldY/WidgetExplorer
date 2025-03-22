//Copyright 2025 HWorldY
//the Apache License, Version 2.0
//Author: HWorldY
#include "wpath.h"
#include "../we.h"
#include "WPlugin/wpluginmanager.h"
WPath::WPath(WEBase *we)
{
    webase=we;
}
QString WPath::getModulePath(){
    WCHAR p[MAX_PATH];
    GetModuleFileName(NULL, p, MAX_PATH);
    QString path = QString::fromWCharArray(p);
    return path;

}
//
QString WPath::getModuleFolder(){
    return splitPath(getModulePath());
}
void WPath::ShellExe(QString lpFile,QString lpOperation,QString lpParameters,QString lpDirectory){
    lpDirectory=(lpDirectory=="default")?WPath::splitPath(lpFile):lpDirectory;
    ShellExecute(0,lpOperation.toStdWString().c_str(),
                 lpFile.toStdWString().c_str(),
                 lpParameters.toStdWString().c_str(),
                 lpDirectory.toStdWString().c_str(),
                 SW_NORMAL);
}
QString WPath::getModulePath(QString moduleName){
    if(webase==nullptr)return "";
    auto pm=webase->pluginManager();
    auto plugin=pm->getPlugin(moduleName);
    return plugin->fileName();
}
QString WPath::getModuleFolder(QString moduleName){
    return splitPath(getModulePath(moduleName));
}
QString WPath::splitPath(QString path){
    int i = path.length() - 1;
    for (; i >= 0&&!(path[i] == '\\'||path[i] == '/'); i--);
    return path.length() >= 2 ? path.mid(0, i + 1) : "";
}
