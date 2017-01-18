//
//  lyPlistManager.h
//  lyGame
//
//  Created by loveyur on 2016/12/24
//  Copyright 2016 loveyur. All rights reserved.
//
//

#include "lyPlistManager.h"

static lyPlistManager* g_pInstacelyPlistManager = nullptr;

lyPlistManager* lyPlistManager::getInstance()
{
    if (!g_pInstacelyPlistManager)
    {
        g_pInstacelyPlistManager = new lyPlistManager();
    }
    return g_pInstacelyPlistManager;
}

lyPlistManager::lyPlistManager()
{
	// TODO: auto generated code
}

lyPlistManager::~lyPlistManager()
{
	// TODO: auto generated code
}



void lyPlistManager::loadTexturePlist(std::string textureName)
{
    if(textureName.empty() || "" == textureName)
        return;
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("TexturePlist/"+textureName+".plist");
}

void lyPlistManager::loadMapPlist(std::string textureName)
{
    if(textureName.empty() || "" == textureName)
        return;
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Texture/Map/Texture_Map_"+textureName+".plist");
}

void lyPlistManager::loadRolePlist(std::string textureName)
{
    if(textureName.empty() || "" == textureName)
        return;
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Texture/Role/Texture_Role_"+textureName+".plist");
}

void lyPlistManager::loadActionPlist(std::string texPath)
{
    if(texPath.find("Map") != std::string::npos)
    {
        std::string mapId = "";
        if(texPath.find("00000") != std::string::npos) mapId = "00000";
        else if (texPath.find("00001") != std::string::npos) mapId = "00001";
        else if (texPath.find("00002") != std::string::npos) mapId = "00002";
        else if (texPath.find("00011") != std::string::npos) mapId = "00011";
        else if (texPath.find("00012") != std::string::npos) mapId = "00012";
        else if (texPath.find("00013") != std::string::npos) mapId = "00013";
        else if (texPath.find("10001") != std::string::npos) mapId = "10001";
        else if (texPath.find("10002") != std::string::npos) mapId = "10002";
        else if (texPath.find("10004") != std::string::npos) mapId = "10004";
        loadMapPlist(mapId);
    }
    else if (texPath.find("Role") != std::string::npos)
    {
        std::string roleName = "";
        if(texPath.find("ant") != std::string::npos) roleName = "ant";
        else if (texPath.find("anyeshizhe") != std::string::npos) roleName = "anyeshizhe";
        else if (texPath.find("bingshe") != std::string::npos) roleName = "bingshe";
        else if (texPath.find("blade") != std::string::npos) roleName = "blade";
        else if (texPath.find("chuansongmen") != std::string::npos) roleName = "chuansongmen";
        else if (texPath.find("Fighter") != std::string::npos) roleName = "Fighter";
        else if (texPath.find("Goblinminer") != std::string::npos) roleName = "Goblinminer";
        else if (texPath.find("Henpli") != std::string::npos) roleName = "Henpli";
        else if (texPath.find("mofashi") != std::string::npos) roleName = "mofashi";
        else if (texPath.find("niutouweibing") != std::string::npos) roleName = "niutouweibing";
        else if (texPath.find("npc") != std::string::npos) roleName = "npc";
        else if (texPath.find("rongjieguai") != std::string::npos) roleName = "rongjieguai";
        loadRolePlist(roleName);
    }
}
