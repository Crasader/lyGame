//
//  CoreCCBLayer.h
//  client-vitamin
//
//  Created by Shinji Hiramatsu on 2014/05/24.
//  Copyright 2014 GCREST,Inc. All rights reserved.
//
//

#ifndef __client_vitamin__CoreCCBLayer__
#define __client_vitamin__CoreCCBLayer__

#include "CoreLayer.h"
#include "CCBInterfaceHandler.h"
#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "spritebuilder/CCBReader.h"
#include "spritebuilder/CCNodeLoader.h"
#include "spritebuilder/CCNodeLoaderLibrary.h"

/**
 * SpriteBuilderのLayerベースクラス
 */

class CoreCCBLayer    : public CoreLayer,
                        public CCBInterfaceHandler
{
public:
    CoreCCBLayer();
    virtual ~CoreCCBLayer();
    
    virtual bool init();
    
    virtual void onExit();
    
    // CCBSelectorResolverクラスのインターフェース
    virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector(cocos2d::Ref * pTarget, const char* pSelectorName);
    virtual cocos2d::SEL_CallFuncN onResolveCCBCCCallFuncSelector(cocos2d::Ref * pTarget, const char* pSelectorName);

    virtual cocos2d::extension::Control::Handler onResolveCCBCCControlSelector(cocos2d::Ref * pTarget, const char* pSelectorName);
    
    // CCBMemberVariableAssignerクラスのインターフェース
    virtual bool onAssignCCBMemberVariable(cocos2d::Ref* target, const char* memberVariableName, cocos2d::Node* node);

    virtual bool onAssignCCBCustomProperty(cocos2d::Ref* target, const char* memberVariableName, const cocos2d::Value& value);
    
    // CCBAnimationManagerDelegateクラスのインターフェース
    virtual void completedAnimationSequenceNamed(const char *name);
    
    
    // Loaderの取得
    virtual spritebuilder::NodeLoader* getLoader();
    
    // ccbiファイルからのデータ読み込み
    virtual cocos2d::Node* readObject(const char* ccbiName);
    virtual cocos2d::Node* readObject(const char* ccbiName, const char* className);
    virtual cocos2d::Node* readObjectFromFile(const char* ccbiName, spritebuilder::NodeLoader* loader);
    virtual cocos2d::Node* readObjectFromFile(const char* ccbiName, const char* className, spritebuilder::NodeLoader* loader);
    
public:
    static CoreCCBLayer* create();
    
protected:
    virtual cocos2d::Node* getUIItemByName(const std::string& name, Node* startTarget=nullptr, bool isRecursive=true);

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    virtual void keyBackClicked(cocos2d::Event* event) {};
#endif

public:
    
    void setAnimationManager();
    
    // getAnimationManager
    spritebuilder::CCBAnimationManager* getAnimationManager();
    
private:
    // startAnimation
    void startAnimation(cocos2d::Node *pTarget);
    
private:
    // アニメーションマネージャ
    spritebuilder::CCBAnimationManager *_animationManager;
};


CREATE_CCB_LOADER_CLASS(CoreCCBLayer, CoreCCBLayerLoader);


#endif /* defined(__client_vitamin__CoreSpriteBuilderLayer__) */
