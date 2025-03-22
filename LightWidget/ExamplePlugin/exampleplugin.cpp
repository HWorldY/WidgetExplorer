//Copyright 2025 HWorldY
//the Apache License, Version 2.0
//Author: HWorldY
#include "exampleplugin.h"
#include "../WidgetExplorerSDK/we.h"
#include "../WidgetExplorerSDK/wfile.h"
#include <QWidget>
#include <windows.h>
#include "exampledialog.h"

ExamplePlugin::ExamplePlugin() {}

ExamplePlugin::~ExamplePlugin()
{

}

void ExamplePlugin::init(QMap<QString,QVariant> &data) {
    Q_UNUSED(data);
    WE::inst();
    WPath::splitPath("//");
    widget.setCommand(data);
    this->data=data;
}

void ExamplePlugin::recMsgFromManager(WPluginMetaData &msg) {
    if(msg.map["Command"]=="start"){
        if(widget.isHidden())widget.show();
        else widget.activateWindow();
    }
    widget.appCommand("\n----\nfrom:"+msg.from+"\ndest:"+msg.dest+"\nmsg:\n");
    widget.appCommand(msg.map);
    if(msg.map["Command"]=="clear"){
        widget.setCommand(data);
        if(widget.isHidden())widget.show();
        else widget.activateWindow();
    }
}
