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
{
}

lyFrame::~lyFrame()
{
}
/*
lyFrame* lyFrame::Create()
{
    return new lyFrame();
}
 */
lyFrame* lyFrame::create(const std::string& filename)
{
    lyFrame *sprite = new (std::nothrow) lyFrame();
    if (sprite && sprite->initWithFile(filename))
    {
        sprite->autorelease();
        return sprite;
    }
    CC_SAFE_DELETE(sprite);
    return nullptr;
}
void lyFrame::OnDraw( float fx,float fy,float fScale,unsigned char alpha )
{
    setPosition(ccp(fx,fy));
    setScaleX( fScale );
    setScaleY( fScale );
    setOpacity( alpha );
    visit();
}

