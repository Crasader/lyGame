//
//  ICommandManager.h
//  CoreAppFramework
//
//  Created by Shinji Hiramatsu on 2014/05/24.
//  Copyright 2014 GCREST,Inc. All rights reserved.
//

#ifndef __CoreAppFramework__ICommandManager_h
#define __CoreAppFramework__ICommandManager_h

typedef int CommandError;

class ICommand;

class ICommandManager
{
public:
    virtual CommandError executeCommand(int cmdID, void* param) = 0;
};



#endif
