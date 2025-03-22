//Copyright 2025 HWorldY
//the Apache License, Version 2.0
//Author: HWorldY
#include"we.h"
#include"webase.h"
WEBase* WE::m_instance=nullptr;
WE::WETYPE WE::t=WE_NONE;
bool WE::init(WEBase* base, WETYPE type)
{
    if (m_instance == nullptr) {
        t = type;
        m_instance = base;
    }
    else return false;
    return true;
}
WEBase* WE::inst(){
    return m_instance;
}
