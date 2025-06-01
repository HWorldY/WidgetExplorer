//Copyright 2025 HWorldY
//the Apache License, Version 2.0
//Author: HWorldY
#include<QLockFile>
#include<QFile>

#include "mainwindow.h"
#include "aboutwindow.h"
#include "ui_mainwindow.h"

#include"../WidgetExplorerSDK/WFile/wpath.h"
#include"../WidgetExplorerSDK/wplugin.h"
#include "lightwidget.h"
#include "../WidgetExplorerSDK/WE/we.h"
#include "../WidgetExplorerSDK/WE/webase.h"
#include"../WidgetExplorerSDK/WPlugin/wwidgetmanager.h"

MainWindow::MainWindow(QStringList param,LightWidget* ptr, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    this->ptr=ptr;
    this->sys=new LightSystem;

    ui->setupUi(this);
    this->resize(1200,800);
    this->setMinimumSize(800,566);

    QPalette pal(this->palette());
    pal.setColor(QPalette::ColorRole::Window, QColor(255,255,255));
    this->setAutoFillBackground(true);
    this->setPalette(pal);

    if(param.length()>=1)if(param[0]=="autorun")ptr->getWEClass()->configManager()->set("autorun",true);
    if(!qvariant_cast<bool>(ptr->getWEClass()->configManager()->get("autorun")))show();

    //Load plugins
    this->sys->loadAllPlugin();
    auto plugins=WE::inst()->getWEClass()->pluginManager()->allPluginsInst();
    foreach(auto plugin,plugins)
    {
        WPluginInterface *app = plugin->inst();
        if (app)
        {
            if(qvariant_cast<QString>(plugin->getMetaData("type"))=="exe"){
                if(qvariant_cast<QString>(plugin->getMetaData("init"))=="default"){
                    continue;
                }
            };
            QMap<QString,QVariant> data;
            QVariant var;
            QVariant var2;
            var.setValue((WEBase*)ptr);
            var2.setValue(plugin);
            data.insert("WE",var);
            data.insert("Plugin",var2);
            app->init(data);
        }
    }
    ui->listLink->addItems(ReadLinkFile());
    initTable();

    QMenuBar* menuBar=this->menuBar();
    QMenu* menuPlugin=new QMenu("插件");
    QAction* actNew=new QAction("创建新插件");
    QAction* actImport=new QAction("导入现有插件");
    QAction* actExport=new QAction("导出");
    QMenu* menuOption=new QMenu("选项");
    QAction* actSetting=new QAction("设置");
    QAction* actReset=new QAction("重启");
    QMenu* menuAbout=new QMenu("关于");
    QAction* actAbout=new QAction("关于");

    menuBar->addMenu(menuPlugin);
    menuPlugin->addAction(actNew);
    menuPlugin->addAction(actImport);
    menuPlugin->addAction(actExport);
    menuBar->addMenu(menuOption);
    menuOption->addAction(actSetting);
    menuOption->addAction(actReset);
    menuBar->addMenu(menuAbout);
    menuAbout->addAction(actAbout);

    connect(actAbout,&QAction::triggered,this,&MainWindow::about);
    connect(actReset,&QAction::triggered,this,&MainWindow::reset);
    connect(actSetting,&QAction::triggered,this,[](){
        WPath().ShellExe(WPath().getModuleFolder()+"config/config.json");
    });

    //Init widgets
    WE::inst()->getWEClass()->widgetManager()->initWidget();
}
void MainWindow::createCol(int col,QString title,QFont font,QColor color){
    QTableWidgetItem*item=new QTableWidgetItem(title);
    item->setFont(font);
    item->setForeground(QBrush(color));
    item->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    ui->tableWidget->setHorizontalHeaderItem(col,item);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(col,QHeaderView::ResizeToContents);
}
void MainWindow::initTable(){
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget->setSelectionMode(QAbstractItemView::NoSelection);

    QFont font;
    font.setPointSize(10);
    font.setFamily("黑体");

    QColor color(0,0,0);

    int colCount=4;

    ui->tableWidget->setColumnCount(colCount);

    createCol(0,"插件名",font,color);
    createCol(1,"版本",font,color);
    createCol(2,"作者",font,color);
    createCol(3,"路径",font,color);

    auto list=WE::inst()->getWEClass()->pluginManager()->allPluginsInst();
    ui->tableWidget->setRowCount(list.length());
    auto it=list.begin();
    for(int i=0;i<=list.length()-1;i++){
        createRow(i,*it);
        it++;
    }
}
void MainWindow::createRow(int row,  WPlugin* info){
    if(row>=ui->tableWidget->rowCount())return;
    QTableWidgetItem*item=nullptr;
    QString str;
    QStringList list={"name","version","author","path"};
    for(int i=0;i<=list.length()-1;i++){
        str=qvariant_cast<QString>(info->getMetaData(list[i]));
        item=new QTableWidgetItem(str);
        item->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
        ui->tableWidget->setItem(row,i,item);
    }
}
void MainWindow::tray(QSystemTrayIcon::ActivationReason reason){
    switch (reason) {
    case QSystemTrayIcon::DoubleClick:
        if(!this->isVisible()){
            this->showNormal();
        }
        else{
            this->activateWindow();
        }
        break;
    default:
        break;
    }
}
MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::closeEvent(QCloseEvent *event)
{
    event->ignore();
    setVisible(false);
}
void MainWindow::showPanel()
{
    this->show();
    this->raise();
}
QStringList MainWindow::ReadLinkFile(){
    QFile file(WPath().getModuleFolder()+"widget/link.txt");
    QStringList list;
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        QString str = in.readAll();
        list = str.split('\n');
        file.close();
    }
    return list;
}


void MainWindow::on_btnCmd_clicked()
{
    QMap<QString,QVariant>map;
    QString str=ui->editCmd->text();
    int i=0;
    for(;i<=str.size()-1;i++){
        if(str[i]==' ')break;
    }
    map.insert("Command",str.mid(i+1));
    ptr->sendMsgs(str.mid(0,i),map);
}

void MainWindow::about(){
    if(aboutWnd==nullptr)aboutWnd=new AboutWindow;
    if(aboutWnd->isHidden())aboutWnd->show();
    aboutWnd->activateWindow();
}

void MainWindow::reset(){
    lock->unlock();
    Sleep(10);
    WPath().ShellExe(WPath().getModulePath());
    ::TerminateProcess(::GetCurrentProcess(), 0);
}

void MainWindow::on_tableWidget_cellDoubleClicked(int row, int column)
{
    auto item=ui->tableWidget->item(row,column);
    ui->editCmd->setText(item->text());
}

void MainWindow::on_btnClear_clicked()
{
    ui->editCmd->clear();
}


void MainWindow::on_listLink_itemClicked(QListWidgetItem *item)
{
    ui->editCmd->setText(item->text());

}

