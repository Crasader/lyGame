//
//  lyTalkingdata.h
//  ly-client
//
//  Created by loveyur on 2016/11/10
//

#include "lyTalkingdata.h"

lyTalkingdata *lyTalkingdata::m_plyTalkingdata = nullptr;

lyTalkingdata* lyTalkingdata::getInstance()
{
    if (m_plyTalkingdata == nullptr)
    {
        m_plyTalkingdata = new lyTalkingdata();
    }
    
    return m_plyTalkingdata;
}

lyTalkingdata::lyTalkingdata()
{
	// TODO: auto generated code
}

lyTalkingdata::~lyTalkingdata()
{
	// TODO: auto generated code
}

