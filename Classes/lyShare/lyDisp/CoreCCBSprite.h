//
//  CoreCCBSprite.h
//  client-vitamin
//
//  Created by Shinji Hiramatsu on 2014/06/24.
//  Copyright 2014 GCREST,Inc. All rights reserved.
//
//

#ifndef __client_vitamin__CoreCCBSprite__
#define __client_vitamin__CoreCCBSprite__

#include "CCBInterfaceHandler.h"
#include "cocos2d.h"
#include "spritebuilder/CCBReader.h"
#include "spritebuilder/CCNodeLoader.h"
#include "spritebuilder/CCNodeLoaderLibrary.h"

/**
 * SpriteBuilderのSpriteベースクラス
 */
class CoreCCBSprite   :   public cocos2d::Sprite,
                          public CCBInterfaceHandler
{
public:
    CoreCCBSprite();
    virtual ~CoreCCBSprite();
    
    virtual bool init();

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
    static CoreCCBSprite* create();
};


CREATE_CCB_LOADER_CLASS(CoreCCBSprite, CoreCCBSpriteLoader);


#endif /* defined(__client_vitamin__CoreCCBSprite__) */
