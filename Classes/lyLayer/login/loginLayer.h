//
//  loginLayer.h
//  VitaminProject
//
//  Created by Shinji Hiramatsu on 2014/05/24.
//  Copyright 2014 GCREST,Inc. All rights reserved.
//

#ifndef __VitaminProject__loginLayer__
#define __VitaminProject__loginLayer__

#include "VitaminCoreLayer.h"
#include "cocos2d.h"
#include "cocostudio/CCActionManagerEx.h"
#include "ui/UIWidget.h"
#include "ApplicationManager.h"

class loginLayerParameter : public SceneParameter
{
public:
    loginLayerParameter(){}
};
class loginLayer : public VitaminCoreLayer, public PartsBaseObj
{
public:
    loginLayer();
    virtual ~loginLayer();
    
    // implement the "static create()" method manually
    CREATE_WITH_FORMAT_FUNC(loginLayer);
    
    virtual void completedAnimationSequenceNamed(const char *name);
    
    virtual bool onTouchBegan(cocos2d::Touch* touches, cocos2d::Event* event);
    virtual void onTouchEnded(cocos2d::Touch* touches, cocos2d::Event* event);
    
    virtual bool onAssignCCBMemberVariable(Ref *pTarget, const char *pMemberVariableName, Node *pNode) override;
    virtual cocos2d::extension::Control::Handler onResolveCCBCCControlSelector(cocos2d::Ref* pTarget, const char* pSelectorName) override;
    
    void setSceneParameter(loginLayerParameter *param);
    virtual void onEnter();
    
    
    void onPressButtonWeixin(cocos2d::Ref *sender, cocos2d::extension::Control::EventType pControlEvent);
    void onPressButtonQQ(cocos2d::Ref *sender, cocos2d::extension::Control::EventType pControlEvent);
    void onPressButtonTest(cocos2d::Ref *sender, cocos2d::extension::Control::EventType pControlEvent);
   
    
private:
    void doFinishScene();
    
    bool _isMoving;

    cocos2d::extension::ControlButton* _buttonTest;
};


// loader
class loginLayerLoader : public cocosbuilder::LayerLoader {
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(loginLayerLoader, loader);
    
protected:
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(loginLayer);
    
};


#endif /* defined(__VitaminProject__loginLayer__) */
