//
//  ApplicationManager.h
//  CoreAppFramework
//
//  Created by Shinji Hiramatsu on 2014/05/24.
//  Copyright 2014 GCREST,Inc. All rights reserved.
//

#ifndef __CoreAppFramework__ApplicationManager__
#define __CoreAppFramework__ApplicationManager__

#include "ISceneManager.h"

typedef int ErrorStatus;


class ISceneManager;
class ICommandManager;
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
    
    /**
     * 一つ前のシーンの情報を削除する
     */
    void deletePreviousScene();
    
    /**
     * 一つ前のシーンIDを取得
     */
    SceneID getPreviousSceneId();
    
    void setSceneManager(ISceneManager* sceneMgr);
    ISceneManager* getSceneManager() const;
    
    void setCommandManager(ICommandManager* cmdMgr);
    ICommandManager* getCommandManager() const;
    
    void setWaitManager(IWaitManager* wtMgr);
    IWaitManager* getWaitManager() const;

    // シーンスタックの情報を取得
    const std::list<SceneBuildInfo> &getSceneInfoStack() {return _sceneInfoStack; }

    // SceneBuildInfo 直接指定版
    void runWithSceneExec(const SceneBuildInfo &sceneInfo);
    void changeSceneExec(const SceneBuildInfo &sceneInfo);
    void pushSceneExec(const SceneBuildInfo &sceneInfo);
    void popSceneExec();
    void backToParentSceneExec(const SceneBuildInfo &sceneInfo);

    // シーンIDを元にstackされている最新のScene情報を探索して取得する
    const SceneBuildInfo getSceneInfoStackById(SceneID sid);

public:
    static ApplicationManager * getInstance();
    
protected:
    std::list<SceneBuildInfo>::iterator removeFromStack(std::list<SceneBuildInfo>::iterator it);
    void deleteRemovedSceneWhenNodeEnter(cocos2d::Node *node);
    
private:
    ISceneManager*      _sceneMgr;
    ICommandManager*    _commandMgr;
    IWaitManager*       _waitMgr;
    std::list<SceneBuildInfo> _sceneInfoStack;
    std::list<SceneParameter*> _removedSceneParams;
    bool _isLock;
};

#endif /* defined(__VitaminProject__ApplicationManager__) */
