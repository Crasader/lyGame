//
//  lyFrame.h
//
//  ly-Game
//
//  Created by loveyur on 2016/12/24
//  Copyright 2016 loveyur. All rights reserved.
//
//

#ifndef __lyGame__lyFrame__
#define __lyGame__lyFrame__

#include "lyLink.h"
#include "cocos2d.h"
using namespace cocos2d;

#define SZ_ACT_MAX 50

class lyFrame:
public CCSprite,
public lyLinkItem<lyFrame>
{
public:
    lyFrame();
    ~lyFrame();
    
    static lyFrame* Create();
    
    void OnDraw(float fx,float fy,float fScale,unsigned char alpha);
    
private:
};


#endif /* defined(__lyGame__lyFrame__) */
