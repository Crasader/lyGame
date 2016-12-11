//
//  IWaitManager.h
//  client-vitamin
//
//  Created by 横山 充 on 2015/03/20.
//
//

#ifndef client_vitamin_IWaitManager_h
#define client_vitamin_IWaitManager_h

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
