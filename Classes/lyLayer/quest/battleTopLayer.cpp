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
,m_pMyRole(nullptr)
{
}

battleTopLayer::~battleTopLayer()
{
    CC_SAFE_RELEASE_NULL(_roleArea);
    CC_SAFE_RELEASE_NULL(m_pMyRole);
}


void battleTopLayer::completedAnimationSequenceNamed(const char *name)
{
}

void battleTopLayer::onEnter()
{
    lyBaseLayer::onEnter();
    this->schedule(schedule_selector(battleTopLayer::checkTestCollision), 0.2f);
    
    this->schedule(schedule_selector(battleTopLayer::StartBorn), 0.2f);
    CCLOG("=====_roleArea x=%f, y=%f",_roleArea->getPosition().x,_roleArea->getPosition().y);
    CCLOG("=====_roleArea w=%f, h=%f",_roleArea->getContentSize().width,_roleArea->getContentSize().height);

    
    
    //int nNum = lyTableLines("Table/TexturePlist.csv");
    //const MAP_MUTI_LINE* szlines = lyCSVReader::getInstance()->getOneFile("Table/TexturePlist.csv");
    
   
}
void battleTopLayer::onExit()
{
    lyBaseLayer::onExit();
    this->unschedule(schedule_selector(battleTopLayer::checkTestCollision));
    this->unschedule(schedule_selector(battleTopLayer::StartBorn));
}
bool battleTopLayer::onAssignCCBMemberVariable(Ref *pTarget, const char *pMemberVariableName, Node *pNode)
{
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "_roleArea", cocos2d::Node*, _roleArea);
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
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onClickDecRole", battleTopLayer::onClickDecRole);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onClickAddRole", battleTopLayer::onClickAddRole);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onClickAction1", battleTopLayer::onClickAction1);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onClickActionSkill", battleTopLayer::onClickActionSkill);
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
void battleTopLayer::onClickDecRole(cocos2d::Ref *sender)
{
    CCLOG("onClickDecRole");

    if (_roleArea) {
        if (_roleArea->getChildren().size()) {
            for(const auto& child: _roleArea->getChildren())
            {
                _roleArea->removeChild(child,true);
                return;
            }
        }
    }
}


void battleTopLayer::onClickAddRole(cocos2d::Ref *sender)
{
    CCLOG("onClickAddRole");

    lyUIDrag* pDrag = lyUIDrag::Create();
    if (pDrag) {
        
        pDrag->setContentSize(Size(75,75));
        pDrag->setSpritePath("images/head/pri_00024_s.png");
        pDrag->setPosition(randPosX(), randPosY());
        lyEventManager::RegEventCPP(UIEventType::UI_TOUCH_DOWN, battleTopLayer::BornDown, pDrag->GetObjID());
        lyEventManager::RegEventCPP(UIEventType::UI_TOUCH_UP, battleTopLayer::BornUp, pDrag->GetObjID());
        _roleArea->addChild(pDrag);
        
        int nInt = lyRandInt(0,3);
        //if (1 == nInt) {
        if (true) {
            m_lyLMTeam1.pushBack(pDrag);
        }
        else
        {
            m_lyLMTeam2.pushBack(pDrag);
        }
    }

    
}
void battleTopLayer::BornDown(long nObjId)
{
    CCLOG("BornDown nObjId=%ld",nObjId);
    _canBorn = true;
}
void battleTopLayer::BornUp(long nObjId)
{
    CCLOG("BornUp nObjId=%ld",nObjId);
    _canBorn = false;
}
void battleTopLayer::StartBorn(float dt)
{
    if (_canBorn) {
        lyUIBullet* pBullet = lyUIBullet::Create();
        if (pBullet) {
            pBullet->setContentSize(Size(75,75));
            pBullet->setPosition( Vec2(lyRandInt(0,500),lyRandInt(0,100)) );
            pBullet->InitPoint( Vec2(lyRandInt(0,500),lyRandInt(0,100)) , Vec2(200, 800));
            pBullet->InitBulletPath("images/head/pri_00024_s.png");
            _roleArea->addChild(pBullet);
            this->schedule(schedule_selector(battleTopLayer::checkBullet), 0.1f);
            
            m_lyLMBullet.pushBack(pBullet);
        }
    }
    
}
void battleTopLayer::onClickAction1(cocos2d::Ref *sender)
{
    CCLOG("onClickAction1");
    /*
    lyUIBullet* pBullet = lyUIBullet::Create();
    if (pBullet) {
        pBullet->setContentSize(Size(75,75));
        pBullet->setPosition(randPosX(), randPosY());
        pBullet->InitPoint(Vec2(120,180 ), Vec2(200, 800));
        pBullet->InitBulletPath("images/head/pri_00024_s.png");
        _roleArea->addChild(pBullet);
        this->schedule(schedule_selector(battleTopLayer::checkBullet), 0.1f);
        
        m_lyLMBullet.pushBack(pBullet);
    }
     */
}

void battleTopLayer::checkBullet(float dt)
{
    for(auto &info : m_lyLMBullet)
    {
        if (info->isOutScreen()) {
            m_lyLMBullet.eraseObject(info);
        }
        else
        {
            Vec2 currPoint = info->getPosition();
            Vec2 diffPoint = info->getDiffPoint();
            info->setPosition(currPoint+diffPoint);
        }
        
    }
}
void battleTopLayer::onClickActionSkill(cocos2d::Ref *sender)
{
    
    CCLOG("onClickActionSkill");
    /*
    if (m_pMyRole) {
        m_pMyRole->setAction(1);
    }
     */
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
void battleTopLayer::checkTestCollision(float dt)
{
    //CCLOG("-------checkCollision");
    
    Size sizeT = this->getContentSize();
    float fMax = lyMax(sizeT.width, sizeT.height);
    float fMin = lyMin(sizeT.width, sizeT.height);
    
    for (auto childTeam1 : m_lyLMTeam1)
    {
        for (auto childTeam2 : m_lyLMTeam2)
        {
            bool bColl = childTeam1->checkCollision(childTeam2);
            if (bColl) {
                CCLOG("-------碰撞了");
            }
            else
            {
                //CCLOG("-------");
            }
        }
    }
    
}
