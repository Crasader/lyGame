//
//  lyEventManager.cpp
//  ly-Game
//
//  Created by loveyur on 2016/12/34
//  Copyright 2016 loveyur. All rights reserved.
//
//

#include "lyEventManager.h"
#include "cocos2d.h"

USING_NS_CC;


lyEventManager::lyEventManager()
{
}

lyEventManager::~lyEventManager()
{
    if (m_EventInstance)
    {
        delete m_EventInstance;
    }
}


lyEventManager* lyEventManager::m_EventInstance = 0;
lyLinkMgr<lyEvent> lyEventManager::m_objEventMgr;


lyEventManager* lyEventManager::getInstance()
{
    if (!m_EventInstance)
    {
        m_EventInstance = new lyEventManager();
    }
    return m_EventInstance;
}
void lyEventManager::RegEventCPP( UIEventType byType,XEventCallBack pCallBackFunc, long dwObjID )
{
    
    lyEvent* pEvent = lyEvent::Create();
    if (pEvent)
    {
        pEvent->m_byType = byType;
        pEvent->m_dwObjID = dwObjID;
        pEvent->m_CallBackFunc = pCallBackFunc;
        m_objEventMgr.AddLinkItem(pEvent);
    }
    
}
void lyEventManager::ExecuteEventCPP( UIEventType byType, long dwObjID ,long dwParam /*= 0 */ )
{
    lyEvent* pEvent = m_objEventMgr.GetHeader();
    while (1)
    {
        if (!pEvent)
        {
            return;
        }
        if ( pEvent  && pEvent->m_byType == byType && pEvent->m_dwObjID == dwObjID)
        {
            pEvent->m_CallBackFunc(dwObjID);
            return;
        }
        pEvent = m_objEventMgr.GetNextItem(pEvent);
    }
}
void lyEventManager::ClearEvents( int eventID, long objGuid )
{

}
