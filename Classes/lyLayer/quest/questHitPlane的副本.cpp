//
//  questHitPlane.cpp
//
//  ly-Game
//
//  Created by loveyur on 2016/12/14
//  Copyright 2016 loveyur. All rights reserved.
//
//

#include "questHitPlane.h"
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

bool questHitPlane::_canBorn = false;
int addNum = 0;


questHitPlane::questHitPlane()
: _isMoving(false)
,_roleArea(nullptr)
{
    m_pPlane = nullptr;
    m_bPause = false;
    m_bGameEnd = false;
}

questHitPlane::~questHitPlane()
{
    CC_SAFE_RELEASE_NULL(_roleArea);
    CC_SAFE_RELEASE_NULL(m_pPlane);
    
}


void questHitPlane::completedAnimationSequenceNamed(const char *name)
{
}

void questHitPlane::onEnter()
{
    lyBaseLayer::onEnter();

    m_bPause = false;
    m_bGameEnd = false;
    
    addNum = 0;
    
    //创建飞机
    BornOnePlane();
    
    //创建下落体
    this->schedule(schedule_selector(questHitPlane::BornOneEnemy), 0.5f);
    
    this->schedule(schedule_selector(questHitPlane::checkCollision), 0.1f);
    
    this->schedule(schedule_selector(questHitPlane::EnemyStartMove), 0.2f);
   
}
void questHitPlane::onExit()
{
    lyBaseLayer::onExit();
    this->unschedule(schedule_selector(questHitPlane::checkCollision));
 
    this->unschedule(schedule_selector(questHitPlane::BornOneEnemy));
    
    this->unschedule(schedule_selector(questHitPlane::EnemyStartMove));
    
}
bool questHitPlane::onAssignCCBMemberVariable(Ref *pTarget, const char *pMemberVariableName, Node *pNode)
{
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "_roleArea", cocos2d::Node*, _roleArea);
 
    return false;
}

cocos2d::extension::Control::Handler questHitPlane::onResolveCCBCCControlSelector(Ref* pTarget, const char* pSelectorName)
{
    return nullptr;
}
cocos2d::SEL_MenuHandler questHitPlane::onResolveCCBCCMenuItemSelector(cocos2d::Ref * pTarget, const char* pSelectorName)
{
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onClickMenuItem01", questHitPlane::onClickMenuItem01);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onClickPause", questHitPlane::onClickPause);
  
    return nullptr;
}
void questHitPlane::setSceneParameter(questHitPlaneParameter *param)
{
    
}
bool questHitPlane::onTouchBegan(cocos2d::Touch* touches, cocos2d::Event* event)
{
    
    return true;
}

void questHitPlane::onTouchEnded(cocos2d::Touch* touches, cocos2d::Event* event)
{
  
}

void questHitPlane::onClickMenuItem01(cocos2d::Ref *sender)
{
    CCLOG("onClickMenuItem01");
    ApplicationManager::getInstance()->changeScene(SCENE_MAIN_TOP);
}

void questHitPlane::onClickPause(cocos2d::Ref *sender)
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
void questHitPlane::pauseGame()
{
    m_bPause = true;
    if (m_pPlane) {
        m_pPlane->setPause(m_bPause);
    }
}
void questHitPlane::resumeGame()
{
    m_bPause = false;
    if (m_pPlane) {
        m_pPlane->setPause(m_bPause);
    }
}
int questHitPlane::randPosX()
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
int questHitPlane::randPosY()
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



