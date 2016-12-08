//
//  CommandManager.cpp
//  CoreAppFramework
//
//  Created by Shinji Hiramatsu on 2014/05/24.
//  Copyright 2014 GCREST,Inc. All rights reserved.
//

#include "CommandManager.h"
#include "cocos2d.h"

static CommandManager *s_configCmdMgr = nullptr;

CommandManager* CommandManager::getInstance()
{
    if (!s_configCmdMgr)
    {
        s_configCmdMgr = new CommandManager();
        s_configCmdMgr->init();
    }
    
    return s_configCmdMgr;
}

CommandManager::CommandManager()
{
}

CommandManager::~CommandManager()
{
}

bool CommandManager::init()
{
    return true;
}

CommandError CommandManager::executeCommand(int cmdID, void* param)
{
    CommandError     err = 0;
    
    return err;
}

