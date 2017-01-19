//
//  lyEvent.h
//
//  ly-Game
//
//  Created by loveyur on 2016/12/24
//  Copyright 2016 loveyur. All rights reserved.
//
//

#ifndef __lyGame__lyEvent__
#define __lyGame__lyEvent__

#include "lyLink.h"


enum UIEventType
{
    UI_TOUCH_DOWN,
    UI_TOUCH_UP,
    UI_TOUCH_CLICK,

    UI_EVENT_CNT
};

typedef void (*XEventCallBack)( long dwObjID );

class lyEvent:public lyLinkItem<lyEvent>
{
public:
    lyEvent();
    virtual ~lyEvent();
    
    
    static lyEvent* Create()
    {
        return new lyEvent();
    };
    
    unsigned char m_byType;
    XEventCallBack m_CallBackFunc;
    long	m_dwObjID;

private:
};


#endif /* defined(__lyGame__lyEvent__) */
