//
//  lyBaseLayerModule.hpp
//
//  ly-Game
//
//  Created by loveyur on 2016/12/14
//  Copyright 2016 loveyur. All rights reserved.
//
//

#ifndef lyBaseLayerModule_h
#define lyBaseLayerModule_h

#include "cocos2d.h"

class lyBaseLayer;

class lyBaseLayerModule
{
public:
    lyBaseLayerModule();
    virtual ~lyBaseLayerModule();
    virtual void init(lyBaseLayer *layer);

protected:
    lyBaseLayer *_parent;
};

#endif /* lyBaseLayerModule_h */
