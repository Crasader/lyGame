//
//  lyBaseScene.cpp
//
//  ly-Game
//
//  Created by loveyur on 2016/12/14
//  Copyright 2016 loveyur. All rights reserved.
//
//
#include "lyBaseScene.h"
#include "cocos2d.h"

USING_NS_CC;


lyBaseScene::lyBaseScene()
{
    
}

lyBaseScene::~lyBaseScene()
{
    
}

bool lyBaseScene::init()
{
    return true;
}

bool lyBaseScene::nextScene()
{
    return false;
}

bool lyBaseScene::previousScene()
{
    return false;
}

cocos2d::Layer* lyBaseScene::createTopLayer(SceneID sid, SceneParameter* params)
{
    cocos2d::Layer*  pLayer = nullptr;
    
    return pLayer;
}

cocos2d::Scene* lyBaseScene::runWithScene(SceneID sid, SceneParameter* params)
{
    cocos2d::Scene*  pScene = createScene(sid, params);
    if (pScene)
    {
        Director::getInstance()->runWithScene(TransitionFade::create(0.4f, pScene));
    }
    
    return pScene;
}

cocos2d::Scene* lyBaseScene::changeScene(SceneID sid, SceneParameter* params)
{
    cocos2d::Scene*  pScene = createScene(sid, params);
    if (pScene)
    {
        Director::getInstance()->replaceScene(TransitionFade::create(0.4f, pScene));
    }
    return pScene;
}

cocos2d::Scene* lyBaseScene::pushScene(SceneID sid, SceneParameter* params)
{
    cocos2d::Scene*  pScene = createScene(sid, params);
    if (pScene)
    {
        Director::getInstance()->pushScene(TransitionFade::create(0.4f, pScene));
    }
    return pScene;
}

void lyBaseScene::popScene()
{
    Director::getInstance()->popScene();
}

cocos2d::Scene* lyBaseScene::createScene(SceneID sid, SceneParameter* params)
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


