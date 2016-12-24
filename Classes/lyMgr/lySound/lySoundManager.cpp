//
//  lySoundManager.h
//
//  ly-Game
//
//  Created by loveyur on 2016/12/14
//  Copyright 2016 loveyur. All rights reserved.
//
//

#include "lySoundManager.h"
#include "SimpleAudioEngine.h"
#include "cocos2d.h"

#include "network/HttpRequest.h"
#include "network/HttpClient.h"

using namespace CocosDenshion;
USING_NS_CC;

// singleton stuff
static lySoundManager *s_lySoundManager = nullptr;


lySoundManager* lySoundManager::getInstance(void)
{
    if (!s_lySoundManager)
    {
        s_lySoundManager = new lySoundManager();
        s_lySoundManager->init();
    }
    
    return s_lySoundManager;
}


lySoundManager::lySoundManager()
{
    
}

lySoundManager::~lySoundManager()
{
    bgmExtension.clear();
    seExtension.clear();
}

bool lySoundManager::init()
{
    bgmExtension = "mp3";
    seExtension = "mp3";
    return true;
}
void lySoundManager::preloadBGM(const char* name)
{
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic(name);
}
void lySoundManager::playBGM(const char* name, bool isLoop)
{
    std::string bgmName = StringUtils::format("%s.%s", name, bgmExtension.c_str());
    CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic(bgmName.c_str(), isLoop);
}

void lySoundManager::playBGM(const int bgmId, bool isLoop)
{
    std::string bgmName = StringUtils::format("%5d.%s", bgmId, bgmExtension.c_str());
    CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic(bgmName.c_str(), isLoop);
}

void lySoundManager::stopBGM()
{
    CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
}

unsigned int lySoundManager::playSE(const char* name, bool isLoop)
{
    //std::string seName = StringUtils::format("%s.%s", name, seExtension.c_str());
    std::string seName = StringUtils::format("%s", name);
    unsigned int rtn = CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(seName.c_str(), isLoop);
    return rtn;
}

unsigned int lySoundManager::playSE(const int seId, bool isLoop)
{
    //std::string seName = StringUtils::format("%5d.%s", seId, seExtension.c_str());
    std::string seName = StringUtils::format("%5d", seId);
    unsigned int rtn = CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(seName.c_str(), isLoop);
    return rtn;
}

void lySoundManager::stopSE(unsigned int seId)
{
    CocosDenshion::SimpleAudioEngine::getInstance()->stopEffect(seId);
}

void lySoundManager::stopAllSE()
{
    CocosDenshion::SimpleAudioEngine::getInstance()->stopAllEffects();
}

void lySoundManager::preloadSE(const int seId)
{
    std::string seName = StringUtils::format("%5d.%s", seId, seExtension.c_str());
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(seName.c_str());
}

void lySoundManager::unloadSE(const int seId)
{
    std::string seName = StringUtils::format("%5d.%s", seId, seExtension.c_str());
    CocosDenshion::SimpleAudioEngine::getInstance()->unloadEffect(seName.c_str());
}


