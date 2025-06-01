//Copyright 2025 HWorldY
//the Apache License, Version 2.0
//Author: HWorldY
#include "lightsystem.h"
#include<QDir>
#include"../WidgetExplorerSDK/WFile/wpath.h"
#include"../WidgetExplorerSDK/WPlugin/wpluginmanager.h"
#include"../WidgetExplorerSDK/WPlugin/wplugin.h"
#include"../WidgetExplorerSDK/we.h"
#include <QCoreApplication>

LightSystem::LightSystem() {

}
void LightSystem::loadAllPlugin(){
    QString plugins = WPath().getModuleFolder()+"widget/widget.json";
    WConfigDocument doc;
    doc.load(plugins,true);
    auto map=doc.toMap();
    for(auto it=map.begin();it!=map.end();it++){
        QJsonDocument doc2(it.value().toJsonObject());
        loadPlugin(plugins,doc2.toJson());
    }
}
void LightSystem::loadPlugin(QString curPath,QString config){
    WConfigDocument doc;
    doc.load(config,false);
    QString jsonPath=WPath().transPath(curPath,qvariant_cast<QString>(doc.get("path")));

    WConfigDocument objectDoc;
    objectDoc.load(jsonPath,true);

    for(int i=1;;i++){
        QString num=QString::number(i);

        auto obj=objectDoc.get(num).toJsonObject();
        if(obj.isEmpty())break;
        QJsonDocument doc2(obj);
        WConfigDocument doc3;
        doc3.load(doc2.toJson(),false);

        loadSinglePlugin(jsonPath,&doc3);
    }
}
void LightSystem::loadSinglePlugin(QString jsonPath,WConfigDocument* doc){
    if(!doc->hasArg("path"))return;
    WPlugin* plugin=new WPlugin(WE::inst()->getWEClass()->pluginManager());
    plugin->readConfig(jsonPath,doc->toJson());
    plugin->load();
    WE::inst()->getWEClass()->pluginManager()->loadPlugin(plugin);
}
