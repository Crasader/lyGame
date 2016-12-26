//
//  lySceneManger.h
//
//  ly-Game
//
//  Created by loveyur on 2016/12/14
//  Copyright 2016 loveyur. All rights reserved.
//
//

#ifndef __lyGame__lySceneManger__
#define __lyGame__lySceneManger__

#include "lyBaseScene.h"
#include "UISceneID.h"

class lySceneManger   :   public lyBaseScene
{
    virtual cocos2d::Scene* runWithScene(const SceneID sid, SceneParameter* params = nullptr);
    
    virtual cocos2d::Scene* changeScene(const SceneID sid, SceneParameter* params = nullptr);
    
    virtual cocos2d::Scene* pushScene(SceneID sid, SceneParameter* params);

    virtual cocos2d::Layer* createTopLayer(const SceneID sid, SceneParameter* params = nullptr);
    
    cocos2d::Layer* readcocosbuilder(const char *fileName);
    


public:
    lySceneManger();
    UISceneType getCurrentUISceneType();
    std::string getCurrentUISceneTypeToString();
        
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

#endif /* defined(__lyGame__lySceneManger__) */
