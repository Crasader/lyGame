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
:m_bDelay(false)
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
    lyFrame* pFrame = lyFrame::createWithSpritePath(pszImg);
    if (pFrame)
    {
        pFrame->retain();
        m_ObjFrames.AddLinkItem(pFrame);
    }
}

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
lyFrame* lyAction::GetHeaderFrame()
{
   return m_ObjFrames.GetHeader();
}
lyFrame* lyAction::GetTailFrame()
{
    return m_ObjFrames.GetTail();
}
