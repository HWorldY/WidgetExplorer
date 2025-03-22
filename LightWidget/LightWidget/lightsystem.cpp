//Copyright 2025 HWorldY
//the Apache License, Version 2.0
//Author: HWorldY
#include "lightsystem.h"
#include<QDir>
#include"../WidgetExplorerSDK/WFile/wpath.h"
#include"../WidgetExplorerSDK/WPlugin/wpluginmanager.h"
#include"../WidgetExplorerSDK/we.h"

LightSystem::LightSystem() {}
void LightSystem::loadAllPlugin(){
    QDir pluginsdir = WPath(WE::inst()).getModuleFolder();
    pluginsdir.cd("widget");

    QFileInfoList pluginsInfo = pluginsdir.entryInfoList(QDir::Files | QDir::NoDotAndDotDot);
    for(const QFileInfo &fileinfo : std::as_const(pluginsInfo))
        WPluginManager::instance()->scanMetaData(fileinfo.absoluteFilePath());

    for(const QFileInfo &fileinfo : std::as_const(pluginsInfo))
        WPluginManager::instance()->loadPlugin(fileinfo.absoluteFilePath());
}
