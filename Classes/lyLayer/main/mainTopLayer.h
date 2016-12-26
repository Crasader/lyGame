//
//  mainTopLayer.h
//
//  ly-Game
//
//  Created by loveyur on 2016/12/14
//  Copyright 2016 loveyur. All rights reserved.
//
//

#ifndef __lyGame__mainTopLayer__
#define __lyGame__mainTopLayer__

#include "lyBaseLayer.h"
#include "lyInclude.h"
#include "cocos2d.h"

#include "ui/UIWidget.h"
#include "ApplicationManager.h"

class mainTopLayerParameter : public SceneParameter
{
public:
    mainTopLayerParameter(){}
};
class mainTopLayer : public lyBaseLayer, public PartsBaseObj
{
public:
    mainTopLayer();
    virtual ~mainTopLayer();
    
    // implement the "static create()" method manually
    CREATE_WITH_FORMAT_FUNC(mainTopLayer);
    
    virtual void completedAnimationSequenceNamed(const char *name);
    
    virtual bool onTouchBegan(cocos2d::Touch* touches, cocos2d::Event* event);
    virtual void onTouchEnded(cocos2d::Touch* touches, cocos2d::Event* event);
    
    virtual bool onAssignCCBMemberVariable(Ref *pTarget, const char *pMemberVariableName, Node *pNode) override;
    virtual cocos2d::extension::Control::Handler onResolveCCBCCControlSelector(cocos2d::Ref* pTarget, const char* pSelectorName) override;
    virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector(cocos2d::Ref * pTarget, const char* pSelectorName) override;
    

    void setSceneParameter(mainTopLayerParameter *param);
    virtual void onEnter();
    
    
    void onPressButtonWeixin(cocos2d::Ref *sender);
    void onPressButtonQQ(cocos2d::Ref *sender);
   
    
private:
    
    bool _isMoving;

    cocos2d::extension::ControlButton* _buttonTest;
};


// loader
class mainTopLayerLoader : public cocosbuilder::LayerLoader {
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(mainTopLayerLoader, loader);
    
protected:
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(mainTopLayer);
    
};


#endif /* defined(__lyGame__mainTopLayer__) */
