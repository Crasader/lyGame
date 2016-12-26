//
//  mainTopLayer.cpp
//
//  ly-Game
//
//  Created by loveyur on 2016/12/14
//  Copyright 2016 loveyur. All rights reserved.
//
//

#include "mainTopLayer.h"
#include "ApplicationManager.h"
#include "UISceneID.h"
#include "cocos2d.h"

USING_NS_CC;
USING_NS_CC_EXT;


mainTopLayer::mainTopLayer()
: _isMoving(false)
{
}

mainTopLayer::~mainTopLayer()
{
}


void mainTopLayer::completedAnimationSequenceNamed(const char *name)
{
}

void mainTopLayer::onEnter()
{
    lyBaseLayer::onEnter();
    
}

bool mainTopLayer::onAssignCCBMemberVariable(Ref *pTarget, const char *pMemberVariableName, Node *pNode)
{
    return false;
}

cocos2d::extension::Control::Handler mainTopLayer::onResolveCCBCCControlSelector(Ref* pTarget, const char* pSelectorName)
{
    return nullptr;
}
cocos2d::SEL_MenuHandler mainTopLayer::onResolveCCBCCMenuItemSelector(cocos2d::Ref * pTarget, const char* pSelectorName)
{
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onClickMenuItem01", mainTopLayer::onClickMenuItem01);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onClickMenuItem02", mainTopLayer::onClickMenuItem02);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onClickMenuItem03", mainTopLayer::onClickMenuItem03);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onClickMenuItem04", mainTopLayer::onClickMenuItem04);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onClickMenuItem05", mainTopLayer::onClickMenuItem05);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onClickMenuItem06", mainTopLayer::onClickMenuItem06);
    return nullptr;
}
void mainTopLayer::setSceneParameter(mainTopLayerParameter *param)
{
    
}
bool mainTopLayer::onTouchBegan(cocos2d::Touch* touches, cocos2d::Event* event)
{
    
    return true;
}

void mainTopLayer::onTouchEnded(cocos2d::Touch* touches, cocos2d::Event* event)
{
  
}

void mainTopLayer::onClickMenuItem01(cocos2d::Ref *sender)
{
    CCLOG("onClickMenuItem01");
    
}
void mainTopLayer::onClickMenuItem02(cocos2d::Ref *sender)
{
    CCLOG("onClickMenuItem02");
    
}
void mainTopLayer::onClickMenuItem03(cocos2d::Ref *sender)
{
    CCLOG("onClickMenuItem03");
    
}
void mainTopLayer::onClickMenuItem04(cocos2d::Ref *sender)
{
    CCLOG("onClickMenuItem04");
    
}
void mainTopLayer::onClickMenuItem05(cocos2d::Ref *sender)
{
    CCLOG("onClickMenuItem05");
    
}
void mainTopLayer::onClickMenuItem06(cocos2d::Ref *sender)
{
    CCLOG("onClickMenuItem06");
    ApplicationManager::getInstance()->changeScene(SCENE_BATTLE_TOP);
}

