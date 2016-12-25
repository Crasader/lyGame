//
//  lyActionManager.cpp
//  ly-Game
//
//  Created by loveyur on 2016/12/34
//  Copyright 2016 loveyur. All rights reserved.
//
//

#include "lyActionManager.h"
#include "cocos2d.h"

USING_NS_CC;

lyActionGroup* lyActionManager::m_szGroupObj[SZ_MAX_ACT_GROUP] = {NULL};
lyActionManager* lyActionManager::m_pInstance = NULL;


lyActionManager::lyActionManager()
{
}

lyActionManager::~lyActionManager()
{
}


lyActionManager* lyActionManager::GetInstance()
{
    if (!m_pInstance)
    {
        m_pInstance = new lyActionManager();
    }
    return m_pInstance;
}

void lyActionManager::AddGroup( lyActionGroup* pActGroup, unsigned int nGroupId )
{
    m_szGroupObj[nGroupId] = pActGroup;
}

lyActionGroup* lyActionManager::GetGroup( unsigned int nGroupId )
{
    return m_szGroupObj[nGroupId];
}
