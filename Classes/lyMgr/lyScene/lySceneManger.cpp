//
//  lySceneManger.cpp
//
//  ly-Game
//
//  Created by loveyur on 2016/12/14
//  Copyright 2016 loveyur. All rights reserved.
//
//


#include "lySceneManger.h"
#include "TransitionFadeCustom.h"
#include "Caption.h"

#include "loginLayer.h"
#include "loadingText.h"
#include "testLayer.h"


USING_NS_CC;

lySceneManger::lySceneManger()
: lyBaseScene()
, _isFade(true)
, _sceneChangingStatus(SceneChangingStatus::NOT_CHANGING)
, _nextSceneChangeInfo()
{
}

cocos2d::Scene* lySceneManger::setupScene(SceneID sid, SceneParameter* params, const std::function<void(cocos2d::Scene*)> &changeFunc)
{
    if (_sceneChangingStatus == SceneChangingStatus::TRANSITION_EXIT) {
        CCLOG("TRANSITION_EXIT");
        return nullptr;
    }
    if (_sceneChangingStatus == SceneChangingStatus::CHANGE_BLOCKED) {
        CCLOG("CHANGE_BLOCKED");
        return nullptr;
    }
    
    cocos2d::Scene *pScene = createScene(sid, params);
    if (pScene)
    {
        SceneChangeInfo changeInfo;
        
        changeInfo.pScene = pScene;
        changeInfo.exitWithMask =  false;
        changeInfo.enterWithMask =  false;
        changeInfo.fade = _isFade;
        changeInfo.fadeTime = 0.4f;
        changeInfo.changeFunc = changeFunc;
        
        _isFade = true;
        
        if (_sceneChangingStatus == SceneChangingStatus::TRANSITION_ENTER) {
            _sceneChangingStatus = SceneChangingStatus::CHANGE_BLOCKED;
            _nextSceneChangeInfo = changeInfo;
            _nextSceneChangeInfo.pScene->retain();
        }
        else {
            execSceneChange(changeInfo);
        }
    }
    else
        CCLOG("pScene is null");
    
    return pScene;
}

void lySceneManger::execSceneChange(const SceneChangeInfo &info)
{
    if (info.fade)
    {
        _sceneChangingStatus = SceneChangingStatus::TRANSITION_EXIT;
        
        auto fader = TransitionFadeCustom::create(info.fadeTime, info.pScene, info.exitWithMask, info.enterWithMask);
        
        fader->setChangeSceneCallback([this]() {
            _sceneChangingStatus = SceneChangingStatus::TRANSITION_ENTER;
        });
        
        fader->setOnExitCallback([this]() {
            auto scheduler = Director::getInstance()->getScheduler();
            scheduler->schedule(schedule_selector(lySceneManger::onSceneChangeFinished), this, 0, 0, 0, false);
        });
        
        info.changeFunc(fader);
    }
    else
    {
        info.changeFunc(info.pScene);
    }
}

void lySceneManger::onSceneChangeFinished(float dt)
{
    auto beforeStatus = _sceneChangingStatus;
    _sceneChangingStatus = SceneChangingStatus::NOT_CHANGING;
    
    if (beforeStatus == SceneChangingStatus::CHANGE_BLOCKED) {
        execSceneChange(_nextSceneChangeInfo);
        _nextSceneChangeInfo.pScene->release();
    }
}

cocos2d::Scene* lySceneManger::runWithScene(const SceneID sid, SceneParameter* params /* = nullptr */)
{
    return setupScene(sid, params, [](Scene *scene) {
        Director::getInstance()->runWithScene(scene);
    });
}

cocos2d::Scene* lySceneManger::changeScene(const SceneID sid, SceneParameter* params /* = nullptr */)
{
    return setupScene(sid, params, [](Scene *scene) {
        Director::getInstance()->replaceScene(scene);
    });
}

cocos2d::Scene* lySceneManger::pushScene(SceneID sid, SceneParameter* params)
{
    return setupScene(sid, params, [](Scene *scene) {
        Director::getInstance()->pushScene(scene);
    });
}

#ifdef VITAMIN_DEBUG_TOOL_ENABLE
#define PARAM_TYPE_CHECK(p, t) CC_ASSERT(p==nullptr || dynamic_cast<t*>(p));
#else
#define PARAM_TYPE_CHECK(p, t)
#endif


cocos2d::Layer* lySceneManger::createTopLayer(SceneID sid, SceneParameter* params)
{
    cocos2d::Layer*  topLayer = NULL;
    
    sceneId = sid;
    
    switch (sid)
    {
        case SCENE_APP_TOP:
        {
            
        }
            break;
        case SCENE_LOGIN:
        {
            topLayer = loginLayer::createWithcocosbuilderFile("ccbi/login/loginLayer", nullptr, Director::getInstance()->getWinSize());
            PARAM_TYPE_CHECK(params, loginLayerParameter);
        }
            break;
        /*
        case SCENE_LOADING_TEXT:
        {
            topLayer = loadingText::createWithcocosbuilderFile("loading/loadingText", nullptr, Director::getInstance()->getWinSize());
            PARAM_TYPE_CHECK(params, loadingTextParameter);
        }
            break;
         */
        case SCENE_TEST_SCENE:
        {
            topLayer = testLayer::createWithcocosbuilderFile("ccbi/main/testScene", nullptr, Director::getInstance()->getWinSize());
            PARAM_TYPE_CHECK(params, testLayerParameter);
            dynamic_cast<testLayer*>(topLayer)->setSceneParameter((testLayerParameter*) params);

            
            
        }
            break;
            
    }
    
    return topLayer;
}


cocos2d::Layer* lySceneManger::readcocosbuilder(const char *fileName)
{
    cocos2d::Layer* layer;
    cocosbuilder::CCBReader* reader = new cocosbuilder::CCBReader(cocosbuilder::NodeLoaderLibrary::getInstance());
    layer = (Layer*)reader->readNodeGraphFromFile(fileName, nullptr, Director::getInstance()->getWinSize());
    CC_SAFE_DELETE(reader);
    return layer;
}

UISceneType lySceneManger::getCurrentUISceneType()
{
    return static_cast<UISceneType>(sceneId);
}

std::string lySceneManger::getCurrentUISceneTypeToString()
{
    // シーン定義を文字列として展開
    UISceneType type = getCurrentUISceneType();
#define DEF_SCENE_TYPE(name) {name, #name},
#define DEF_SCENE_TYPE_1(name, val) {name, #name},
    static std::map<int, std::string> _sceneTypeName = {
#include "UISceneID.h"
    };
    if (_sceneTypeName.count(type))
        return _sceneTypeName[type];
    return "invalid scene type";
}
