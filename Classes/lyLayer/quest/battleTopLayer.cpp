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

USING_NS_CC;
USING_NS_CC_EXT;


battleTopLayer::battleTopLayer()
: _isMoving(false)
{
}

battleTopLayer::~battleTopLayer()
{
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
    return false;
}

cocos2d::extension::Control::Handler battleTopLayer::onResolveCCBCCControlSelector(Ref* pTarget, const char* pSelectorName)
{
    return nullptr;
}
cocos2d::SEL_MenuHandler battleTopLayer::onResolveCCBCCMenuItemSelector(cocos2d::Ref * pTarget, const char* pSelectorName)
{
    //CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onPressButtonQQ", battleTopLayer::onPressButtonQQ);
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

void battleTopLayer::onPressButtonWeixin(cocos2d::Ref *sender)
{
    CCLOG("onPressButtonWeixin");
    ApplicationManager::getInstance()->changeScene(SCENE_TEST_SCENE);
}
void battleTopLayer::onPressButtonQQ(cocos2d::Ref *sender)
{
    CCLOG("onPressButtonQQ");
    //ApplicationManager::getInstance()->changeScene(SCENE_LOADING_TEXT);
}

