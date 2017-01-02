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
    void LoadActionGroupLibrary();
    
    //先构造动作组，再添加到管理类中
    void AddGroup( lyActionGroup* pActGroup, unsigned int nGroupId );
    //添加动作组id为x的动作组到管理类
    void AddGroup(int nGroupId);
    void LoadOneAction(std::map<std::string,int> map, int nId);
    
    lyActionGroup* GetGroup( unsigned int nGroupId );
    
private:
    static lyActionGroup*		m_szGroupObj[SZ_MAX_ACT_GROUP];
    static lyActionManager*     m_pInstance;
};


#endif /* defined(__lyGame__lyActionManager__) */
