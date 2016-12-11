//
//  testScene.h
//  VitaminProject
//
//  Created by Shinji Hiramatsu on 2014/05/24.
//  Copyright 2014 GCREST,Inc. All rights reserved.
//

#ifndef __VitaminProject__testScene__
#define __VitaminProject__testScene__

#include "VitaminCoreLayer.h"
#include "cocos2d.h"
#include "cocostudio/CCActionManagerEx.h"
#include "ui/UIWidget.h"
#include "ApplicationManager.h"


class testScene : public VitaminCoreLayer
{
public:
    testScene();
    virtual ~testScene();
    
    // implement the "static create()" method manually
    CREATE_WITH_FORMAT_FUNC(testScene);
    
    virtual void completedAnimationSequenceNamed(const char *name);
    
    virtual bool onTouchBegan(cocos2d::Touch* touches, cocos2d::Event* event);
    virtual void onTouchEnded(cocos2d::Touch* touches, cocos2d::Event* event);
    
    virtual bool onAssignCCBMemberVariable(Ref *pTarget, const char *pMemberVariableName, Node *pNode) override;
    virtual cocos2d::extension::Control::Handler onResolveCCBCCControlSelector(cocos2d::Ref* pTarget, const char* pSelectorName) override;
    
    virtual void onEnter();
    
    
    void onClickedButton1(cocos2d::Ref *sender, cocos2d::extension::Control::EventType pControlEvent);
    void onClickedButton2(cocos2d::Ref *sender, cocos2d::extension::Control::EventType pControlEvent);
    void btnNextLayer(cocos2d::Ref *sender, cocos2d::extension::Control::EventType pControlEvent);
    
    
private:
    void doFinishScene();
    
    bool _isMoving;
    cocos2d::Label *_nameLabel;
    cocos2d::Sprite * _sprtest;
    
};


// loader
class testSceneLoader : public cocosbuilder::LayerLoader {
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(testSceneLoader, loader);
    
protected:
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(testScene);
    
};


#endif /* defined(__VitaminProject__testScene__) */
