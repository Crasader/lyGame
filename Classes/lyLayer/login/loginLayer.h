//
//  loginLayer.h
//
//  ly-Game
//
//  Created by loveyur on 2016/12/14
//  Copyright 2016 loveyur. All rights reserved.
//
//

#ifndef __lyGame__loginLayer__
#define __lyGame__loginLayer__

#include "lyBaseLayer.h"
#include "cocos2d.h"
#include "cocostudio/CCActionManagerEx.h"
#include "ui/UIWidget.h"
#include "ApplicationManager.h"

class loginLayerParameter : public SceneParameter
{
public:
    loginLayerParameter(){}
};
class loginLayer : public lyBaseLayer, public PartsBaseObj
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
    virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector(cocos2d::Ref * pTarget, const char* pSelectorName) override;
    

    void setSceneParameter(loginLayerParameter *param);
    virtual void onEnter();
    
    
    void onPressButtonWeixin(cocos2d::Ref *sender);
    void onPressButtonQQ(cocos2d::Ref *sender);
   
    
private:
    
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


#endif /* defined(__lyGame__loginLayer__) */
