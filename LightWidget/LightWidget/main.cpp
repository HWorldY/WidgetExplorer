//Copyright 2025 HWorldY
//the Apache License, Version 2.0
//Author: HWorldY
#include"mainwindow.h"
#include"lightwidget.h"

#include"../WidgetExplorerSDK/we.h"
#include"../WidgetExplorerSDK/wplugin.h"
#include"../WidgetExplorerSDK/WConfig/wconfigdocument.h"
#include"../WidgetExplorerSDK/WFile/wpath.h"

#include<QApplication>
#include<QLockFile>
#include<QMenu>
#include<QSystemTrayIcon>
#include<QStyleFactory>
int main(int argc, char* argv[])
{
    //Initialization work
    auto lwptr=new LightWidget;
    if(lwptr==nullptr)return 0;
    if(!WE::init(lwptr,WE::WE_LW))return 0;
    lwptr->getWEClass()->configManager()->load(WPath().getModuleFolder()+"config/config.json",true);

    if (qEnvironmentVariableIsEmpty("QT_FONT_DPI"))
    {
        auto config=lwptr->getWEClass()->configManager();
        if(config->hasArg("font"))qputenv("QT_FONT_DPI", qvariant_cast<QByteArray>(lwptr->getWEClass()->configManager()->get("font")));
        if(config->hasArg("scale"))qputenv("QT_SCALE_FACTOR", qvariant_cast<QByteArray>(lwptr->getWEClass()->configManager()->get("scale")));
    }

    QLockFile* lockfile=new QLockFile(WPath().getModuleFolder() + ".lock");
    if (!lockfile->tryLock(0))return 1;

    QApplication a(argc, argv);
    a.setWindowIcon(QIcon(":/icons/icon/we.jpg"));
    a.setQuitOnLastWindowClosed(false);

    //Main
    QStringList param;
    for (int i = 1; i <= argc - 1; i++)param.push_back(argv[i]);

    MainWindow w(param,lwptr);
    w.setWindowTitle("LightWidget");
    w.lock=lockfile;

    //Create System Tray
    QSystemTrayIcon* pSystemTray = new QSystemTrayIcon(&w);
    if (NULL != pSystemTray) {
        pSystemTray->setIcon(QIcon(":/icons/icon/we.jpg"));
        pSystemTray->setToolTip("LightWidget");
        pSystemTray->show();
    }
    auto* trayMenu = new QMenu(&w);
    QObject::connect(pSystemTray, &QSystemTrayIcon::activated, &w, &MainWindow::tray);
    auto* showPanelAction = new QAction("显示", &w);
    QObject::connect(showPanelAction, &QAction::triggered, &w, &MainWindow::showPanel);
    trayMenu->addAction(showPanelAction);
    auto* quitAction = new QAction("退出", &w);
    QObject::connect(quitAction, &QAction::triggered, &w, &QApplication::quit);
    trayMenu->addAction(quitAction);
    pSystemTray->setContextMenu(trayMenu);
    pSystemTray->show();

    return a.exec();
}
