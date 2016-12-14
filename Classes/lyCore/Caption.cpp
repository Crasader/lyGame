
//file  Caption.cpp
//
//  ly-Game
//
//  Created by loveyur on 2016/11/11
//  Copyright 2016 loveyur. All rights reserved.
//
//

#include "Caption.h"

USING_NS_CC;

// constructor
Caption::Caption()
: CoreLayer()
, _delegate(nullptr)
, _backButton(nullptr)
, _captionName(nullptr)
, _animationManager(nullptr)
, _backButtonTxt(nullptr)
, _captionTitleImg(nullptr)
{
}

// destructor
Caption::~Caption() {
    CC_SAFE_RELEASE_NULL(_backButton);
    CC_SAFE_RELEASE_NULL(_captionName);
    CC_SAFE_RELEASE_NULL(_backButtonTxt);
}

void Caption::onEnter()
{
    CoreLayer::onEnter();
    if (this->getUserObject() != nullptr) {
        // アニメーションマネージャー設定
        _animationManager = (cocosbuilder::CCBAnimationManager *)this->getUserObject();
        _animationManager->setDelegate(this);
    }
}

void Caption::onEnterTransitionDidFinish()
{
    CoreLayer::onEnterTransitionDidFinish();
}

void Caption::onExit()
{
    CoreLayer::onExit();
    
    if (_animationManager != nullptr) {
        _animationManager->setDelegate(nullptr);
    }
}

void Caption::onExitTransitionDidStart()
{
    CoreLayer::onExitTransitionDidStart();
}

bool Caption::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event)
{
    Rect rect = this->getBoundingBox();
    if (rect.containsPoint(touch->getLocation()))
    {
        return true;
    }
    return false;
}

void Caption::onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *unused_event)
{
    
}

void Caption::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event)
{
    
}

bool Caption::onAssignCCBMemberVariable(Ref *pTarget, const char *pMemberVariableName, Node *pNode) {
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "backButton", cocos2d::extension::ControlButton *, _backButton);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "captionName", cocos2d::Label *, _captionName);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "backButtonTxt", cocos2d::Label *, _backButtonTxt);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "captionTitleImg", cocos2d::Sprite *, _captionTitleImg);
    
    return false;
}

cocos2d::extension::Control::Handler Caption::onResolveCCBCCControlSelector(cocos2d::Ref * pTarget, const char* pSelectorName) {
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "pressedBack:", Caption::pressedBack);

    return NULL;
}

void Caption::completedAnimationSequenceNamed(const char *name)
{
    if (strcmp(name, "start") == 0)
    {
        if (_delegate != nullptr)
        {
            _delegate->notifyCaptionStartComplete(this);
        }
    }
    else if (strcmp(name, "end") == 0)
    {
        if (_delegate != nullptr)
        {
            _delegate->notifyCaptionEndComplete(this);
        }
        
    }
}

void Caption::pressedBack(cocos2d::Ref *pSender, cocos2d::extension::Control::EventType type)
{
    if (type == cocos2d::extension::Control::EventType::TOUCH_UP_INSIDE) {
        if (_delegate != nullptr)
        {
            _delegate->pressedBack(this);
        }
    }
}

CaptionDelegate* Caption::getDelegate()
{
    return _delegate;
}

void Caption::setDelegate(CaptionDelegate *pDelegate)
{
    _delegate = pDelegate;
}

void Caption::setBackVisible(bool visible)
{
    _backButton->setVisible(visible);
    _backButtonTxt->setVisible(visible);
}

void Caption::setCaptionName(std::string captionName)
{
    _captionName->setString(captionName);
}

void Caption::setCaptionTileImgVisible(bool visible)
{
    _captionTitleImg->setVisible(visible);
}

void Caption::setButtonEnable(bool enable)
{
    _backButton->setEnabled(enable);
}

bool Caption::getButtonEnable()
{
    return _backButton->isEnabled();
}

void Caption::show()
{
    auto runningAnimation = _animationManager->getRunningSequenceName();
    if (runningAnimation && strcmp(runningAnimation, "start") == 0)
    {
        return;
    }

    _animationManager->runAnimationsForSequenceNamed("start");
}

void Caption::hide()
{
    auto runningAnimation = _animationManager->getRunningSequenceName();
    if (runningAnimation && strcmp(runningAnimation, "end") == 0)
    {
        return;
    }

    _animationManager->runAnimationsForSequenceNamed("end");
}

cocos2d::Point Caption::getBackBtnPosition() {
    return _backButton->getParent()->convertToWorldSpace(_backButton->getPosition());
}

cocos2d::Size Caption::getBackBtnSize() {
    return _backButton->getContentSize();
}
