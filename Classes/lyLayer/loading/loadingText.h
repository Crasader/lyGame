//
//  loadingText.h
//
//  ly-Game
//
//  Created by loveyur on 2016/12/14
//  Copyright 2016 loveyur. All rights reserved.
//
//

#ifndef __lyGame__loadingText__
#define __lyGame__loadingText__

#include "lyBaseLayer.h"
#include "cocos2d.h"
#include "cocostudio/CCActionManagerEx.h"
#include "ui/UIWidget.h"
#include "ApplicationManager.h"
struct loadingTextParameter : public SceneParameter
{
public:
    loadingTextParameter(){};
};

class loadingText : public PartsBase
{
public:
    static loadingText* createFromFile();
    
    loadingText();
    virtual ~loadingText();
    
    CREATE_FUNC(loadingText);
    
    
    virtual bool onAssignCCBMemberVariable(Ref *pTarget, const char *pMemberVariableName, Node *pNode) override;
    virtual cocos2d::extension::Control::Handler onResolveCCBCCControlSelector(cocos2d::Ref* pTarget, const char* pSelectorName) override;
    virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector(cocos2d::Ref * pTarget, const char* pSelectorName) override;
    
    virtual void onEnter() override;
    
};


#endif /* defined(__lyGame__loadingText__) */
