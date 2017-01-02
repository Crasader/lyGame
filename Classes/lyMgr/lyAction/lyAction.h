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
#include "lylink.h"

class lyAction
{
public:
    lyAction();
    virtual ~lyAction();
    virtual bool init();
    static lyAction* Create();

 
    void AddFrame(const char* pszImg);
 
    lyFrame* GetNextFrame(lyFrame* pSpr);
    lyFrame* GetHeaderFrame();
    lyFrame* GetTailFrame();
    
    lyLinkMgr<lyFrame> getFrames()
    {
        return m_ObjFrames;
    };
    
    //
    void setDelay(bool is)
    {
        m_bDelay = is;
    };
    bool isDelay()
    {
        return m_bDelay;
    };
private:
    lyLinkMgr<lyFrame>  m_ObjFrames;
    bool                m_bDelay;   //true 播放完当前动作才能播放下一个动作，false，立即切换动作
};


#endif /* defined(__lyGame__lyAction__) */
