//
//  loginLayer.cpp
//
//  ly-Game
//
//  Created by loveyur on 2016/12/14
//  Copyright 2016 loveyur. All rights reserved.
//
//

#include "loginLayer.h"
#include "ApplicationManager.h"
#include "UISceneID.h"
#include "cocos2d.h"

USING_NS_CC;
USING_NS_CC_EXT;


loginLayer::loginLayer()
: _isMoving(false)
{
}

loginLayer::~loginLayer()
{
}


void loginLayer::completedAnimationSequenceNamed(const char *name)
{
}

void loginLayer::onEnter()
{
    lyBaseLayer::onEnter();
    
}

bool loginLayer::onAssignCCBMemberVariable(Ref *pTarget, const char *pMemberVariableName, Node *pNode)
{
    return false;
}

cocos2d::extension::Control::Handler loginLayer::onResolveCCBCCControlSelector(Ref* pTarget, const char* pSelectorName)
{
    return nullptr;
}
cocos2d::SEL_MenuHandler loginLayer::onResolveCCBCCMenuItemSelector(cocos2d::Ref * pTarget, const char* pSelectorName)
{
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onPressButtonQQ", loginLayer::onPressButtonQQ);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onPressButtonWeixin", loginLayer::onPressButtonWeixin);
    return nullptr;
}
void loginLayer::setSceneParameter(loginLayerParameter *param)
{
    
}
bool loginLayer::onTouchBegan(cocos2d::Touch* touches, cocos2d::Event* event)
{
    
    return true;
}

void loginLayer::onTouchEnded(cocos2d::Touch* touches, cocos2d::Event* event)
{
  
}

void loginLayer::onPressButtonWeixin(cocos2d::Ref *sender)
{
    CCLOG("onPressButtonWeixin");
    ApplicationManager::getInstance()->changeScene(SCENE_TEST_SCENE);
}
void loginLayer::onPressButtonQQ(cocos2d::Ref *sender)
{
    CCLOG("onPressButtonQQ");
    //ApplicationManager::getInstance()->changeScene(SCENE_LOADING_TEXT);
}

