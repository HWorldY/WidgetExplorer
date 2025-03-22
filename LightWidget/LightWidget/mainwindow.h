//Copyright 2025 HWorldY
//the Apache License, Version 2.0
//Author: HWorldY
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QListWidget>
#include <QMainWindow>
#include <QButtonGroup>
#include <QCloseEvent>
#include <QSystemTrayIcon>
#include <QLockFile>
#include <QPluginLoader>

#include "aboutwindow.h"
#include"../WidgetExplorerSDK/wdef.h"

namespace Ui { class MainWindow; }

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QStringList param, LightWidget *ptr, QWidget *parent = nullptr);
    ~MainWindow();
    void closeEvent(QCloseEvent *event);
    void tray(QSystemTrayIcon::ActivationReason reason);
    void initTable();
    void createCol(int col,QString title,QFont font,QColor color);
    void createRow(int row,  QPluginLoader* info);
    QStringList ReadLinkFile();
    LightWidget* ptr=nullptr;
    QLockFile* lock;
public slots:
    void showPanel();
private slots:
    void on_btnCmd_clicked();
    void on_tableWidget_cellDoubleClicked(int row, int column);
    void on_btnClear_clicked();
    void on_listLink_itemClicked(QListWidgetItem *item);
    void about();
    void reset();
private:
    Ui::MainWindow *ui;
    AboutWindow* aboutWnd=nullptr;
};
#endif // MAINWINDOW_H
