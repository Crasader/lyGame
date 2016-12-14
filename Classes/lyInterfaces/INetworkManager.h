//
//  INetworkManager.h
//
//  ly-Game
//
//  Created by loveyur on 2016/12/14
//  Copyright 2016 loveyur. All rights reserved.
//
//

#ifndef __CoreAppFramework__INetworkManager_h
#define __CoreAppFramework__INetworkManager_h

#include "cocos2d.h"

class INetworkManager
{
public:
    virtual void eventConnectionStart(std::string tag) = 0;
    virtual void eventConnectionEnd(std::string tag, cocos2d::Ref *config) = 0;
    virtual void eventConnectionError(std::string tag, cocos2d::Ref *config) = 0;
    virtual void eventConnectionReview() = 0;
    virtual void eventConnectionUpdateApplication() = 0;
    virtual void eventConnectionUpdateResource() = 0;
    virtual void eventConnectionUpdateMaster(bool refreshUserData) = 0;
    virtual void eventConnectionMaintenance(const cocos2d::ValueMap &data){};
    virtual void eventConnectionRetryNotify(cocos2d::Ref *config, bool retryFlg) = 0;
};

#endif
