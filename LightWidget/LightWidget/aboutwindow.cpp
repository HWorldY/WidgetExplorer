//Copyright 2025 HWorldY
//the Apache License, Version 2.0
//Author: HWorldY
#include "aboutwindow.h"
#include "ui_aboutwindow.h"

AboutWindow::AboutWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::AboutWindow)
{
    ui->setupUi(this);
    ui->labelLink->setOpenExternalLinks(true);
}

AboutWindow::~AboutWindow()
{
    delete ui;
}
