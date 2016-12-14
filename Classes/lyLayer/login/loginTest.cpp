//
//  loginTest.cpp
//  VitaminProject
//
//  Created by Shinji Hiramatsu on 2014/05/24.
//  Copyright 2014 GCREST,Inc. All rights reserved.
//

#include "loginTest.h"
#include "ApplicationManager.h"
#include "UISceneID.h"
#include "cocos2d.h"

USING_NS_CC;
USING_NS_CC_EXT;


loginTest::loginTest()
: _isMoving(false)
{
}

loginTest::~loginTest()
{
}


void loginTest::completedAnimationSequenceNamed(const char *name)
{
    doFinishScene();
}
void loginTest::onEnter()
{
    VitaminCoreLayer::onEnter();
}

void loginTest::onExit()
{
    VitaminCoreLayer::onExit();
}

bool loginTest::onAssignCCBMemberVariable(Ref *pTarget, const char *pMemberVariableName, Node *pNode)
{
    //CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "_nameLabel", cocos2d::Label*, _nameLabel);
    //CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "_buttonTest", ControlButton*, _buttonTest);
    
    return false;
}

cocos2d::extension::Control::Handler loginTest::onResolveCCBCCControlSelector(Ref* pTarget, const char* pSelectorName)
{
//    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressButtonQQ", loginTest::onPressButtonQQ);
//    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressButtonWeixin", loginTest::onPressButtonWeixin);
    //CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressButtonTest", loginTest::onPressButtonTest);
    
    return nullptr;
}
void loginTest::setSceneParameter(loginTestParameter *param)
{
    
}
bool loginTest::onTouchBegan(cocos2d::Touch* touches, cocos2d::Event* event)
{
    
    return true;
}

void loginTest::onTouchEnded(cocos2d::Touch* touches, cocos2d::Event* event)
{
  
}

void loginTest::doFinishScene()
{
}
void loginTest::onPressButtonWeixin(cocos2d::Ref *sender, cocos2d::extension::Control::EventType pControlEvent)
{
    CCLOG("onPressButtonWeixin");
    //ApplicationManager::getInstance()->changeScene(SCENE_LOADING_TEXT);

}
void loginTest::onPressButtonQQ(cocos2d::Ref *sender, cocos2d::extension::Control::EventType pControlEvent)
{
    CCLOG("onPressButtonQQ");
    //ApplicationManager::getInstance()->changeScene(SCENE_LOADING_TEXT);
    
}
void loginTest::onPressButtonTest(cocos2d::Ref *sender, cocos2d::extension::Control::EventType pControlEvent)
{
    CCLOG("onPressButtonTest");
}


