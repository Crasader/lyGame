//
//  loadingText.cpp
//  VitaminProject
//
//  Created by Shinji Hiramatsu on 2014/05/24.
//  Copyright 2014 GCREST,Inc. All rights reserved.
//

#include "loadingText.h"
#include "ApplicationManager.h"
#include "UISceneID.h"
#include "cocos2d.h"

USING_NS_CC;
USING_NS_CC_EXT;


loadingText::loadingText()
: _isMoving(false)
{
}

loadingText::~loadingText()
{
}


void loadingText::completedAnimationSequenceNamed(const char *name)
{
    doFinishScene();
}

void loadingText::onEnter()
{
    VitaminCoreLayer::onEnter();
    
}
void loadingText::setSceneParameter(loadingTextParameter *param)
{
 
}
bool loadingText::onAssignCCBMemberVariable(Ref *pTarget, const char *pMemberVariableName, Node *pNode)
{
    //CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "_nameLabel", cocos2d::Label*, _nameLabel);
    return false;
}

cocos2d::extension::Control::Handler loadingText::onResolveCCBCCControlSelector(Ref* pTarget, const char* pSelectorName)
{
    //CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressButton", loadingText::onClickedButton1);
    return nullptr;
}

bool loadingText::onTouchBegan(cocos2d::Touch* touches, cocos2d::Event* event)
{
    
    return true;
}

void loadingText::onTouchEnded(cocos2d::Touch* touches, cocos2d::Event* event)
{
  
}

void loadingText::doFinishScene()
{
}
void loadingText::onClickedButton1(cocos2d::Ref *sender, cocos2d::extension::Control::EventType pControlEvent)
{
    CCLOG("onClickedButton1");
}

