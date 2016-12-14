//
//  ApplicationManager.cpp
//
//  ly-Game
//
//  Created by loveyur on 2016/12/14
//  Copyright 2016 loveyur. All rights reserved.
//
//

#include "ApplicationManager.h"
#include "ISceneInterfaces.h"
#include "ICommandManager.h"
#include "CoreLayer.h"

static ApplicationManager *s_appMgr = nullptr;


ApplicationManager* ApplicationManager::getInstance()
{
    if (!s_appMgr)
    {
        s_appMgr = new ApplicationManager();
        s_appMgr->init();
    }
    
    return s_appMgr;
}

ApplicationManager::ApplicationManager()    :
    _sceneMgr(nullptr),
    _commandMgr(nullptr),
    _soundMgr(nullptr),
    _imageMgr(nullptr),
    _adwareMgr(nullptr),
    _waitMgr(nullptr),
    _sceneInfoStack(),
    _removedSceneParams(),
    _isLock(false)
{
    
}

ApplicationManager::~ApplicationManager()
{
    clearSceneHistory();
    
    for (auto &sceneParam : _removedSceneParams) {
        delete sceneParam;
    }
    _removedSceneParams.clear();
}

bool ApplicationManager::init()
{
    return true;
}

void ApplicationManager::resume()
{
    auto runningScene = cocos2d::Director::getInstance()->getRunningScene();
    if (!runningScene)
    {
        return;
    }
    auto children = runningScene->getChildren();
    if (!children.empty()) {
        auto coreLayer = dynamic_cast<CoreLayer*>(children.front());
        if (coreLayer) {
            coreLayer->onGameResume();
        }
    }
}

void ApplicationManager::pause()
{
    auto runningScene = cocos2d::Director::getInstance()->getRunningScene();
    if (!runningScene)
    {
        return;
    }
    auto children = runningScene->getChildren();
    if (!children.empty()) {
        auto coreLayer = dynamic_cast<CoreLayer*>(children.front());
        if (coreLayer) {
            coreLayer->onGamePause();
        }
    }
}


void ApplicationManager::preloadImages()
{
    
}

void ApplicationManager::unloadImages()
{
}

void ApplicationManager::lock()
{
    _isLock = true;
}

void ApplicationManager::unLock()
{
    _isLock = false;
}

ErrorStatus ApplicationManager::executeCommand(int cmdID, void* param)
{
    ErrorStatus     err = 0;
    if (_commandMgr)
    {
        err = _commandMgr->executeCommand(cmdID, param);
    }
    return err;
}

void ApplicationManager::runWithSceneExec(const SceneBuildInfo &sceneInfo)
{
    if (_sceneMgr)
    {
        
        if (isLock())
        {
            if (_waitMgr != nullptr)
            {
                _waitMgr->waitrunWithScene(sceneInfo);
                return;
            }
        }
        cocos2d::Scene *newScene =_sceneMgr->runWithScene(sceneInfo.sid, sceneInfo.param);
        if (newScene)
        {
            _sceneInfoStack.push_front(sceneInfo);
        }
        else
            CCLOG("newScene is null");
    }
    else
        CCLOG("_sceneMgr is null");
}

void ApplicationManager::changeSceneExec(const SceneBuildInfo &sceneInfo)
{
    if (_sceneMgr)
    {
        
        if (isLock())
        {
            if (_waitMgr != nullptr)
            {
                _waitMgr->waitchangeScene(sceneInfo);
                return;
            }
        }
        cocos2d::Scene *newScene = _sceneMgr->changeScene(sceneInfo.sid, sceneInfo.param);
        if (newScene != nullptr) {
            _sceneInfoStack.push_front(sceneInfo);
            deleteRemovedSceneWhenNodeEnter(newScene);
        }
    }
}

void ApplicationManager::pushSceneExec(const SceneBuildInfo &sceneInfo)
{
    if (_sceneMgr)
    {
        if (isLock())
        {
            if (_waitMgr != nullptr)
            {
                _waitMgr->waitPushScene(sceneInfo);
                return;
            }
        }
        cocos2d::Scene *newScene = _sceneMgr->pushScene(sceneInfo.sid, sceneInfo.param);
        if (newScene != nullptr) {
            _sceneInfoStack.push_front(sceneInfo);
        }
    }
}

void ApplicationManager::popSceneExec()
{
    if (_sceneMgr)
    {
        if (isLock())
        {
            if (_waitMgr != nullptr)
            {
                _waitMgr->waitPopScene();
                return;
            }
        }
        _sceneMgr->popScene();
    }
}

