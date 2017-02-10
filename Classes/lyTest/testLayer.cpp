//
//  testLayer.cpp
//
//  ly-Game
//
//  Created by loveyur on 2016/12/14
//  Copyright 2016 loveyur. All rights reserved.
//
//

#include "testLayer.h"
#include "ApplicationManager.h"
#include "UISceneID.h"

#include "lyCSVReader.h"
#include "lyDefFunc.h"

#include "lyActionGroup.h"
#include "lyActionManager.h"
#include "lyPlistManager.h"
//#include "lyUIRole.h"


USING_NS_CC;
USING_NS_CC_EXT;


testLayer::testLayer()
: _isMoving(false)
, _nameLabel(nullptr)
,_rolelayer(nullptr)
{
}

testLayer::~testLayer()
{
    CC_SAFE_RELEASE_NULL(_nameLabel);
    CC_SAFE_RELEASE_NULL(_rolelayer);
}


void testLayer::completedAnimationSequenceNamed(const char *name)
{

}

void testLayer::onEnter()
{
    lyBaseLayer::onEnter();
}

void testLayer::onExit()
{
    lyBaseLayer::onExit();
}


bool testLayer::onAssignCCBMemberVariable(Ref *pTarget, const char *pMemberVariableName, Node *pNode)
{
    //CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "_sprtest", cocos2d::Sprite *, _sprtest);
    return false;
}

cocos2d::extension::Control::Handler testLayer::onResolveCCBCCControlSelector(Ref* pTarget, const char* pSelectorName)
{
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressCtrlButton", testLayer::onPressCtrlButton);
    return nullptr;
}
cocos2d::SEL_MenuHandler testLayer::onResolveCCBCCMenuItemSelector(cocos2d::Ref * pTarget, const char* pSelectorName)
{
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onPressBack", testLayer::onPressBack);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onPressStart", testLayer::onPressStart);
    return nullptr;
}

void testLayer::setSceneParameter(testLayerParameter *param)
{
    
}
bool testLayer::onTouchBegan(cocos2d::Touch* touches, cocos2d::Event* event)
{
    
    return true;
}

void testLayer::onTouchEnded(cocos2d::Touch* touches, cocos2d::Event* event)
{
  
}

void testLayer::onPressBack(cocos2d::Ref *sender)
{
    CCLOG("onPressBack");
    ApplicationManager::getInstance()->changeScene(SCENE_MAIN_TOP);
}
void testLayer::onPressStart(cocos2d::Ref *sender)
{
    CCLOG("onPressStart");
    
    
    
    
}
void testLayer::onPressCtrlButton(cocos2d::Ref *sender, cocos2d::extension::Control::EventType pControlEvent)
{
    ApplicationManager::getInstance()->changeScene(SCENE_MAIN_TOP);
}

