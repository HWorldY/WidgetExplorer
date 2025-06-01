//Copyright 2025 HWorldY
//the Apache License, Version 2.0
//Author: HWorldY
#ifndef LIGHTSYSTEM_H
#define LIGHTSYSTEM_H
#include<QString>
#include"../WidgetExplorerSDK/WConfig/wconfigdocument.h"


class LightSystem
{
public:
    LightSystem();
    void loadAllPlugin();
    void loadPlugin(QString jsonPath,QString config);
    void loadSinglePlugin(QString jsonPath,WConfigDocument* doc);
};

#endif // LIGHTSYSTEM_H
