//Copyright 2025 HWorldY
//the Apache License, Version 2.0
//Author: HWorldY
#include"wpath.h"
#include"../WPlugin/wpluginmanager.h"
#include"../WPlugin/wplugin.h"

#include<QDir>
///
/// \brief The WPathPrivate class
///
class WPathPrivate{
public:
    QString moduleName="";
};

///
/// \brief WPath::WPath
/// \param we
///
WPath::WPath(WEBase *we):WBase(we)
{
    d=new WPathPrivate;
}
///
/// \brief WPath::~WPath
///
WPath::~WPath(){
    delete d;
    d=nullptr;
}
///
/// \brief WPath::setWEBase
/// \param base
///
void WPath::setWEBase(WEBase* base){
    setBase(base);
}
///
/// \brief WPath::getModulePath
/// \return
///
QString WPath::getModulePath(){
    WCHAR p[MAX_PATH];
    GetModuleFileName(NULL, p, MAX_PATH);
    QString path = QString::fromWCharArray(p);
    return QDir::cleanPath(path);
}
///
/// \brief WPath::getModuleFolder
/// \return
///
QString WPath::getModuleFolder(){
    return splitPath(getModulePath());
}
///
/// \brief WPath::getModulePath
/// \param moduleName
/// \return
///
QString WPath::getModulePath(QUuid moduleId){
    if(getBase()==nullptr)return "";
    auto pm=getBase()->getWEClass()->pluginManager();
    auto plugin=pm->getPluginById(moduleId);
    return qvariant_cast<QString>(plugin->getMetaData("path"));
}
///
/// \brief WPath::getModuleFolder
/// \param moduleName
/// \return
///
QString WPath::getModuleFolder(QUuid moduleId){
    return splitPath(getModulePath(moduleId));
}
///
/// \brief WPath::getModulePath
/// \param plugin
/// \return
///
QString WPath::getModulePath(WPlugin *plugin){
    if(getBase()==nullptr)return "";
    return qvariant_cast<QString>(plugin->getMetaData("path"));
}
///
/// \brief WPath::getModuleFolder
/// \param plugin
/// \return
///
QString WPath::getModuleFolder(WPlugin *plugin){
    return splitPath(getModulePath(plugin));
}
///
/// \brief WPath::splitPath
/// \param path
/// \return
///
QString WPath::splitPath(QString path){
    path=QDir::cleanPath(path);
    return path.mid(0,path.lastIndexOf("/")+1);
}
///
/// \brief WPath::transPath
/// \param cur
/// \param des
/// \return
///
QString WPath::transPath(QString cur,QString des){
    cur=QDir::cleanPath(cur);
    des=QDir::cleanPath(des);
    QFileInfo info(cur);

    if(info.isFile()){
        cur=splitPath(cur);
    }

    QDir currentDir(cur);

    if(QDir::isAbsolutePath(des))return QDir::cleanPath(des);
    QString absolutePath = currentDir.absoluteFilePath(des);
    absolutePath=QDir::cleanPath(absolutePath);
    return absolutePath;
}
///
/// \brief WPath::ShellExe
/// \param lpFile
/// \param lpOperation
/// \param lpParameters
/// \param lpDirectory
///
void WPath::ShellExe(QString lpFile,QString lpOperation,QString lpParameters,QString lpDirectory){
    lpDirectory=(lpDirectory=="default")?WPath().splitPath(lpFile):lpDirectory;
    ShellExecute(0,lpOperation.toStdWString().c_str(),
                 lpFile.toStdWString().c_str(),
                 lpParameters.toStdWString().c_str(),
                 lpDirectory.toStdWString().c_str(),
                 SW_NORMAL);
}
