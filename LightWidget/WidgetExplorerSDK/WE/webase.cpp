//Copyright 2025 HWorldY
//the Apache License, Version 2.0
//Author: HWorldY
#include "webase.h"
class WEBasePrivate{
public:
    WEBasePrivate(WEBase* base):
        weclass(QSharedPointer<WEClass>(new WEClass(base))),
        webasedata(QSharedPointer<WEBaseData>(new WEBaseData)){
        };
    QSharedPointer<WEClass> weclass;
    QSharedPointer<WEBaseData> webasedata;
};
///
/// \brief WEBase::WEBase
///
WEBase::WEBase() {
    this->d=new WEBasePrivate(this);
}
///
/// \brief WEBase::~WEBase
///
WEBase::~WEBase(){
    if(d)delete d;
    d=nullptr;
}
///
/// \brief WEBase::getWEClass
/// \return
///
QSharedPointer<WEClass> WEBase::getWEClass(){
    return d->weclass;
}
///
/// \brief WEBase::setWEClass
/// \param weclass
///
void WEBase::setWEClass(QSharedPointer<WEClass> weclass){
    d->weclass=weclass;
}
///
/// \brief WEBase::getWEBaseData
/// \return
///
QSharedPointer<WEBaseData> WEBase::getWEBaseData(){
    return d->webasedata;
}
///
/// \brief WEBase::setWEBaseData
/// \param webasedata
///
void WEBase::setWEBaseData(QSharedPointer<WEBaseData> webasedata){
    d->webasedata=webasedata;
}
