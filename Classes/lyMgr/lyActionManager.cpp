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
#include "lyInclude.h"

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

void lyActionManager::loadAllAction()
{
    //加载所有动作组到内存中
    int nLineNum = lyTableLines("Table/RoleGroup.csv");
    
    for (int nGroupId = 1; nGroupId <= nLineNum; nGroupId++) {
        
        const MAP_ONE_LINE* szOneLine = lyTableOneLine("Table/RoleGroup.csv",nGroupId);
        if(szOneLine)
        {
            lyActionGroup* pNewGroup = lyActionGroup::Create();
            if (pNewGroup)
            {
                for (int nStatusIndex = 0; nStatusIndex < 5; nStatusIndex++) {
                    std::string strActionIndex = StringUtils::format("ActionId%d", nStatusIndex);
                    
                    int nActionId = lyStrToInt(szOneLine->find(strActionIndex)->second.c_str());
                    if (nActionId == 0) {
                        break;
                    }
                    lyAction* pOneAction = lyAction::Create();
                    if (pOneAction)
                    {
                        const MAP_ONE_LINE* szOneActionLine = lyTableOneLine("Table/RoleAction.csv", nActionId);
                        if(szOneActionLine)
                        {
                            int nActionMaxId = lyStrToInt(szOneActionLine->find("MaxId")->second.c_str());
                            std::string strActionPath = szOneActionLine->find("Path")->second.c_str();
                            int nWidth = lyStrToInt(szOneActionLine->find("Width")->second.c_str());
                            int nHeight = lyStrToInt(szOneActionLine->find("Height")->second.c_str());
                            int isPath = lyStrToInt(szOneActionLine->find("isPath")->second.c_str());
        
                            for ( unsigned char byIndex = 0; byIndex <= nActionMaxId; byIndex++ )
                            {
                                
                                std::string strFramePath = StringUtils::format(strActionPath.c_str(), byIndex,".png");
                                lyFrame* pFrame = NULL;
                                if (isPath) {
                                    pFrame = lyFrame::createWithSpritePath(strFramePath);
                                    if (pFrame) {
                                        pFrame->setAnchorPoint(Vec2(0,0));
                                        pFrame->setContentSize(Size(nWidth, nHeight));
                                        pOneAction->AddFrameByPath(strFramePath.c_str());
                                    }
                                }
                                else
                                {
                                    pFrame = lyFrame::createWithSpriteName(strFramePath);
                                    if (pFrame) {
                                        pFrame->setAnchorPoint(Vec2(0,0));
                                        pFrame->setContentSize(Size(nWidth, nHeight));
                                        pOneAction->AddFrameByName(strFramePath.c_str());
                                    }
                                }
                            }
                        }
                        pNewGroup->AddAction(pOneAction, nStatusIndex);
                    }
                }
                lyActionManager::GetInstance()->AddGroup(pNewGroup, nGroupId);
            }
        }
    }
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
                pAction->AddFrameByPath(szName);
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
                pAction2->AddFrameByPath(szName);
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
                    pOneAction->AddFrameByPath(szName);
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
