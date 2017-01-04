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

USING_NS_CC;
USING_NS_CC_EXT;


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
}
void battleTopLayer::onExit()
{
    lyBaseLayer::onExit();
    this->unschedule(schedule_selector(battleTopLayer::checkTestCollision));
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
    
    //playSe(SE_TOUCH);
    /*
    lyUIBase* pUI = lyUIBase::Create();
    if (pUI) {
        lyFrame* pSpr = lyFrame::create("images/head/pri_00024_s.png");
        if (pSpr) {
            pSpr->retain();
            pSpr->setPosition(0,0);
            pUI->addChild(pSpr);
        }
        pUI->setContentSize(Size(10,10));
        pUI->setPosition(randPosX(), randPosY());
        _roleArea->addChild(pUI);
    }
     */
    lyUIDrag* pUI = lyUIDrag::Create();
    if (pUI) {
        //pUI->setAnchorPoint(Point(0,0));
        pUI->setContentSize(Size(75,75));
        pUI->InitSpr("images/head/pri_00024_s.png");
        pUI->setPosition(randPosX(), randPosY());
        CCLOG("_roleArea x=%f, y=%f",_roleArea->getPosition().x,_roleArea->getPosition().y);
        _roleArea->addChild(pUI);
        
        int nInt = lyRandInt(0,3);
        if (1 == nInt) {
            m_lyLMTeam1.pushBack(pUI);
        }
        else
        {
            m_lyLMTeam2.pushBack(pUI);
        }
    }

    
}
void battleTopLayer::onClickAction1(cocos2d::Ref *sender)
{
    CCLOG("onClickAction1");
    if (m_pMyRole)
    {
        m_pMyRole->setAction(0);
        return;
    }
    else
    {
        m_pMyRole = lyUIRole::Create();
    }
     if (_roleArea && m_pMyRole) {
         m_pMyRole->setRoleId(0);
         m_pMyRole->setGroupId(0);
         m_pMyRole->setContentSize(Size(800,800));
         m_pMyRole->setPosition(randPosX(), randPosY());
         m_pMyRole->setTag(UIROLE_INDEX);
         CCLOG("_roleArea x=%f, y=%f",_roleArea->getPosition().x,_roleArea->getPosition().y);
         _roleArea->addChild(m_pMyRole);
     }

}
void battleTopLayer::onClickActionSkill(cocos2d::Ref *sender)
{
    CCLOG("onClickActionSkill");
    if (m_pMyRole) {
        m_pMyRole->setAction(1);
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
