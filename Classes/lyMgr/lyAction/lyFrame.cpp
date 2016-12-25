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
lyFrame* lyFrame::Create()
{
    return new lyFrame();
}

void lyFrame::OnDraw( float fx,float fy,float fScale,unsigned char alpha )
{
    setPosition(ccp(fx,fy));
    setScaleX( fScale );
    setScaleY( fScale );
    setOpacity( alpha );
    visit();
}

