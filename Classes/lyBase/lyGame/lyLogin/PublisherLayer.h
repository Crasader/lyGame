//
//  PublisherLayer.h
//  VitaminProject
//
//  Created by Mitsuru Yokoyama on 2014/06/09.
//  Copyright 2014 GCREST,Inc. All rights reserved.
//

#ifndef __VitaminProject__PublisherLayer__
#define __VitaminProject__PublisherLayer__

#include "VitaminCoreLayer.h"
#include "cocos2d.h"
#include "cocostudio/CCActionManagerEx.h"

class PublisherLayer : public VitaminCoreLayer
{
public:
    // implement the "static create()" method manually
    CREATE_WITH_FORMAT_FUNC(PublisherLayer);
    
    PublisherLayer();
    virtual ~PublisherLayer();
    
private:
    bool _skipSequence;
    cocos2d::Node* _skipButton;
    
    virtual void onEnter() override;
    virtual void onExit() override;
    virtual bool onAssignCCBMemberVariable(cocos2d::Ref* target, const char* memberVariableName, cocos2d::Node* node);
    virtual cocos2d::extension::Control::Handler onResolveCCBCCControlSelector(cocos2d::Ref * pTarget, const char* pSelectorName) override;
    virtual void completedAnimationSequenceNamed(const char *name) override;
    
    void playPublisherCall(float dt);
    
    void onClickedSkip(cocos2d::Ref *pSender, cocos2d::extension::Control::EventType type);
};


// loader
class PublisherLayerLoader : public spritebuilder::LayerLoader {
public:
    SB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(PublisherLayerLoader, loader);
    
protected:
    SB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(PublisherLayer);
    
};


#endif /* defined(__VitaminProject__PublisherLayer__) */
