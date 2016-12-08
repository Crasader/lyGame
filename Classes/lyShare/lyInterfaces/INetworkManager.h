//
//  INetworkManager.h
//  CoreAppFramework
//
//  Created by Mitsuru Yokoyama on 2014/06/10.
//  Copyright 2014 GCREST,Inc. All rights reserved.
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
    virtual void eventConnectionRetryNotify(cocos2d::Ref *config, bool retryFlg) = 0;
};

#endif
