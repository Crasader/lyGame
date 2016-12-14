//
//  lyBaseLayerModule.cpp
//
//  ly-Game
//
//  Created by loveyur on 2016/12/14
//  Copyright 2016 loveyur. All rights reserved.
//
//

#include "lyBaseLayerModule.h"

lyBaseLayerModule::lyBaseLayerModule()
: _parent(nullptr)
{
}

lyBaseLayerModule::~lyBaseLayerModule()
{
}

void lyBaseLayerModule::init(lyBaseLayer *parent)
{
    _parent = parent;
}
