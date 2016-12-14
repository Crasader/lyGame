//
//  ISceneInterfaces.h
//
//  ly-Game
//
//  Created by loveyur on 2016/12/14
//  Copyright 2016 loveyur. All rights reserved.
//
//

#ifndef __CoreAppFramework__ISceneInterfaces_h
#define __CoreAppFramework__ISceneInterfaces_h

#include "cocos2d.h"

typedef int SceneID;

class SceneParameter
{
public:
    SceneParameter() {}
    virtual ~SceneParameter() {}
};

class ISceneInterfaces
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
