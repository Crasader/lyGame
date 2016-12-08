//
//  SceneManager.cpp
//  CoreAppFramework
//
//  Created by Shinji Hiramatsu on 2014/05/24.
//  Copyright 2014 GCREST,Inc. All rights reserved.
//

#include "SceneManager.h"
#include "cocos2d.h"

USING_NS_CC;


SceneManager::SceneManager()
{
    
}

SceneManager::~SceneManager()
{
    
}

bool SceneManager::init()
{
    return true;
}

bool SceneManager::nextScene()
{
    return false;
}

bool SceneManager::previousScene()
{
    return false;
}
cocos2d::Layer* SceneManager::createTopLayer(SceneID sid, SceneParameter* params)
{
    cocos2d::Layer*  pLayer = nullptr;
    return pLayer;
}


cocos2d::Scene* SceneManager::runWithScene(SceneID sid, SceneParameter* params)
{
    cocos2d::Scene*  pScene = createScene(sid, params);
    if (pScene)
    {
        Director::getInstance()->runWithScene(TransitionFade::create(0.4f, pScene));
    }
    
    return pScene;
}

cocos2d::Scene* SceneManager::changeScene(SceneID sid, SceneParameter* params)
{
    cocos2d::Scene*  pScene = createScene(sid, params);
    if (pScene)
    {
        Director::getInstance()->replaceScene(TransitionFade::create(0.4f, pScene));
    }
    return pScene;
}

cocos2d::Scene* SceneManager::pushScene(SceneID sid, SceneParameter* params)
{
    cocos2d::Scene*  pScene = createScene(sid, params);
    if (pScene)
    {
        Director::getInstance()->pushScene(TransitionFade::create(0.4f, pScene));
    }
    return pScene;
}

void SceneManager::popScene()
{
    Director::getInstance()->popScene();
}

cocos2d::Scene* SceneManager::createScene(SceneID sid, SceneParameter* params)
{
    Scene* pScene = nullptr;
    
    cocos2d::Layer*  pLayer = createTopLayer(sid, params);
    if (pLayer)
    {
        // 'scene' is an autorelease object
        pScene = Scene::create();
        
        // add layer as a child to scene
        pScene->addChild(pLayer);
    }
    
    return pScene;
}


