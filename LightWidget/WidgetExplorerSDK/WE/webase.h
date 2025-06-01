//Copyright 2025 HWorldY
//the Apache License, Version 2.0
//Author: HWorldY
#ifndef WEBASE_H
#define WEBASE_H
#include"../WDef/wedef.h"
#include"../WE/webasedata.h"
#include"../WE/weclass.h"

#include <QObject>
#include<QSharedPointer>

class WEBasePrivate;

class WE_NAMESPACE::WEBase
{
public:
    WEBase();
    virtual ~WEBase();
    virtual QSharedPointer<WEClass> getWEClass();
    virtual void setWEClass(QSharedPointer<WEClass> weclass);
    virtual QSharedPointer<WEBaseData> getWEBaseData();
    virtual void setWEBaseData(QSharedPointer<WEBaseData> webasedata);
private:
    WEBasePrivate* d=0;
};

Q_DECLARE_METATYPE(WE_NAMESPACE::WEBase);
Q_DECLARE_METATYPE(WE_NAMESPACE::WEBase*);

#endif // WEBASE_H
