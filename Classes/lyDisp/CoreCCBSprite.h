//
//  CoreCCBSprite.h
//
//  Created by loveyur on 2016/12/11.
//  Copyright 2016 loveyur All rights reserved.
//
//

#ifndef __client_vitamin__CoreCCBSprite__
#define __client_vitamin__CoreCCBSprite__

#include "CCBInterfaceHandler.h"
#include "cocos2d.h"
#include "cocosbuilder/CCBReader.h"
#include "cocosbuilder/CCNodeLoader.h"
#include "cocosbuilder/CCNodeLoaderLibrary.h"

/**
 * cocosbuilderのSpriteベースクラス
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
    virtual cocosbuilder::NodeLoader* getLoader();
    
    // ccbiファイルからのデータ読み込み
    virtual cocos2d::Node* readObject(const char* ccbiName);
    virtual cocos2d::Node* readObject(const char* ccbiName, const char* className);
    virtual cocos2d::Node* readObjectFromFile(const char* ccbiName, cocosbuilder::NodeLoader* loader);
    virtual cocos2d::Node* readObjectFromFile(const char* ccbiName, const char* className, cocosbuilder::NodeLoader* loader);
    
public:
    static CoreCCBSprite* create();
};


CREATE_CCB_LOADER_CLASS(CoreCCBSprite, CoreCCBSpriteLoader);


#endif /* defined(__client_vitamin__CoreCCBSprite__) */
