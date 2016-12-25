//
//  lyAction.h
//
//  ly-Game
//
//  Created by loveyur on 2016/12/24
//  Copyright 2016 loveyur. All rights reserved.
//
//

#ifndef __lyGame__lyAction__
#define __lyGame__lyAction__

#include "lyFrame.h"

class lyAction
{
public:
    lyAction();
    virtual ~lyAction();
    
    static lyAction* Create();

    void OnFrame(float fDeltaTime);
    //void OnDraw(float fx,float fy,float fScale,unsigned char alpha);

    void AddFrame(const char* pszImg);
    
    lyFrame* GetNextFrame(lyFrame* pSpr);
    
private:
    //XSprite* m_pCurrFrame;
    lyLinkMgr<lyFrame> m_ObjFrames;
};


#endif /* defined(__lyGame__lyAction__) */
