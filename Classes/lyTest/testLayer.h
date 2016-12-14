//
//  testLayer.h
//
//  ly-Game
//
//  Created by loveyur on 2016/12/14
//  Copyright 2016 loveyur. All rights reserved.
//
//

#ifndef __VitaminProject__testLayer__
#define __VitaminProject__testLayer__

#include "lyBaseLayer.h"
#include "cocos2d.h"
#include "cocostudio/CCActionManagerEx.h"
#include "ui/UIWidget.h"
#include "ApplicationManager.h"


struct testLayerParameter : public SceneParameter
{
public:
    testLayerParameter(){};
};


class testLayer : public lyBaseLayer, public PartsBaseObj
{
public:
    testLayer();
    virtual ~testLayer();
    
    // implement the "static create()" method manually
    CREATE_WITH_FORMAT_FUNC(testLayer);
    
    virtual void completedAnimationSequenceNamed(const char *name);
    
    virtual bool onTouchBegan(cocos2d::Touch* touches, cocos2d::Event* event);
    virtual void onTouchEnded(cocos2d::Touch* touches, cocos2d::Event* event);
    
    virtual bool onAssignCCBMemberVariable(Ref *pTarget, const char *pMemberVariableName, Node *pNode) override;
    virtual cocos2d::extension::Control::Handler onResolveCCBCCControlSelector(cocos2d::Ref* pTarget, const char* pSelectorName) override;
    virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector(cocos2d::Ref * pTarget, const char* pSelectorName) override;
    
    void setSceneParameter(testLayerParameter *param);
    
    virtual void onEnter();
    virtual void onExit();
    
    
    void onClickedMenuButton(cocos2d::Ref *sender);
    void onPressCtrlButton(cocos2d::Ref *sender, cocos2d::extension::Control::EventType pControlEvent);
    
private:
    void doFinishScene();
    
    bool _isMoving;
    cocos2d::Label *_nameLabel;
    cocos2d::Sprite * _sprtest;
    
};


// loader
class testLayerLoader : public cocosbuilder::LayerLoader {
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(testLayerLoader, loader);
    
protected:
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(testLayer);
    
};


#endif /* defined(__VitaminProject__testLayer__) */
