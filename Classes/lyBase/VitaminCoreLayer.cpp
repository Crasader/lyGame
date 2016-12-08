//
//  VitaminCoreLayer.cpp
//  vitaminProject
//
//  Created by Shinji Hiramatsu on 2014/05/24.
//  Copyright 2014 GCREST,Inc. All rights reserved.
//

#include "VitaminCoreLayer.h"
#include "ApplicationManager.h"

#include "VitaminSceneID.h"

#include "VitaminID.h"
#include "cocos2d.h"

USING_NS_CC;



VitaminCoreLayer::VitaminCoreLayer()  :
    CoreCCBLayer(),
    _modules()
{

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
}

void VitaminCoreLayer::onEnterTransitionDidFinish()
{
    CoreLayer::onEnterTransitionDidFinish();
}

void VitaminCoreLayer::onExit()
{
    CoreCCBLayer::onExit();
}

void VitaminCoreLayer::onExitTransitionDidStart()
{
    CoreLayer::onExitTransitionDidStart();
}




#pragma 通信関連

void VitaminCoreLayer::eventConnectionStart(std::string tag){}

void VitaminCoreLayer::eventConnectionEnd(std::string tag, cocos2d::Ref *config){}

void VitaminCoreLayer::eventConnectionReview(){};



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



