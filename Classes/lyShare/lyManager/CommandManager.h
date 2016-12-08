//
//  CommandManager.h
//  CoreAppFramework
//
//  Created by Shinji Hiramatsu on 2014/05/24.
//  Copyright 2014 GCREST,Inc. All rights reserved.
//

#ifndef __CoreAppFramework__CommandManager__
#define __CoreAppFramework__CommandManager__

#include "ICommandManager.h"

class CommandManager    : public ICommandManager
{
public:
    CommandManager();
    virtual ~CommandManager();
    
    virtual bool init();
    
    virtual CommandError executeCommand(int cmdID, void* param);
    
public:
    static CommandManager * getInstance();
    
};

#endif /* defined(__CoreAppFramework__CommandManager__) */
