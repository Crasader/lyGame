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

void lyActionManager::LoadActionGroupLibrary()
{
    std::map<std::string, int> newMap;
    newMap.insert(std::pair<std::string, int>("TextureP/Role/Jingzhang/GC1",4));
    newMap.insert(std::pair<std::string, int>("TextureP/Role/Jingzhang/standby",19));
    

    this->LoadOneAction(newMap, 0);
}

void lyActionManager::AddGroup( lyActionGroup* pActGroup, unsigned int nGroupId )
{
    m_szGroupObj[nGroupId] = pActGroup;
}
void lyActionManager::AddGroup(int nGroupId)
{
    lyActionGroup* pNewGroup = lyActionGroup::Create();
    if (pNewGroup) {
        m_szGroupObj[nGroupId] = pNewGroup;
        
        lyAction* pAction = lyAction::Create();
        if (pAction)
        {
            for ( unsigned char byIndex = 0; byIndex < 9; byIndex++ )
            {
                char szName[50];
                memset(szName, 0, sizeof(char)*50 );
                sprintf(szName, "TextureP/Role/Jingzhang/run/%03d.png",byIndex);
                pAction->AddFrame(szName);
            }
            pNewGroup->AddAction(pAction, 0);
        }
        lyAction* pAction2 = lyAction::Create();
        if (pAction2)
        {
            for ( unsigned char byIndex = 0; byIndex < 16; byIndex++ )
            {
                char szName[50];
                memset(szName, 0, sizeof(char)*50 );
                sprintf(szName, "TextureP/Role/Jingzhang/skill1/%03d.png",byIndex);
                pAction2->AddFrame(szName);
            }
            pNewGroup->AddAction(pAction2, 1);
        }

    }

}

void lyActionManager::LoadOneAction(std::map<std::string,int> map, int nId)
{
    lyActionGroup* pNewGroup = lyActionGroup::Create();
    if (pNewGroup) {
        int nState = 0;
        for (auto iter = map.begin(); iter != map.end(); ++iter)
        {
            lyAction* pOneAction = lyAction::Create();
            if (pOneAction)
            {
                for ( unsigned char byIndex = 0; byIndex <= iter->second; byIndex++ )
                {
                    char szName[50];
                    memset(szName, 0, sizeof(char)*50 );
                    sprintf(szName, "%s/%03d.png",iter->first.c_str(),byIndex);
                    pOneAction->AddFrame(szName);
                }
                //默认state是待机动作，可以立即切换成别的状态，其他默认均不可，看需求
                if (nState)
                {
                    pOneAction->setDelay(true);
                }
                else
                {
                    pOneAction->setDelay(false);
                }
                pNewGroup->AddAction(pOneAction, nState++);
            }
        }
        lyActionManager::GetInstance()->AddGroup(pNewGroup, nId);
    }
    
    
}
lyActionGroup* lyActionManager::GetGroup( unsigned int nGroupId )
{
    return m_szGroupObj[nGroupId];
}
