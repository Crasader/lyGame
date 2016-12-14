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
    doFinishScene();
}

void loginLayer::onEnter()
{
    lyBaseLayer::onEnter();
    
}

bool loginLayer::onAssignCCBMemberVariable(Ref *pTarget, const char *pMemberVariableName, Node *pNode)
{
    //CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "_nameLabel", cocos2d::Label*, _nameLabel);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "_buttonTest", ControlButton*, _buttonTest);
    
    return false;
}

cocos2d::extension::Control::Handler loginLayer::onResolveCCBCCControlSelector(Ref* pTarget, const char* pSelectorName)
{
//    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressButtonQQ", loginLayer::onPressButtonQQ);
//    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressButtonWeixin", loginLayer::onPressButtonWeixin);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressButtonTest", loginLayer::onPressButtonTest);
    
    return nullptr;
}
cocos2d::SEL_MenuHandler loginLayer::onResolveCCBCCMenuItemSelector(cocos2d::Ref * pTarget, const char* pSelectorName)
{
    //CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onPressMenuButton", testLayer::onClickedMenuButton);
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

void loginLayer::doFinishScene()
{
}
void loginLayer::onPressButtonWeixin(cocos2d::Ref *sender, cocos2d::extension::Control::EventType pControlEvent)
{
    CCLOG("onPressButtonWeixin");
    //ApplicationManager::getInstance()->changeScene(SCENE_LOADING_TEXT);

}
void loginLayer::onPressButtonQQ(cocos2d::Ref *sender, cocos2d::extension::Control::EventType pControlEvent)
{
    CCLOG("onPressButtonQQ");
    //ApplicationManager::getInstance()->changeScene(SCENE_LOADING_TEXT);
    
}
void loginLayer::onPressButtonTest(cocos2d::Ref *sender, cocos2d::extension::Control::EventType pControlEvent)
{
    CCLOG("onPressButtonTest");
}


