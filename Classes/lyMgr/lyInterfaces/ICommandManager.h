//
//  ICommandManager.h
//
//  ly-Game
//
//  Created by loveyur on 2016/12/14
//  Copyright 2016 loveyur. All rights reserved.
//
//

#ifndef __lyGame__ICommandManager_h
#define __lyGame__ICommandManager_h

typedef int CommandError;

class ICommand;

class ICommandManager
{
public:
    virtual CommandError executeCommand(int cmdID, void* param) = 0;
};



#endif
