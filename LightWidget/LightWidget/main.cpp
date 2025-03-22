//Copyright 2025 HWorldY
//the Apache License, Version 2.0
//Author: HWorldY
#include<QApplication>
#include<QLockFile>
#include<QMenu>
#include<QSystemTrayIcon>
#include<QStyleFactory>

#include"../WidgetExplorerSDK/we.h"
#include"../WidgetExplorerSDK/wplugin.h"
#include"../WidgetExplorerSDK/WConfig/wconfig.h"
#include"../WidgetExplorerSDK/WFile/wpath.h"

#include"mainwindow.h"
#include"lightwidget.h"

int main(int argc, char* argv[])
{

    auto lwptr=new LightWidget;
    if(lwptr==nullptr)return 0;
    if(!WE::init(lwptr,WE::WE_LW))return 0;
    lwptr->configManager()->readConfig();

    if (qEnvironmentVariableIsEmpty("QT_FONT_DPI"))
    {
        auto config=lwptr->configManager();
        if(config->getConfig("font")!="")qputenv("QT_FONT_DPI", qvariant_cast<QByteArray>(lwptr->configManager()->getConfig("font")));
        if(config->getConfig("scale")!="")qputenv("QT_SCALE_FACTOR", qvariant_cast<QByteArray>(lwptr->configManager()->getConfig("scale")));
    }

    QLockFile* lockfile=new QLockFile(WPath(WE::inst()).getModuleFolder() + ".lock");
    if (!lockfile->tryLock(0))return 1;

    QApplication a(argc, argv);
    a.setWindowIcon(QIcon(":/icons/icon/we.jpg"));
    a.setQuitOnLastWindowClosed(false);

    QStringList param;
    for (int i = 1; i <= argc - 1; i++)param.push_back(argv[i]);
    //param.push_back("autorun");

    MainWindow w(param,lwptr);
    w.setWindowTitle("LightWidget");
    w.lock=lockfile;

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
