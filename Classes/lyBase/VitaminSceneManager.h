//
//  VitaminSceneManager.h
//  VitaminProject
//
//  Created by Shinji Hiramatsu on 2014/05/24.
//  Copyright 2014 GCREST,Inc. All rights reserved.
//

#ifndef __VitaminProject__VitaminSceneManager__
#define __VitaminProject__VitaminSceneManager__

#include "SceneManager.h"
#include "VitaminSceneID.h"

class VitaminSceneManager   :   public SceneManager
{
    virtual cocos2d::Scene* runWithScene(const SceneID sid, SceneParameter* params = nullptr);
    
    virtual cocos2d::Scene* changeScene(const SceneID sid, SceneParameter* params = nullptr);
    
    virtual cocos2d::Scene* pushScene(SceneID sid, SceneParameter* params);

    virtual cocos2d::Layer* createTopLayer(const SceneID sid, SceneParameter* params = nullptr);
    
    cocos2d::Layer* readSpriteBuilder(const char *fileName);
    


public:
    VitaminSceneManager();
    VitaminSceneType getCurrentVitaminSceneType();
    std::string getCurrentVitaminSceneTypeToString();
        
public:
    SceneID sceneId;
    bool _isFade;

private:
    enum SceneChangingStatus {
        NOT_CHANGING,
        TRANSITION_EXIT,
        TRANSITION_ENTER,
        CHANGE_BLOCKED,
    };
    
    struct SceneChangeInfo {
        cocos2d::Scene* pScene;
        bool exitWithMask;
        bool enterWithMask;
        bool fade;
        float fadeTime;
        std::function<void(cocos2d::Scene*)> changeFunc;
    };
    
    SceneChangingStatus _sceneChangingStatus;
    SceneChangeInfo _nextSceneChangeInfo;
    
    cocos2d::Scene* setupScene(SceneID sid, SceneParameter* params, const std::function<void(cocos2d::Scene*)> &changeFunc);
    void execSceneChange(const SceneChangeInfo &param);
    void onSceneChangeFinished(float dt);

};

#endif /* defined(__VitaminProject__VitaminSceneManager__) */
