//
//  lyActionManager.h
//
//  ly-Game
//
//  Created by loveyur on 2016/12/24
//  Copyright 2016 loveyur. All rights reserved.
//
//

#ifndef __lyGame__lyActionManager__
#define __lyGame__lyActionManager__

#include "lyActionGroup.h"

class lyActionManager
{
public:
    lyActionManager();
    virtual ~lyActionManager();
    
    static lyActionManager* GetInstance();
    void AddGroup( lyActionGroup* pActGroup, unsigned int nGroupId );
    lyActionGroup* GetGroup( unsigned int nGroupId );
    
private:
    static lyActionGroup*		m_szGroupObj[SZ_MAX_ACT_GROUP];
    static lyActionManager*     m_pInstance;
};


#endif /* defined(__lyGame__lyActionManager__) */
