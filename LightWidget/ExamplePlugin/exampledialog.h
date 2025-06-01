//Copyright 2025 HWorldY
//the Apache License, Version 2.0
//Author: HWorldY
#ifndef EXAMPLEDIALOG_H
#define EXAMPLEDIALOG_H
#include <QDialog>
namespace Ui {
class ExampleDialog;
}
class ExamplePlugin;
class ExampleDialog : public QWidget
{
    Q_OBJECT
public:
    explicit ExampleDialog(QWidget *parent = nullptr);
    ~ExampleDialog();
    void setCommand(QMap<QString,QVariant> map);
    void appCommand(QMap<QString,QVariant> map);
    void appCommand(QString str);
    ExamplePlugin* plugin=nullptr;
private:
    Ui::ExampleDialog *ui;
};

#endif // EXAMPLEDIALOG_H
