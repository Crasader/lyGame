//
//  lyAction.cpp
//  ly-Game
//
//  Created by loveyur on 2016/12/34
//  Copyright 2016 loveyur. All rights reserved.
//
//

#include "lyAction.h"
#include "cocos2d.h"

USING_NS_CC;


lyAction::lyAction()
{
}

lyAction::~lyAction()
{
}
bool lyAction::init()
{
    return true;
}
lyAction* lyAction::Create()
{
    return new lyAction();
}

void lyAction::AddFrame( const char* pszImg )
{
    lyFrame* pFrame = lyFrame::create(pszImg);
    if (pFrame)
    {
        m_ObjFrames.AddLinkItem(pFrame);
    }
}

// void lyAction::OnFrame( float fDeltaTime )
// {
// 	if ( m_pCurrFrame )
// 	{
// 		m_pCurrFrame = m_ObjFrames.XML_GetNextItem(m_pCurrFrame);
// 		if (!m_pCurrFrame)
// 		{
// 			m_pCurrFrame = m_ObjFrames.XLM_GetHeader();
// 		}
// 	}
// }

// void lyAction::OnDraw( float fx,float fy,float fScale,unsigned char alpha )
// {
// 	if ( m_pCurrFrame )
// 	{
// 		m_pCurrFrame->setPosition(ccp(fx,fy));
// 		m_pCurrFrame->setScaleX( fScale );
// 		m_pCurrFrame->setScaleY( fScale );
// 		m_pCurrFrame->setOpacity( alpha );
// 		m_pCurrFrame->visit();
// 	}
//
// }


lyFrame* lyAction::GetNextFrame( lyFrame* pSpr )
{
    lyFrame* pNextSpr = NULL;
    if (!pSpr)
    {
        pNextSpr = m_ObjFrames.GetHeader();
    }
    else
    {
        pNextSpr = m_ObjFrames.GetNextItem(pSpr);
        if (!pNextSpr)
        {
            pNextSpr = m_ObjFrames.GetHeader();
        }
    }
    return pNextSpr;
}
