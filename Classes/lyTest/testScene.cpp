//
//  testScene.cpp
//  VitaminProject
//
//  Created by Shinji Hiramatsu on 2014/05/24.
//  Copyright 2014 GCREST,Inc. All rights reserved.
//

#include "testScene.h"
#include "ApplicationManager.h"
#include "UISceneID.h"
#include "cocos2d.h"

USING_NS_CC;
USING_NS_CC_EXT;

testScene* testScene::create()
{
    //testScene* pRet = new (std::nothrow) testScene();
    cocosbuilder::CCBReader* reader = new cocosbuilder::CCBReader(cocosbuilder::NodeLoaderLibrary::getInstance());
    testScene *pRet = (testScene*)reader->readNodeGraphFromFile("testScene", nullptr, Director::getInstance()->getWinSize());
    //CC_SAFE_DELETE(reader);
    if (pRet && pRet->init())
    {
        pRet->autorelease();
        return pRet;
    }
    else
    {
        delete pRet;
        pRet = nullptr;
        return nullptr;
    }
}
testScene::testScene()
: _isMoving(false)
, _nameLabel(nullptr)
,_sprtest(nullptr)
{
}

testScene::~testScene()
{
    CC_SAFE_RELEASE_NULL(_nameLabel);
    CC_SAFE_RELEASE_NULL(_sprtest);
}


void testScene::completedAnimationSequenceNamed(const char *name)
{
    doFinishScene();
}

void testScene::onEnter()
{
    VitaminCoreLayer::onEnter();
    
}

bool testScene::onAssignCCBMemberVariable(Ref *pTarget, const char *pMemberVariableName, Node *pNode)
{
    //CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "_nameLabel", cocos2d::Label*, _nameLabel);
    //CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "_sprtest", cocos2d::Sprite *, _sprtest);
    return false;
}

cocos2d::extension::Control::Handler testScene::onResolveCCBCCControlSelector(Ref* pTarget, const char* pSelectorName)
{
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressButton", testScene::onClickedButton1);
    //CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressButton", testScene::onClickedButton2);
    return nullptr;
}
void testScene::setSceneParameter(testSceneParameter *param)
{
    
}
bool testScene::onTouchBegan(cocos2d::Touch* touches, cocos2d::Event* event)
{
    
    return true;
}

void testScene::onTouchEnded(cocos2d::Touch* touches, cocos2d::Event* event)
{
  
}

void testScene::doFinishScene()
{
}
void testScene::onClickedButton1(cocos2d::Ref *sender, cocos2d::extension::Control::EventType pControlEvent)
{
    CCLOG("onClickedButton1");
    if(_sprtest)
    {
        Texture2D* aTexture = TextureCache::sharedTextureCache()->addImage("btns/Cmn_Btn_Click.png");
        _sprtest->createWithTexture(aTexture);
    }
    else
        CCLOG("_sprtest is null");

    //_nameLabel->setString("点击有相应了！！");
}
void testScene::onClickedButton2(cocos2d::Ref *sender, cocos2d::extension::Control::EventType pControlEvent)
{
    CCLOG("onClickedButton2");
    if(_sprtest)
    {
        Texture2D* aTexture = TextureCache::sharedTextureCache()->addImage("btns/Cmn_Btn_Gray.png");
        _sprtest->createWithTexture(aTexture);
    }
    else
        CCLOG("_sprtest is null");
    //_nameLabel->setString("点击有相应了！！");
}
void testScene::btnNextLayer(cocos2d::Ref *sender, cocos2d::extension::Control::EventType pControlEvent)
{
    CCLOG("btnNextLayer");
    //_nameLabel->setString("切换场景！！！");
}
