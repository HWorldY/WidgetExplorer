#ifndef SIDEBAR_H
#define SIDEBAR_H

#include <QGridLayout>
#include <QWidget>
#include<QVector>
#include<QButtonGroup>
#include<QToolButton>
#include<QStackedWidget>

class SideBar : public QWidget
{
    Q_OBJECT

public:
    explicit SideBar(QWidget *parent = nullptr);
    void setBtnCount(unsigned int count);
    void setButtonContent(unsigned int index, QString content);
    void connectStack(QStackedWidget* stackedWidget);
    ~SideBar();
    QStackedWidget* stack;
private slots:
    void onButtonClicked();

private:
    QButtonGroup btnGroup;
};

#endif // SIDEBAR_H
