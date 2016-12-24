//
//  IWaitManager.h
//
//  ly-Game
//
//  Created by loveyur on 2016/12/14
//  Copyright 2016 loveyur. All rights reserved.
//
//

#ifndef __lyGame__IWaitManager__
#define __lyGame__IWaitManager__

#include "cocos2d.h"
#include "ApplicationManager.h"

class IWaitManager
{
public:
    virtual void waitrunWithScene(const SceneBuildInfo &sceneInfo) = 0;
    virtual void waitchangeScene(const SceneBuildInfo &sceneInfo) = 0;
    virtual void waitPushScene(const SceneBuildInfo &sceneInfo) = 0;
    virtual void waitPopScene() = 0;
    virtual void waitChangePreviousScene() = 0;
};

#endif
