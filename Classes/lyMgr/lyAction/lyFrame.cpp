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
lyFrame* lyFrame::createWithSpritePath(const std::string& filepath)
{
    return (lyFrame*)CCSprite::create(filepath);
}
lyFrame* lyFrame::createWithSpriteName(const std::string& filename)
{
    return (lyFrame*)CCSprite::createWithSpriteFrameName(filename);
}
void lyFrame::update(float delta)
{
    CCSprite::update(delta);
}

void lyFrame::lyVisit()
{
    CCSprite::visit();
}