void questHitPlane::BornOnePlane()
{
    int nRoleId = 3;
    /*
    m_pPlane = lyUIRole::Create();
    if (m_pPlane) {  
        m_pPlane->setRoleId(3);
        m_pPlane->setTouchEnabled(true);
        m_pPlane->setPosition(200, 0);
        const MAP_ONE_LINE* szOneLine = lyTableOneLine("Table/Role.csv",3);
        if(szOneLine)
        {
            int nWidth = lyStrToInt(szOneLine->find("Width")->second.c_str());
            int nHeight = lyStrToInt(szOneLine->find("Height")->second.c_str());
            m_pPlane->setContentSize(Size(nWidth,nHeight));
        }
        m_pPlane->setAnchorPoint(Vec2(0,0));
        m_pPlane->setDragSpan(10, 260, -50, 50);
        _roleArea->addChild(m_pPlane);
    }
 /*
        int randX = lyRandInt(2,200);
        nRoleId = 4;
        lyUIRole* pUIRole = lyUIRole::Create();
        if (pUIRole) {
            pUIRole->setRoleId(nRoleId);
            pUIRole->setTouchEnabled(true);
            
            const MAP_ONE_LINE* szOneLine = lyTableOneLine("Table/Role.csv",nRoleId);
            if(szOneLine)
            {
                int nWidth = lyStrToInt(szOneLine->find("Width")->second.c_str());
                int nHeight = lyStrToInt(szOneLine->find("Height")->second.c_str());
                pUIRole->setContentSize(Size(nWidth,nHeight));
            }
            pUIRole->setAnchorPoint(Vec2(0,0));
            pUIRole->setPosition(randX, 0);
            
            _roleArea->addChild(pUIRole);
        }
  
    nRoleId = 5;
    lyUIRole* pUIRoleNew = lyUIRole::Create();
    if (pUIRoleNew) {
        pUIRoleNew->setRoleId(nRoleId);
        pUIRoleNew->setTouchEnabled(true);
        
        const MAP_ONE_LINE* szOneLine = lyTableOneLine("Table/Role.csv",nRoleId);
        if(szOneLine)
        {
            int nWidth = lyStrToInt(szOneLine->find("Width")->second.c_str());
            int nHeight = lyStrToInt(szOneLine->find("Height")->second.c_str());
            pUIRoleNew->setContentSize(Size(nWidth,nHeight));
        }
        pUIRoleNew->setAnchorPoint(Vec2(0,0));
        pUIRoleNew->setPosition(200, 0);
        
        _roleArea->addChild(pUIRoleNew);
    }
         */
}
bool bCalcBlood = false;
void questHitPlane::checkCollision(float dt)
{
    if (m_bPause) {
        return;
    }
    if (m_pPlane) {
        for (auto oneRain : m_verEnemy)
        {
            bool bColl = m_pPlane->checkCollision(oneRain);
            if (bColl)
            {
                //如果子弹血量0 则释放资源
                //计算伤害
                oneRain->calcHurt(m_pPlane);
                m_pPlane->calcHurt(oneRain);
                
                if (oneRain->isDead()) {
                    oneRain->playMissAction();
                    m_verEnemy.eraseObject(oneRain);
                }
                
                if (bCalcBlood) {
                    //如果飞机血量0 则停止游戏
                    if (m_pPlane->isDead()) {
                        m_bGameEnd = true;
                        pauseGame();
                    }
                }
            }
            else
            {
                //CCLOG("-------");
            }
        }
        
    }
    
    
}
void questHitPlane::EnemyStartMove(float dt)
{
    if (m_bPause) {
        return;
    }
    for(auto &info : m_verEnemy )
    {
        /*
        if (info->isOutScreen())
        {
            info->Clear();
            m_verEnemy.eraseObject(info);
        }
        else
         //*/
        {
            Vec2 currPoint = info->getPosition();
  
                Vec2 moveVector = info->getMoveVector();
                info->setPosition(currPoint+moveVector);
           
            
        }
    }
}

//随机生成敌人 下落

void questHitPlane::BornOneEnemy(float dt)
{
    
    if (m_bPause) {
        return;
    }
    if (addNum > 3 ) {
        //return;
    }
    
    for (int nIndex = 0; nIndex < 1; nIndex++) {
        int nRoleId =  lyRandInt(4, 4);
        lyUIBullet* pUIBullet = lyUIBullet::Create();
        if (pUIBullet) {
            pUIBullet->setRoleId(nRoleId);
            pUIBullet->setTouchEnabled(false);
            
            const MAP_ONE_LINE* szOneLine = lyTableOneLine("Table/Role.csv",nRoleId);
            if(szOneLine)
            {
                int nWidth = lyStrToInt(szOneLine->find("Width")->second.c_str());
                int nHeight = lyStrToInt(szOneLine->find("Height")->second.c_str());
                pUIBullet->setContentSize(Size(nWidth,nHeight));
            }
            Size visibleSize = Director::getInstance()->getVisibleSize();
            int randX = lyRandInt(0,visibleSize.width);
            pUIBullet->setPosition( randX,visibleSize.height );
            pUIBullet->setRoute();
            pUIBullet->setAnchorPoint(Vec2(0,0));
            addNum++;
            _roleArea->addChild(pUIBullet);
            
            m_verEnemy.pushBack(pUIBullet);
        }
    }
    
   
}
