//
//  CCBInterfaceHandler.h
//
//  Created by loveyur on 2016/12/11.
//  Copyright 2016 loveyur All rights reserved.
//

#ifndef __client_vitamin__CCBInterfaceHandler__
#define __client_vitamin__CCBInterfaceHandler__

#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "cocosbuilder/cocosbuilder.h"


/**
 * NodeLoaderクラスの定義マクロ
 */
#define CREATE_CCB_LOADER_CLASS(__TYPE__, __LOADER_TYPE__) \
class __LOADER_TYPE__ : public cocosbuilder::NodeLoader  \
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
virtual __TYPE__ * createCCNode(cocos2d::Node * pParent, cocosbuilder::CCBReader * pCCBReader) { \
return __TYPE__::create(); \
} \
}; \


/**
 * cocosbuilderのccbファイルのインターフェース定義クラス
 */

class CCBInterfaceHandler   : public cocosbuilder::CCBSelectorResolver,
                            public cocosbuilder::CCBMemberVariableAssigner,
                            public cocosbuilder::CCBAnimationManagerDelegate
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


#endif /* defined(__client_vitamin__CCBInterfaceHandler__) */
