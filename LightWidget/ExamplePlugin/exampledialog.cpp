//Copyright 2025 HWorldY
//the Apache License, Version 2.0
//Author: HWorldY
#include "exampledialog.h"
#include "ui_exampledialog.h"
#include<windows.h>

ExampleDialog::ExampleDialog(QWidget *parent)
    : ui(new Ui::ExampleDialog)
{
    Q_UNUSED(parent);
    ui->setupUi(this);
}

ExampleDialog::~ExampleDialog()
{
    delete ui;
}

void ExampleDialog::setCommand(QMap<QString,QVariant> map){
    ui->textEdit->clear();
    QString str="";
    for(auto it=map.begin();it!=map.end();it++){
        str+=it.key();
        str+=":";
        str+=it->toString();
        str+="\n";
    }
    ui->textEdit->setText(str);
}
void ExampleDialog::appCommand(QMap<QString,QVariant> map){
    QString str="";
    for(auto it=map.begin();it!=map.end();it++){
        str+=it.key();
        str+=":";
        str+=it->toString();
        str+="\n";
    }
    appCommand(str);
}
void ExampleDialog::appCommand(QString str){
    QString org=ui->textEdit->toPlainText();
    str=org+str;
    ui->textEdit->setText(str);
}
