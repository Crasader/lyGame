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


USING_NS_CC;
USING_NS_CC_EXT;


battleTopLayer::battleTopLayer()
: _isMoving(false)
,_roleArea(nullptr)
{
}

battleTopLayer::~battleTopLayer()
{
    CC_SAFE_RELEASE_NULL(_roleArea);
}


void battleTopLayer::completedAnimationSequenceNamed(const char *name)
{
}

void battleTopLayer::onEnter()
{
    lyBaseLayer::onEnter();
    
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
    //CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onPressButtonWeixin", battleTopLayer::onPressButtonWeixin);
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

#include "lyFrame.h"
void battleTopLayer::onClickAddRole(cocos2d::Ref *sender)
{
    CCLOG("onClickAddRole");
    float fStartX = 0;
    float fStartY = 0;
    float fEndX = 0;
    float fEndY = 0;
    if (_roleArea)
    {
        fStartX = _roleArea->getPositionX();
        fStartY = _roleArea->getPositionY();
        fEndX = fStartX + _roleArea->getContentSize().width;
        fEndY = fStartY + _roleArea->getContentSize().height;
    }
    int posX = lyRandInt(fStartX,fEndX);
    int posY = lyRandInt(fStartY,fEndY);
    
    
    lyUIBase* pUI = lyUIBase::Create();
    if (pUI) {
        lyFrame* pSpr = lyFrame::create("images/head/pri_00024_s.png");
        if (pSpr) {
            pSpr->setPosition(0,0);
            pUI->addChild(pSpr);
        }
        pUI->setContentSize(Size(10,10));
        pUI->setPosition(posX, posY);
        _roleArea->addChild(pUI);
    }
    
    
    
    
}

