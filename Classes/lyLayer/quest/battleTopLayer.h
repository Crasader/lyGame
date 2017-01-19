//
//  battleTopLayer.h
//
//  ly-Game
//
//  Created by loveyur on 2016/12/14
//  Copyright 2016 loveyur. All rights reserved.
//
//

#ifndef __lyGame__battleTopLayer__
#define __lyGame__battleTopLayer__

#include "lyBaseLayer.h"
#include "lyInclude.h"
#include "cocos2d.h"

#include "ui/UIWidget.h"
#include "ApplicationManager.h"

#include "lyUIRole.h"
#include "lyUIDrag.h"
#include "lyUIBullet.h"


class battleTopLayerParameter : public SceneParameter
{
public:
    battleTopLayerParameter(){}
};
class battleTopLayer : public lyBaseLayer, public PartsBaseObj
{
public:
    battleTopLayer();
    virtual ~battleTopLayer();
    
    // implement the "static create()" method manually
    CREATE_WITH_FORMAT_FUNC(battleTopLayer);
    
    virtual void completedAnimationSequenceNamed(const char *name);
    
    virtual bool onTouchBegan(cocos2d::Touch* touches, cocos2d::Event* event);
    virtual void onTouchEnded(cocos2d::Touch* touches, cocos2d::Event* event);
    
    virtual bool onAssignCCBMemberVariable(Ref *pTarget, const char *pMemberVariableName, Node *pNode) override;
    virtual cocos2d::extension::Control::Handler onResolveCCBCCControlSelector(cocos2d::Ref* pTarget, const char* pSelectorName) override;
    virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector(cocos2d::Ref * pTarget, const char* pSelectorName) override;
    

    void setSceneParameter(battleTopLayerParameter *param);
    virtual void onEnter();
    virtual void onExit();
    
    void onClickMenuItem01(cocos2d::Ref *sender);
    void onClickDecRole(cocos2d::Ref *sender);
    void onClickAddRole(cocos2d::Ref *sender);
    void onClickAction1(cocos2d::Ref *sender);
    void onClickActionSkill(cocos2d::Ref *sender);
    
   
    void checkTestCollision(float dt);
    void checkBullet(float dt);
private:
    int randPosX();
    int randPosY();
 
    
private:
    bool            _isMoving;
    cocos2d::Node*  _roleArea;
    lyUIRole*       m_pMyRole;
    
    Vector<lyUIDrag*>    m_lyLMTeam1;
    Vector<lyUIDrag*>    m_lyLMTeam2;
    Vector<lyUIBullet*>    m_lyLMBullet;
};


// loader
class battleTopLayerLoader : public cocosbuilder::LayerLoader {
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(battleTopLayerLoader, loader);
    
protected:
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(battleTopLayer);
    
};


#endif /* defined(__lyGame__battleTopLayer__) */
