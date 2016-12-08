//
//  lyLogin.h
//  ly-client
//
//  Created by loveyur on 2016/11/10
//

#include "lyLogin.h"

lyLogin *lyLogin::m_plyLogin = nullptr;

lyLogin* lyLogin::getInstance()
{
    if (m_plyLogin == nullptr)
    {
        m_plyLogin = new lyLogin();
    }
    
    return m_plyLogin;
}

lyLogin::lyLogin()
{
	// TODO: auto generated code
}

lyLogin::~lyLogin()
{
	// TODO: auto generated code
}

