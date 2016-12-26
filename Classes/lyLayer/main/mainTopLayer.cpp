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
    //CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onPressButtonQQ", mainTopLayer::onPressButtonQQ);
   // CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onPressButtonWeixin", mainTopLayer::onPressButtonWeixin);
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

void mainTopLayer::onPressButtonWeixin(cocos2d::Ref *sender)
{
    CCLOG("onPressButtonWeixin");
    ApplicationManager::getInstance()->changeScene(SCENE_TEST_SCENE);
}
void mainTopLayer::onPressButtonQQ(cocos2d::Ref *sender)
{
    CCLOG("onPressButtonQQ");
    //ApplicationManager::getInstance()->changeScene(SCENE_LOADING_TEXT);
}

