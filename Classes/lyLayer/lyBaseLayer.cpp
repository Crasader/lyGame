//
//  lyBaseLayer.cpp
//
//  ly-Game
//
//  Created by loveyur on 2016/12/14
//  Copyright 2016 loveyur. All rights reserved.
//
//

#include "lyBaseLayer.h"
#include "ApplicationManager.h"
#include "UISceneID.h"
#include "cocos2d.h"

USING_NS_CC;


lyBaseLayer::lyBaseLayer()    :
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

lyBaseLayer::~lyBaseLayer()
{
    for(auto module : _modules)
    {
        CC_SAFE_DELETE(module.second);
    }
}

void lyBaseLayer::onEnter()
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

void lyBaseLayer::onEnterTransitionDidFinish()
{
    CoreLayer::onEnterTransitionDidFinish();
}

void lyBaseLayer::onExit()
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

void lyBaseLayer::onExitTransitionDidStart()
{
    CoreLayer::onExitTransitionDidStart();
}

void lyBaseLayer::setCaption(SceneID sid, bool isStatusBarVisible, CaptionDelegate *delegate)
{
 
    _caption->setButtonEnable(false);
    _caption->setVisible(false);
    
    _caption->setDelegate(delegate);
}

void lyBaseLayer::setCaptionEnable(bool enable)
{
    _caption->setButtonEnable(enable);
}

void lyBaseLayer::showCaption()
{
	if (_caption != nullptr) {
		_caption->setVisible(true);
		_caption->show();
	}
}

void lyBaseLayer::hideCaption()
{
    if (_caption) {
        _caption->hide();
    }
}

void lyBaseLayer::hideCaptionTitle()
{
    if (_caption) {
        _caption->setCaptionTileImgVisible(false);
    }
}


#pragma ローディング画面

#pragma 通信関連

void lyBaseLayer::eventConnectionStart(std::string tag){}

void lyBaseLayer::eventConnectionEnd(std::string tag, cocos2d::Ref *config){}

void lyBaseLayer::eventConnectionReview(){};

void lyBaseLayer::eventConnectionMaintenance(const cocos2d::ValueMap &data)
{
}


void lyBaseLayer::eventConnectionError(std::string tag, cocos2d::Ref *config)
{
 
}

void lyBaseLayer::eventConnectionRetryNotify(cocos2d::Ref *config, bool retryFlg)
{
   
}

void lyBaseLayer::waitrunWithScene(const SceneBuildInfo &sceneInfo)
{
    CCLOG("lyBaseLayer::waitrunWithScene");
    this->stopAllActions();
    this->runAction(Sequence::create(DelayTime::create(1.f), CallFunc::create([this, sceneInfo]() {
        CCLOG("lyBaseLayer::waitrunWithScene call runWithScene");
        ApplicationManager::getInstance()->runWithSceneExec(sceneInfo);
    }), NULL));
}

void lyBaseLayer::waitchangeScene(const SceneBuildInfo &sceneInfo)
{
    CCLOG("lyBaseLayer::waitchangeScene");
    this->stopAllActions();
    this->runAction(Sequence::create(DelayTime::create(1.f), CallFunc::create([this, sceneInfo]() {
        CCLOG("lyBaseLayer::waitchangeScene call changeScene");
        ApplicationManager::getInstance()->changeSceneExec(sceneInfo);
    }), NULL));
}

void lyBaseLayer::waitPushScene(const SceneBuildInfo &sceneInfo)
{
    CCLOG("lyBaseLayer::waitPushScene");
    this->stopAllActions();
    this->runAction(Sequence::create(DelayTime::create(1.f), CallFunc::create([this, sceneInfo]() {
        CCLOG("lyBaseLayer::waitPushScene call pushScene");
        ApplicationManager::getInstance()->pushSceneExec(sceneInfo);
    }), NULL));
}

void lyBaseLayer::waitPopScene()
{
    CCLOG("lyBaseLayer::waitPopScene");
    this->stopAllActions();
    this->runAction(Sequence::create(DelayTime::create(1.f), CallFunc::create([this]() {
        CCLOG("lyBaseLayer::waitPopScene call popScene");
        ApplicationManager::getInstance()->popScene();
    }), NULL));
}

void lyBaseLayer::waitChangePreviousScene()
{
    CCLOG("lyBaseLayer::waitChangePreviousScene");
    this->stopAllActions();
    this->runAction(Sequence::create(DelayTime::create(1.f), CallFunc::create([this]() {
        CCLOG("lyBaseLayer::waitChangePreviousScene call changePreviousScene");
        ApplicationManager::getInstance()->changePreviousScene();
    }), NULL));
}

void lyBaseLayer::eventConnectionUpdateApplication()
{
   
}

void lyBaseLayer::eventConnectionUpdateResource()
{
    
    
    
    
}

void lyBaseLayer::toResourceDownloadPage(float t)
{
   }


cocos2d::Rect lyBaseLayer::getMenuRect(const char* objectName) {
    cocos2d::Rect menuRect;
    return menuRect;
}

/**
 * メンテナンス画面に遷移
 */
void lyBaseLayer::moveMaintenenceScene()
{

}
void lyBaseLayer::eventConnectionUpdateMaster(bool refreshUserData)
{
}


