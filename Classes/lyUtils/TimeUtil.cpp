//
//  TimeUtil.cpp
//
//  ly-Game
//
//  Created by loveyur on 2016/12/14
//  Copyright 2016 loveyur. All rights reserved.
//
//

#include "TimeUtil.h"
#include "cocos2d.h"


double TimeUtil::getMSecTime()
{
    struct timeval tv;
    gettimeofday(&tv, nullptr);
    return tv.tv_sec*1000.0+tv.tv_usec/1000.0;
}

double TimeUtil::getTime()
{
    struct timeval tv;
    gettimeofday(&tv, nullptr);
    return (double)(tv.tv_sec) + (double)((tv.tv_usec)* 0.001 * 0.001);
}

