//
//  VitaminCommandManager.h
//  VitaminProject
//
//  Created by Shinji Hiramatsu on 2014/05/24.
//  Copyright 2014 GCREST,Inc. All rights reserved.
//

#ifndef __VitaminProject__VitaminCommandManager__
#define __VitaminProject__VitaminCommandManager__

#include "CommandManager.h"

class VitaminCommandManager : public CommandManager
{
public:
    virtual CommandError executeCommand(int cmdID, void* param);
};

#endif /* defined(__VitaminProject__VitaminCommandManager__) */
