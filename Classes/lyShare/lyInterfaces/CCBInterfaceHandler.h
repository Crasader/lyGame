//
//
//  lyISoundInterfaces.h
//  ly-client
//	声音管理类基类接口
//  Created by loveyur on 2016/11/11
//  Copyright 2016 loveyur All rights reserved.
//

#ifndef ly_CCBInterfaceHandler__
#define ly_CCBInterfaceHandler__

#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "spritebuilder/SpriteBuilder.h"


/**
 * NodeLoaderクラスの定義マクロ
 */
#define CREATE_CCB_LOADER_CLASS(__TYPE__, __LOADER_TYPE__) \
class __LOADER_TYPE__ : public spritebuilder::NodeLoader  \
{ \
public: \
static __LOADER_TYPE__ * loader() { \
__LOADER_TYPE__ * ptr = new __LOADER_TYPE__(); \
if(ptr != NULL) { \
ptr->autorelease(); \
return ptr; \
} \
CC_SAFE_DELETE(ptr); \
return NULL; \
} \
protected: \
virtual __TYPE__ * createCCNode(cocos2d::Node * pParent, spritebuilder::CCBReader * pCCBReader) { \
return __TYPE__::create(); \
} \
}; \

class CCBInterfaceHandler   : public spritebuilder::CCBSelectorResolver,
                            public spritebuilder::CCBMemberVariableAssigner,
                            public spritebuilder::CCBAnimationManagerDelegate
{
public:
    
    // CCBSelectorResolver
    virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector(cocos2d::Ref * pTarget, const char* pSelectorName);
    virtual cocos2d::SEL_CallFuncN onResolveCCBCCCallFuncSelector(cocos2d::Ref * pTarget, const char* pSelectorName);
    virtual cocos2d::extension::Control::Handler onResolveCCBCCControlSelector(cocos2d::Ref * pTarget, const char* pSelectorName);
    
    // CCBMemberVariableAssigner
    virtual bool onAssignCCBMemberVariable(cocos2d::Ref* target, const char* memberVariableName, cocos2d::Node* node);
    virtual bool onAssignCCBCustomProperty(cocos2d::Ref* target, const char* memberVariableName, const cocos2d::Value& value);
    
    // CCBAnimationManagerDelegate
    virtual void completedAnimationSequenceNamed(const char *name);
    
};


#endif /* defined(ly_CCBInterfaceHandler__) */
