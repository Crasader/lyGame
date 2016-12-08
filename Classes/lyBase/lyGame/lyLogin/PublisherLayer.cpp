//
//  PublisherLayer.cpp
//  VitaminProject
//
//  Created by Mitsuru Yokoyama on 2014/06/09.
//  Copyright 2014 GCREST,Inc. All rights reserved.
//

#include "PublisherLayer.h"
#include "ApplicationManager.h"
#include "VitaminSceneID.h"
#include "cocos2d.h"
#include <random>
USING_NS_CC;


PublisherLayer::PublisherLayer()
: _skipSequence(false)
, _skipButton(nullptr)
{
}

PublisherLayer::~PublisherLayer()
{
    
}

void PublisherLayer::onEnter()
{
    VitaminCoreLayer::onEnter();
    
   }

void PublisherLayer::onExit()
{
    VitaminCoreLayer::onExit();
    
    CC_SAFE_RELEASE(_skipButton);
}

bool PublisherLayer::onAssignCCBMemberVariable(cocos2d::Ref* pTarget, const char* pMemberVariableName, cocos2d::Node* pNode)
{
    SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_skipButton", cocos2d::Node *, _skipButton);
    
    return false;
}

cocos2d::extension::Control::Handler PublisherLayer::onResolveCCBCCControlSelector(cocos2d::Ref * pTarget, const char* pSelectorName)
{
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onClickedSkip", PublisherLayer::onClickedSkip);
    return NULL;
}

void PublisherLayer::completedAnimationSequenceNamed(const char *name)
{
    if (_skipSequence)
    {
        return;
    }
}

void PublisherLayer::playPublisherCall(float dt)
{
    auto existSound = std::vector<std::string>();
    
 }

void PublisherLayer::onClickedSkip(cocos2d::Ref *pSender, cocos2d::extension::Control::EventType type)
{
    if (_skipSequence) return;
    _skipSequence = true;
    
   
}
