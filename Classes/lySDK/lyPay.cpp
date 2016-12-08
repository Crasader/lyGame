//
//  lyPay.h
//  ly-client
//
//  Created by loveyur on 2016/11/10
//

#include "lyPay.h"

lyPay *lyPay::m_plyPay = nullptr;

lyPay* lyPay::getInstance()
{
    if (m_plyPay == nullptr)
    {
        m_plyPay = new lyPay();
    }
    
    return m_plyPay;
}

lyPay::lyPay()
{
	// TODO: auto generated code
}

lyPay::~lyPay()
{
	// TODO: auto generated code
}

