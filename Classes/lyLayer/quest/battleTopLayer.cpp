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
    m_bGameEnd = false;
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
    m_bGameEnd = false;
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
    if (m_bGameEnd) {
        CCLOG("是否充值继续游戏？");
        return;
    }
    if (m_bPause) {
        resumeGame();
    }
    else
        pauseGame();
}
void battleTopLayer::pauseGame()
{
    m_bPause = true;
    if (m_pPlane) {
        m_pPlane->setPause(m_bPause);
    }
}
void battleTopLayer::resumeGame()
{
    m_bPause = false;
    if (m_pPlane) {
        m_pPlane->setPause(m_bPause);
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
        if (bColl)
        {
            //CCLOG("-------碰撞了");
            //如果子弹血量0 则释放资源
            if (oneRain->isDead()) {
                oneRain->playMissAction();
                m_verEnemy.eraseObject(oneRain);
            }
            //计算伤害
            m_pPlane->calcHurt(oneRain);
            
            //如果飞机血量0 则停止游戏
            if (m_pPlane->isDead()) {
                m_bGameEnd = true;
                pauseGame();
            }
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

        m_pPlane->setDragSpan(0, 260, -50, 50);
        m_pPlane->setRoleId(15);
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
            info->Clear();
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
    lyUIBullet* pRain = lyUIBullet::Create();
    if (pRain)
    {
        pRain->setBulletId( lyRandInt(1, 15) );
        _roleArea->addChild(pRain);
        this->schedule(schedule_selector(battleTopLayer::EnemyStartMove), 0.1f);
        m_verEnemy.pushBack(pRain);
    }
}
