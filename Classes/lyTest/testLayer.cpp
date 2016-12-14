//
//  testLayer.cpp
//  VitaminProject
//
//  Created by Shinji Hiramatsu on 2014/05/24.
//  Copyright 2014 GCREST,Inc. All rights reserved.
//

#include "testLayer.h"
#include "ApplicationManager.h"
#include "UISceneID.h"
#include "cocos2d.h"

USING_NS_CC;
USING_NS_CC_EXT;


testLayer::testLayer()
: _isMoving(false)
, _nameLabel(nullptr)
,_sprtest(nullptr)
{
}

testLayer::~testLayer()
{
    CC_SAFE_RELEASE_NULL(_nameLabel);
    CC_SAFE_RELEASE_NULL(_sprtest);
}


void testLayer::completedAnimationSequenceNamed(const char *name)
{

}

void testLayer::onEnter()
{
    VitaminCoreLayer::onEnter();
}

void testLayer::onExit()
{
    VitaminCoreLayer::onExit();
}


bool testLayer::onAssignCCBMemberVariable(Ref *pTarget, const char *pMemberVariableName, Node *pNode)
{
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "_nameLabel", cocos2d::Label*, _nameLabel);
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
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onPressMenuButton", testLayer::onClickedMenuButton);
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

void testLayer::doFinishScene()
{
}
void testLayer::onClickedMenuButton(cocos2d::Ref *sender)
{
    CCLOG("onClickedMenuButton");
    if(_sprtest)
    {
        Texture2D* aTexture = TextureCache::sharedTextureCache()->addImage("btns/Cmn_Btn_Click.png");
        _sprtest->createWithTexture(aTexture);
    }
    else
        CCLOG("_sprtest is null");

    //_nameLabel->setString("点击有相应了！！");
}
void testLayer::onPressCtrlButton(cocos2d::Ref *sender, cocos2d::extension::Control::EventType pControlEvent)
{
    CCLOG("onPressCtrlButton");
    if(_sprtest)
    {
        Texture2D* aTexture = TextureCache::sharedTextureCache()->addImage("btns/Cmn_Btn_Click.png");
        _sprtest->createWithTexture(aTexture);
    }
    else
        CCLOG("_sprtest is null");
    
    //_nameLabel->setString("点击有相应了！！");
}