void ApplicationManager::changePreviousScene()
{
    if (_sceneMgr && hasPreviousScene())
    {
        if (isLock())
        {
            if (_waitMgr != nullptr)
            {
                _waitMgr->waitChangePreviousScene();
                return;
            }
        }
        auto prevSceneIt = ++(_sceneInfoStack.begin());
        
        cocos2d::Scene *newScene = _sceneMgr->changeScene(prevSceneIt->sid, prevSceneIt->param);
        if (newScene != nullptr) {
            removeFromStack(_sceneInfoStack.begin());
            deleteRemovedSceneWhenNodeEnter(newScene);
        }
    }
}

void ApplicationManager::backToParentSceneExec(const SceneBuildInfo &sceneInfo)
{
    auto pos = _sceneInfoStack.end();
    for(auto itr = _sceneInfoStack.begin(); itr != _sceneInfoStack.end(); ++itr)
    {
        if (itr->sid == sceneInfo.sid)
        {
            pos = itr;
            break;
        }
    }
    if (pos != _sceneInfoStack.end())
    {
        pos++;
        auto itr = _sceneInfoStack.begin();
        while(itr != pos)
        {
            itr = removeFromStack(itr);
        }
    }

    changeSceneExec(sceneInfo);
}



bool ApplicationManager::hasPreviousScene() const
{
    return _sceneInfoStack.size() >= 2;
}

void ApplicationManager::clearSceneHistory()
{
    while (_sceneInfoStack.size() > 0) {
        removeFromStack(_sceneInfoStack.begin());
    }
}

void ApplicationManager::clearPreviousSceneHistory()
{
    if (hasPreviousScene())
    {
        auto itr = _sceneInfoStack.begin()++;
        while(itr != _sceneInfoStack.end())
        {
            itr = removeFromStack(itr);
        }
    }
}

void ApplicationManager::deletePreviousScene()
{
    if (_sceneMgr && hasPreviousScene())
    {
        removeFromStack(_sceneInfoStack.begin());
    }
}

SceneID ApplicationManager::getPreviousSceneId()
{
    if (_sceneMgr && hasPreviousScene())
    {
        std::list<SceneBuildInfo>::iterator it;
        it = _sceneInfoStack.begin();
        std::advance(it, 1);
        
        if(it != _sceneInfoStack.end())
        {
            return it->sid;
        }
    }
    
    return 0;
}

const SceneBuildInfo ApplicationManager::getSceneInfoStackById(SceneID sid) {
    // スタックの中からsidを検索
    auto pos = _sceneInfoStack.end();
    for(auto itr = _sceneInfoStack.begin(); itr != _sceneInfoStack.end(); ++itr)
    {
        if (itr->sid == sid)
        {
            pos = itr;
            break;
        }
    }

    if (pos != _sceneInfoStack.end()) {
        return SceneBuildInfo(pos->sid, pos->param);
    }
    return SceneBuildInfo(0, nullptr);
}

std::list<SceneBuildInfo>::iterator ApplicationManager::removeFromStack(std::list<SceneBuildInfo>::iterator it)
{
    if (it->param) {
        _removedSceneParams.push_back(it->param);
    }
    
    return _sceneInfoStack.erase(it);
}

void ApplicationManager::deleteRemovedSceneWhenNodeEnter(cocos2d::Node *node)
{
    // clone deleting targets
    auto deletingSceneParams = _removedSceneParams;
    
    node->setOnEnterCallback([this, deletingSceneParams]() {
        for (auto &sceneParam : deletingSceneParams) {
            auto it = std::find(_removedSceneParams.begin(), _removedSceneParams.end(), sceneParam);
            
            if (it != _removedSceneParams.end()) {
                delete sceneParam;
                _removedSceneParams.erase(it);
            }
        }
    });
}

void ApplicationManager::setSceneManager(ISceneInterfaces* sceneMgr)
{
    _sceneMgr = sceneMgr;
}

ISceneInterfaces* ApplicationManager::getSceneManager() const
{
    return _sceneMgr;
}

void ApplicationManager::setCommandManager(ICommandManager* cmdMgr)
{
    _commandMgr = cmdMgr;
}

ICommandManager* ApplicationManager::getCommandManager() const
{
    return _commandMgr;
}

void ApplicationManager::setAdwareManager(IAdwareManager* adwareMgr)
{
    _adwareMgr = adwareMgr;
}

IAdwareManager* ApplicationManager::getAdwareManager() const
{
    return _adwareMgr;
}

void ApplicationManager::setWaitManager(IWaitManager* wtMgr)
{
    _waitMgr = wtMgr;
}

IWaitManager* ApplicationManager::getWaitManager() const
{
    return _waitMgr;
}

