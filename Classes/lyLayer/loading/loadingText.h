//
//  loadingText.h
//  VitaminProject
//
//  Created by Shinji Hiramatsu on 2014/05/24.
//  Copyright 2014 GCREST,Inc. All rights reserved.
//

#ifndef __VitaminProject__loadingText__
#define __VitaminProject__loadingText__

#include "VitaminCoreLayer.h"
#include "cocos2d.h"
#include "cocostudio/CCActionManagerEx.h"
#include "ui/UIWidget.h"
#include "ApplicationManager.h"
struct loadingTextParameter : public SceneParameter
{
public:
    loadingTextParameter(){};
};

class loadingText : public VitaminCoreLayer, public PartsBaseObj
{
public:
    loadingText();
    virtual ~loadingText();
    
    // implement the "static create()" method manually
    CREATE_WITH_FORMAT_FUNC(loadingText);
    
    virtual void completedAnimationSequenceNamed(const char *name);
    
    virtual bool onTouchBegan(cocos2d::Touch* touches, cocos2d::Event* event);
    virtual void onTouchEnded(cocos2d::Touch* touches, cocos2d::Event* event);
    
    virtual bool onAssignCCBMemberVariable(Ref *pTarget, const char *pMemberVariableName, Node *pNode) override;
    virtual cocos2d::extension::Control::Handler onResolveCCBCCControlSelector(cocos2d::Ref* pTarget, const char* pSelectorName) override;
    virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector(cocos2d::Ref * pTarget, const char* pSelectorName) override;
    

    void setSceneParameter(loadingTextParameter *param);
    
    virtual void onEnter();
    
    
    void onClickedButton1(cocos2d::Ref *sender, cocos2d::extension::Control::EventType pControlEvent);
   
    
private:
    void doFinishScene();
    
    bool _isMoving;
};


// loader
class loadingTextLoader : public cocosbuilder::LayerLoader {
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(loadingTextLoader, loader);
    
protected:
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(loadingText);
    
};


#endif /* defined(__VitaminProject__loadingText__) */
