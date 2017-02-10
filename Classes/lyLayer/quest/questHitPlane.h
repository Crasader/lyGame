//
//  questHitPlane.h
//
//  ly-Game
//
//  Created by loveyur on 2016/12/14
//  Copyright 2016 loveyur. All rights reserved.
//
//

#ifndef __lyGame__questHitPlane__
#define __lyGame__questHitPlane__

#include "lyBaseLayer.h"
#include "lyInclude.h"
#include "cocos2d.h"

#include "ui/UIWidget.h"
#include "ApplicationManager.h"

#include "lyUIRole.h"
#include "lyUIBullet.h"


class questHitPlaneParameter : public SceneParameter
{
public:
    questHitPlaneParameter(){}
};
class questHitPlane : public lyBaseLayer, public PartsBaseObj
{
public:
    questHitPlane();
    virtual ~questHitPlane();
    
    // implement the "static create()" method manually
    CREATE_WITH_FORMAT_FUNC(questHitPlane);
    
    virtual void completedAnimationSequenceNamed(const char *name);
    
    virtual bool onTouchBegan(cocos2d::Touch* touches, cocos2d::Event* event);
    virtual void onTouchEnded(cocos2d::Touch* touches, cocos2d::Event* event);
    
    virtual bool onAssignCCBMemberVariable(Ref *pTarget, const char *pMemberVariableName, Node *pNode) override;
    virtual cocos2d::extension::Control::Handler onResolveCCBCCControlSelector(cocos2d::Ref* pTarget, const char* pSelectorName) override;
    virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector(cocos2d::Ref * pTarget, const char* pSelectorName) override;
    

    void setSceneParameter(questHitPlaneParameter *param);
    virtual void onEnter();
    virtual void onExit();
    
    void onClickMenuItem01(cocos2d::Ref *sender);
    //暂停游戏
    void onClickPause(cocos2d::Ref *sender);
    
    void BornOnePlane();
    void BornOneEnemy(float dt);
    
    void EnemyStartMove(float dt);
    void checkCollision(float dt);
    void pauseGame();
    void resumeGame();
    
    
    void Test();
private:
    int randPosX();
    int randPosY();
 
    
private:
    static bool     _canBorn;
    bool            _isMoving;
    cocos2d::Node*  _roleArea;
 
 
    Vector<lyUIBullet*>     m_verEnemy;
    lyUIRole*               m_pPlane;
    
    bool                    m_bPause;
    bool                    m_bGameEnd;
    
};


// loader
class questHitPlaneLoader : public cocosbuilder::LayerLoader {
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(questHitPlaneLoader, loader);
    
protected:
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(questHitPlane);
    
};


#endif /* defined(__lyGame__questHitPlane__) */