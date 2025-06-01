//Copyright 2025 HWorldY
//the Apache License, Version 2.0
//Author: HWorldY
#ifndef WCONFIG_H
#define WCONFIG_H
#include"../WDef/wedef.h"

#include<QString>

template<class T>class WConfigPrivate{
public:
    QMap<QString,T> map;
    QMap<QString,T> defaultMap;
    T defaultValue;
};

template <class T>
class WE_NAMESPACE::WConfig
{
public:
    WConfig();
    virtual ~WConfig();
    T get(QString key);
    bool setDefault(QString key, T value);
    bool hasArg(QString key);
    bool set(QString key, T value);
    void setDefaultValue(T value);
    QMap<QString, T> toMap();
    QMap<QString, T> toMapDefualt();
private:
    WConfigPrivate<T>* d=nullptr;
};

///
/// \brief WConfig::WConfig
///
template<class T>
WConfig<T>::WConfig() {
    this->d=new WConfigPrivate<T>;
}
///
/// \brief WConfig::~WConfig
///
template<class T>
WConfig<T>::~WConfig() {
    delete this->d;
}
///
/// \brief WConfig::get
/// \param key
/// \return
///
template<class T>
T WConfig<T>::get(QString key){
    if(!hasArg(key))return d->defaultValue;
    else return d->map.contains(key)?d->map[key]:d->defaultMap[key];
}
///
/// \brief WConfig::setDefault
/// \param key
/// \param value
/// \return
///
template<class T>
bool WConfig<T>::setDefault(QString key,T value){
    d->defaultMap[key]=value;
    return !d->map.contains(key);
}
///
/// \brief WConfig::hasArg
/// \param key
/// \return
///
template<class T>
bool WConfig<T>::hasArg(QString key){
    return d->defaultMap.contains(key)||d->map.contains(key);
}
///
/// \brief WConfig::set
/// \param key
/// \param value
/// \return
///
template<class T>
bool WConfig<T>::set(QString key,T value){
    bool res=false;
    if(hasArg(key))res=true;
    d->map.insert(key,value);
    return res;
}
///
/// \brief WConfig::setDefaultValue
/// \param value
///
template<class T>
void WConfig<T>::setDefaultValue(T value){
    d->defaultValue=value;
}
///
/// \brief WConfig::toMap
/// \return
///
template<class T>
QMap<QString,T> WConfig<T>::toMap(){
    return d->map;
}
///
/// \brief WConfig::toMapDefualt
/// \return
///
template<class T>
QMap<QString,T> WConfig<T>::toMapDefualt(){
    return d->defaultMap;
}
#endif // WCONFIG_H
