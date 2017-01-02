//
//  lyFrame.cpp
//  ly-Game
//
//  Created by loveyur on 2016/12/34
//  Copyright 2016 loveyur. All rights reserved.
//
//

#include "lyFrame.h"
#include "cocos2d.h"

USING_NS_CC;


lyFrame::lyFrame()
:CCSprite()
{
}

lyFrame::~lyFrame()
{
}
lyFrame* lyFrame::create(const std::string& filename)
{
    return (lyFrame*)CCSprite::create(filename);
}
void lyFrame::update(float delta)
{
    CCSprite::update(delta);
}

void lyFrame::lyVisit()
{
    CCSprite::visit();
}
