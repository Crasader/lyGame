//
//  ISceneManager.h
//  CoreAppFramework
//
//  Created by Shinji Hiramatsu on 2014/05/24.
//  Copyright 2014 GCREST,Inc. All rights reserved.
//

#ifndef __CoreAppFramework__ISceneManager_h
#define __CoreAppFramework__ISceneManager_h

#include "cocos2d.h"

typedef int SceneID;

class SceneParameter
{
public:
    SceneParameter() {}
    virtual ~SceneParameter() {}
};

class ISceneManager
{
public:

    virtual bool init() = 0;

    virtual bool nextScene() = 0;
    
    virtual bool previousScene() = 0;
    
    virtual cocos2d::Scene* runWithScene(const SceneID sid, SceneParameter* params = nullptr) = 0;

    virtual cocos2d::Scene* changeScene(const SceneID sid, SceneParameter* params = nullptr) = 0;
    
    virtual cocos2d::Scene* pushScene(SceneID sid, SceneParameter* params = nullptr) = 0;
    
    virtual void popScene() = 0;

    virtual cocos2d::Scene* createScene(const SceneID sid, SceneParameter* params = nullptr) = 0;
};


#endif
