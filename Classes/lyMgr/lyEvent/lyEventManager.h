//
//  lyEventManager.h
//
//  ly-Game
//
//  Created by loveyur on 2016/12/24
//  Copyright 2016 loveyur. All rights reserved.
//
//

#ifndef __lyGame__lyEventManager__
#define __lyGame__lyEventManager__

#include "lyEvent.h"

class lyEventManager
{
public:
    lyEventManager();
    ~lyEventManager();

    static lyEventManager* getInstance();
    
    static void RegEventCPP(UIEventType byType,XEventCallBack pCallBackFunc, long dwObjID );
    static void ExecuteEventCPP(UIEventType byType, long dwObjID ,long dwParam = 0 );
    
    static void ClearEvents(int eventID, long objGuid);
    
private:
    static lyEventManager* m_EventInstance;
    
    static lyLinkMgr<lyEvent> m_objEventMgr;
};


#endif /* defined(__lyGame__lyEventManager__) */
