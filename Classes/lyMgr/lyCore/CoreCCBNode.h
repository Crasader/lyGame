//
//  CoreCCBNode.h
//
//  ly-Game
//
//  Created by loveyur on 2016/12/14
//  Copyright 2016 loveyur. All rights reserved.
//
//

#ifndef __lyGame__CoreCCBNode__
#define __lyGame__CoreCCBNode__

#include "CCBInterfaceHandler.h"
#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "cocosbuilder/CCBReader.h"
#include "cocosbuilder/CCNodeLoader.h"
#include "cocosbuilder/CCNodeLoaderLibrary.h"

/**
 * cocosbuilderのNodeベースクラス
 */

class CoreCCBNode   :   public cocos2d::Node,
                        public CCBInterfaceHandler
{
public:
    CoreCCBNode();
    virtual ~CoreCCBNode();
    
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

    virtual void onEnter() override;
    virtual void onExit() override;
    
public:
    static CoreCCBNode* create();
    
protected:
    virtual cocos2d::Node* getUIItemByName(const std::string& name, Node* startTarget=nullptr, bool isRecursive=true);
    
    cocosbuilder::CCBAnimationManager* getAnimationManager();
    
private:
    // アニメーションマネージャ
    cocosbuilder::CCBAnimationManager *_animationManager;
};


CREATE_CCB_LOADER_CLASS(CoreCCBNode, CoreCCBNodeLoader);


#endif /* defined(__lyGame__CoreCCBNode__) */
