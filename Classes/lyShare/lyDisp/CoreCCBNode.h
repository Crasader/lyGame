//
//  CoreCCBNode.h
//  client-vitamin
//
//  Created by Shinji Hiramatsu on 2014/06/24.
//  Copyright 2014 GCREST,Inc. All rights reserved.
//
//

#ifndef __client_vitamin__CoreCCBNode__
#define __client_vitamin__CoreCCBNode__

#include "CCBInterfaceHandler.h"
#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "spritebuilder/CCBReader.h"
#include "spritebuilder/CCNodeLoader.h"
#include "spritebuilder/CCNodeLoaderLibrary.h"

/**
 * SpriteBuilderのNodeベースクラス
 */

class CoreCCBNode   :   public cocos2d::Node,
                        public CCBInterfaceHandler
{
public:
    CoreCCBNode();
    virtual ~CoreCCBNode();
    
    virtual bool init();

    virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector(cocos2d::Ref * pTarget, const char* pSelectorName);
    virtual cocos2d::SEL_CallFuncN onResolveCCBCCCallFuncSelector(cocos2d::Ref * pTarget, const char* pSelectorName);

    virtual cocos2d::extension::Control::Handler onResolveCCBCCControlSelector(cocos2d::Ref * pTarget, const char* pSelectorName);
    
    virtual bool onAssignCCBMemberVariable(cocos2d::Ref* target, const char* memberVariableName, cocos2d::Node* node);

    virtual bool onAssignCCBCustomProperty(cocos2d::Ref* target, const char* memberVariableName, const cocos2d::Value& value);
    
    virtual void completedAnimationSequenceNamed(const char *name);
    
    virtual spritebuilder::NodeLoader* getLoader();
    
    virtual cocos2d::Node* readObject(const char* ccbiName);
    virtual cocos2d::Node* readObject(const char* ccbiName, const char* className);
    virtual cocos2d::Node* readObjectFromFile(const char* ccbiName, spritebuilder::NodeLoader* loader);
    virtual cocos2d::Node* readObjectFromFile(const char* ccbiName, const char* className, spritebuilder::NodeLoader* loader);

    virtual void onEnter() override;
    virtual void onExit() override;
    
public:
    static CoreCCBNode* create();
    
protected:
    virtual cocos2d::Node* getUIItemByName(const std::string& name, Node* startTarget=nullptr, bool isRecursive=true);
    
    spritebuilder::CCBAnimationManager* getAnimationManager();
    
private:
    // アニメーションマネージャ
    spritebuilder::CCBAnimationManager *_animationManager;
};


CREATE_CCB_LOADER_CLASS(CoreCCBNode, CoreCCBNodeLoader);


#endif /* defined(__client_vitamin__CoreCCBNode__) */
