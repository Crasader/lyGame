//
//  battleTopLayer.cpp
//
//  ly-Game
//
//  Created by loveyur on 2016/12/14
//  Copyright 2016 loveyur. All rights reserved.
//
//

#include "battleTopLayer.h"
#include "ApplicationManager.h"
#include "UISceneID.h"
#include "cocos2d.h"
#include "lyUIBase.h"
#include "lyDefFunc.h"
#include "lySoundID.h"
#include "lyActionManager.h"
#include "lyCSVReader.h"

#include "lyEventManager.h"

USING_NS_CC;
USING_NS_CC_EXT;

bool battleTopLayer::_canBorn = false;

battleTopLayer::battleTopLayer()
: _isMoving(false)
,_roleArea(nullptr)
{
    m_pPlane = nullptr;
    m_bPause = false;
}

battleTopLayer::~battleTopLayer()
{
    CC_SAFE_RELEASE_NULL(_roleArea);
    CC_SAFE_RELEASE_NULL(m_pPlane);
    
}


void battleTopLayer::completedAnimationSequenceNamed(const char *name)
{
}

void battleTopLayer::onEnter()
{
    lyBaseLayer::onEnter();

    m_bPause = false;
    //创建飞机
    BornOnePlane();
    
    //创建下落体
    this->schedule(schedule_selector(battleTopLayer::BornOneEnemy), 0.4f);
    
    this->schedule(schedule_selector(battleTopLayer::checkCollision), 0.1f);
   
}
void battleTopLayer::onExit()
{
    lyBaseLayer::onExit();
    this->unschedule(schedule_selector(battleTopLayer::checkCollision));
 
    this->unschedule(schedule_selector(battleTopLayer::BornOneEnemy));
}
bool battleTopLayer::onAssignCCBMemberVariable(Ref *pTarget, const char *pMemberVariableName, Node *pNode)
{
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "_roleArea", cocos2d::Node*, _roleArea);
 
    return false;
}

cocos2d::extension::Control::Handler battleTopLayer::onResolveCCBCCControlSelector(Ref* pTarget, const char* pSelectorName)
{
    return nullptr;
}
cocos2d::SEL_MenuHandler battleTopLayer::onResolveCCBCCMenuItemSelector(cocos2d::Ref * pTarget, const char* pSelectorName)
{
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onClickMenuItem01", battleTopLayer::onClickMenuItem01);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onClickPause", battleTopLayer::onClickPause);
  
    return nullptr;
}
void battleTopLayer::setSceneParameter(battleTopLayerParameter *param)
{
    
}
bool battleTopLayer::onTouchBegan(cocos2d::Touch* touches, cocos2d::Event* event)
{
    
    return true;
}

void battleTopLayer::onTouchEnded(cocos2d::Touch* touches, cocos2d::Event* event)
{
  
}

void battleTopLayer::onClickMenuItem01(cocos2d::Ref *sender)
{
    CCLOG("onClickMenuItem01");
    ApplicationManager::getInstance()->changeScene(SCENE_MAIN_TOP);
}

void battleTopLayer::onClickPause(cocos2d::Ref *sender)
{
    CCLOG("onClickPause");
    m_bPause = !m_bPause;
    if (m_pPlane) {
        m_pPlane->setCanDrag(m_bPause);
    }
}
int battleTopLayer::randPosX()
{
    float fStartX = 0;
    float fEndX = 0;
    int nPosX = 0;
    if (_roleArea)
    {
        fStartX = _roleArea->getPositionX();
        fEndX = fStartX + _roleArea->getContentSize().width;
    }
    
    nPosX = lyRandInt(fStartX,fEndX);
    CCLOG("randPosX=%d",nPosX);
}
int battleTopLayer::randPosY()
{
   
    float fStartY = 0;
    float fEndY = 0;
    int nPosY = 0;
    if (_roleArea)
    {
        fStartY = _roleArea->getPositionY();
        fEndY = fStartY + _roleArea->getContentSize().height;
    }
    nPosY = lyRandInt(fStartY,fEndY);
    CCLOG("randPosY=%d",nPosY);
    return nPosY;
}
void battleTopLayer::checkCollision(float dt)
{
    if (m_bPause) {
        return;
    }
    for (auto oneRain : m_verEnemy)
    {
        bool bColl = m_pPlane->checkCollision(oneRain);
        if (bColl) {
            CCLOG("-------碰撞了");
            oneRain->playMissEffect();
            m_verEnemy.eraseObject(oneRain);
        }
        else
        {
            //CCLOG("-------");
        }
    }
  
    
}


void battleTopLayer::BornOnePlane()
{
    m_pPlane = lyUIDrag::Create();
    if (m_pPlane) {
        
        m_pPlane->setContentSize(Size(75,75));
        m_pPlane->setSpritePath("images/head/pri_00024_s.png");
        m_pPlane->setPosition(200, 0);
        _roleArea->addChild(m_pPlane);
    }
}
void battleTopLayer::EnemyStartMove(float dt)
{
    if (m_bPause) {
        return;
    }
    for(auto &info : m_verEnemy )
    {
        if (info->isOutScreen())
        {
            info->playMissEffect();
            m_verEnemy.eraseObject(info);
        }
        else
        {
            Vec2 currPoint = info->getPosition();
            Vec2 diffPoint = info->getDiffPoint();
            info->setPosition(currPoint+diffPoint);
        }
    }
}
//随机生成敌人 下落
void battleTopLayer::BornOneEnemy(float dt)
{
    if (m_bPause) {
        return;
    }
    const MAP_ONE_LINE* szOneLine = lyTableOneLine("Table/Role.csv",1);
    if(szOneLine)
    {
        lyUIBullet* pRain = lyUIBullet::Create();
        if (pRain)
        {
            string strPath = szOneLine->find("Path")->second.c_str();
            int nWidth = lyStrToInt(szOneLine->find("Width")->second.c_str());
            int nHeight = lyStrToInt(szOneLine->find("Height")->second.c_str());
            int nBornXs = lyStrToInt(szOneLine->find("BornXs")->second.c_str());
            int nBornXe = lyStrToInt(szOneLine->find("BornXe")->second.c_str());
            int nBornYs = lyStrToInt(szOneLine->find("BornYs")->second.c_str());
            int nBornYe = lyStrToInt(szOneLine->find("BornYe")->second.c_str());
            
            int nEndXs = lyStrToInt(szOneLine->find("EndXs")->second.c_str());
            int nEndXe = lyStrToInt(szOneLine->find("EndXe")->second.c_str());
            int nEndYs = lyStrToInt(szOneLine->find("EndYs")->second.c_str());
            int nEndYe = lyStrToInt(szOneLine->find("EndYe")->second.c_str());
            
            pRain->setContentSize(Size(nWidth,nHeight));
            pRain->setPosition( Vec2(lyRandInt(nBornXs,nBornXe),lyRandInt(nBornYs,nBornYe)) );
            pRain->InitPoint( Vec2( lyRandInt(nBornXs,nBornXe),lyRandInt(nBornYs,nBornYe)) , Vec2( lyRandInt(nEndXs,nEndXe), lyRandInt(nEndYs,nEndYe) ));
            pRain->setButtlePath(strPath,0);
            _roleArea->addChild(pRain);
            this->schedule(schedule_selector(battleTopLayer::EnemyStartMove), 0.1f);
            m_verEnemy.pushBack(pRain);
        }
    }
}
