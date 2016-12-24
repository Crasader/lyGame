//
//  ApplicationManager.h
//
//  ly-Game
//
//  Created by loveyur on 2016/12/14
//  Copyright 2016 loveyur. All rights reserved.
//
//
#ifndef __lyGame__ApplicationManager__
#define __lyGame__ApplicationManager__

#include "ISceneInterfaces.h"


typedef int ErrorStatus;


class ISceneInterfaces;
class ICommandManager;
class IAppSoundManager;
class IImageManager;
class IAdwareManager;
class IWaitManager;

class SceneBuildInfo
{
public:
    SceneBuildInfo(SceneID sid, SceneParameter* param)
    : sid(sid) , param(param)
    {
    }
    
    virtual ~SceneBuildInfo() {}
    
    SceneID sid;
    SceneParameter* param;
};


class ApplicationManager
{
public:
    ApplicationManager();
    virtual ~ApplicationManager();
    
    bool init();
    
    void resume();
    void pause();
    
    void preloadImages();
    void unloadImages();
    
    void lock();
    void unLock();
    bool isLock() { return _isLock; }
    
    ErrorStatus executeCommand(int cmdID, void* param);
    
    void runWithScene(SceneID sid) {
        runWithSceneExec(SceneBuildInfo(sid, nullptr));
    }
    
    template<class T>
    void runWithScene(SceneID sid, const T& param) {
        runWithSceneExec(SceneBuildInfo(sid, new T(param)));
    }
    
    void changeScene(SceneID sid) {
        changeSceneExec(SceneBuildInfo(sid, nullptr));
    }
    
    template<class T>
    void changeScene(SceneID sid, const T& param) {
        changeSceneExec(SceneBuildInfo(sid, new T(param)));
    }
    
    void pushScene(SceneID sid) {
        pushSceneExec(SceneBuildInfo(sid, nullptr));
    }
    
    template<class T>
    void pushScene(SceneID sid, const T& param) {
        pushSceneExec(SceneBuildInfo(sid, new T(param)));
    }

    void popScene() {
        popSceneExec();
    }
    
    template<class T>
    void popScene() {
        popSceneExec();
    }

    void backToParentScene(SceneID sid) {
        backToParentSceneExec(SceneBuildInfo(sid, nullptr));
    }
    
    template<class T>
    void backToParentScene(SceneID sid, const T& param) {
        backToParentSceneExec(SceneBuildInfo(sid, new T(param)));
    }
    
    
    bool hasPreviousScene() const;
    void changePreviousScene();
    void clearSceneHistory();
    void clearPreviousSceneHistory();
    

    void deletePreviousScene();
    
    SceneID getPreviousSceneId();
    
    void setSceneManager(ISceneInterfaces* sceneMgr);
    ISceneInterfaces* getSceneManager() const;
    
    void setCommandManager(ICommandManager* cmdMgr);
    ICommandManager* getCommandManager() const;
    
    void setSoundManager(IAppSoundManager* cmdMgr);
    IAppSoundManager* getSoundManager() const;
    
    void setAdwareManager(IAdwareManager* adMgr);
    IAdwareManager* getAdwareManager() const;

    void setWaitManager(IWaitManager* wtMgr);
    IWaitManager* getWaitManager() const;

    const std::list<SceneBuildInfo> &getSceneInfoStack() {return _sceneInfoStack; }

    void runWithSceneExec(const SceneBuildInfo &sceneInfo);
    void changeSceneExec(const SceneBuildInfo &sceneInfo);
    void pushSceneExec(const SceneBuildInfo &sceneInfo);
    void popSceneExec();
    void backToParentSceneExec(const SceneBuildInfo &sceneInfo);

    const SceneBuildInfo getSceneInfoStackById(SceneID sid);

public:
    static ApplicationManager * getInstance();
    
protected:
    std::list<SceneBuildInfo>::iterator removeFromStack(std::list<SceneBuildInfo>::iterator it);
    void deleteRemovedSceneWhenNodeEnter(cocos2d::Node *node);
    
private:
    ISceneInterfaces*      _sceneMgr;
    ICommandManager*    _commandMgr;
    IAppSoundManager*   _soundMgr;
    IImageManager*      _imageMgr;
    IAdwareManager*         _adwareMgr;
    IWaitManager*       _waitMgr;
    std::list<SceneBuildInfo> _sceneInfoStack;
    std::list<SceneParameter*> _removedSceneParams;
    bool _isLock;
};

#endif /* defined(__VitaminProject__ApplicationManager__) */
