//
//  VitaminCoreLayer.cpp
//  vitaminProject
//
//  Created by Shinji Hiramatsu on 2014/05/24.
//  Copyright 2014 GCREST,Inc. All rights reserved.
//

#include "VitaminCoreLayer.h"
#include "ApplicationManager.h"
#include "UISceneID.h"
#include "cocos2d.h"

USING_NS_CC;


VitaminCoreLayer::VitaminCoreLayer()    :
    CoreCCBLayer(),
    _caption(nullptr),
    _fadeLayer(nullptr),
    _multiTouchFilter(nullptr),
    _enableMultiTouch(false),
    _modules(),
    _retryFlg(false)
{
#ifdef VITAMIN_DEBUG_TOOL_ENABLE
    _backKeyEventListener = nullptr;
#endif
}

VitaminCoreLayer::~VitaminCoreLayer()
{
    for(auto module : _modules)
    {
        CC_SAFE_DELETE(module.second);
    }
}

void VitaminCoreLayer::onEnter()
{
    CoreLayer::onEnter();
    setAnimationManager();
    ApplicationManager::getInstance()->setWaitManager(this);

#ifdef VITAMIN_DEBUG_TOOL_ENABLE
    // デバッグ用仮想バックキー
    createDebugBackButton();
#endif

    // マルチタッチを抑制する
    _multiTouchFilter = EventListenerTouchOneByOne::create();
    _multiTouchFilter->setSwallowTouches(false);
    _multiTouchFilter->onTouchBegan = [this](Touch* touch, Event* event){
        if (!_enableMultiTouch) {
            if (touch->getID() > 0)
            {
                return true;
            }
        }
        return false;
    };
    _eventDispatcher->addEventListenerWithFixedPriority(_multiTouchFilter, -1);
}

void VitaminCoreLayer::onEnterTransitionDidFinish()
{
    CoreLayer::onEnterTransitionDidFinish();
}

void VitaminCoreLayer::onExit()
{
      if (_multiTouchFilter)
    {
        _eventDispatcher->removeEventListener(_multiTouchFilter);
        _multiTouchFilter = nullptr;
    }
#ifdef VITAMIN_DEBUG_TOOL_ENABLE
    if (_backKeyEventListener)
    {
        _eventDispatcher->removeEventListener(_backKeyEventListener);
        _backKeyEventListener = nullptr;
    }
#endif

    CoreCCBLayer::onExit();
}

void VitaminCoreLayer::onExitTransitionDidStart()
{
    CoreLayer::onExitTransitionDidStart();
}

void VitaminCoreLayer::setCaption(SceneID sid, bool isStatusBarVisible, CaptionDelegate *delegate)
{
 
    _caption->setButtonEnable(false);
    _caption->setVisible(false);
    
    _caption->setDelegate(delegate);
}

void VitaminCoreLayer::setCaptionEnable(bool enable)
{
    _caption->setButtonEnable(enable);
}

void VitaminCoreLayer::showCaption()
{
	if (_caption != nullptr) {
		_caption->setVisible(true);
		_caption->show();
	}
}

void VitaminCoreLayer::hideCaption()
{
    if (_caption) {
        _caption->hide();
    }
}

void VitaminCoreLayer::hideCaptionTitle()
{
    if (_caption) {
        _caption->setCaptionTileImgVisible(false);
    }
}


#pragma ローディング画面

#pragma 通信関連

void VitaminCoreLayer::eventConnectionStart(std::string tag){}

void VitaminCoreLayer::eventConnectionEnd(std::string tag, cocos2d::Ref *config){}

void VitaminCoreLayer::eventConnectionReview(){};

void VitaminCoreLayer::eventConnectionMaintenance(const cocos2d::ValueMap &data)
{
}


void VitaminCoreLayer::eventConnectionError(std::string tag, cocos2d::Ref *config)
{
 
}

void VitaminCoreLayer::eventConnectionRetryNotify(cocos2d::Ref *config, bool retryFlg)
{
   
}

void VitaminCoreLayer::waitrunWithScene(const SceneBuildInfo &sceneInfo)
{
    CCLOG("VitaminCoreLayer::waitrunWithScene");
    this->stopAllActions();
    this->runAction(Sequence::create(DelayTime::create(1.f), CallFunc::create([this, sceneInfo]() {
        CCLOG("VitaminCoreLayer::waitrunWithScene call runWithScene");
        ApplicationManager::getInstance()->runWithSceneExec(sceneInfo);
    }), NULL));
}

void VitaminCoreLayer::waitchangeScene(const SceneBuildInfo &sceneInfo)
{
    CCLOG("VitaminCoreLayer::waitchangeScene");
    this->stopAllActions();
    this->runAction(Sequence::create(DelayTime::create(1.f), CallFunc::create([this, sceneInfo]() {
        CCLOG("VitaminCoreLayer::waitchangeScene call changeScene");
        ApplicationManager::getInstance()->changeSceneExec(sceneInfo);
    }), NULL));
}

void VitaminCoreLayer::waitPushScene(const SceneBuildInfo &sceneInfo)
{
    CCLOG("VitaminCoreLayer::waitPushScene");
    this->stopAllActions();
    this->runAction(Sequence::create(DelayTime::create(1.f), CallFunc::create([this, sceneInfo]() {
        CCLOG("VitaminCoreLayer::waitPushScene call pushScene");
        ApplicationManager::getInstance()->pushSceneExec(sceneInfo);
    }), NULL));
}

void VitaminCoreLayer::waitPopScene()
{
    CCLOG("VitaminCoreLayer::waitPopScene");
    this->stopAllActions();
    this->runAction(Sequence::create(DelayTime::create(1.f), CallFunc::create([this]() {
        CCLOG("VitaminCoreLayer::waitPopScene call popScene");
        ApplicationManager::getInstance()->popScene();
    }), NULL));
}

void VitaminCoreLayer::waitChangePreviousScene()
{
    CCLOG("VitaminCoreLayer::waitChangePreviousScene");
    this->stopAllActions();
    this->runAction(Sequence::create(DelayTime::create(1.f), CallFunc::create([this]() {
        CCLOG("VitaminCoreLayer::waitChangePreviousScene call changePreviousScene");
        ApplicationManager::getInstance()->changePreviousScene();
    }), NULL));
}

void VitaminCoreLayer::eventConnectionUpdateApplication()
{
   
}

void VitaminCoreLayer::eventConnectionUpdateResource()
{
    
    
    
    
}

void VitaminCoreLayer::toResourceDownloadPage(float t)
{
   }


cocos2d::Rect VitaminCoreLayer::getMenuRect(const char* objectName) {
    cocos2d::Rect menuRect;
    return menuRect;
}

/**
 * メンテナンス画面に遷移
 */
void VitaminCoreLayer::moveMaintenenceScene()
{

}
void VitaminCoreLayer::eventConnectionUpdateMaster(bool refreshUserData)
{
}


