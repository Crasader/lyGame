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


enum XEventType
{
    XCTRL_TOUCH_DOWN,
    XCTRL_TOUCH_UP,
    XCTRL_TOUCH_CLICK,
    XCTRL_TOUCH_CHG,		//checkboxºÍradiobutton Ñ¡ÖÐ×´Ì¬¸üÐÂ
    XCTRL_PROBAR_CHG_END,
    XCTRL_PROBAR_CHG_TEST,
    
    
    XCTRL_EVT_CNT
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
