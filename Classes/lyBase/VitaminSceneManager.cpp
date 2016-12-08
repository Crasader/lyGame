//
//  VitaminSceneManager.cpp
//  VitaminProject
//
//  Created by Shinji Hiramatsu on 2014/05/24.
//  Copyright 2014 GCREST,Inc. All rights reserved.
//

#include "VitaminSceneManager.h"
#include "MaintenanceLayer.h"

USING_NS_CC;

VitaminSceneManager::VitaminSceneManager()
: SceneManager()
, _isFade(true)
, _sceneChangingStatus(SceneChangingStatus::NOT_CHANGING)
, _nextSceneChangeInfo()
{
}

cocos2d::Scene* VitaminSceneManager::setupScene(SceneID sid, SceneParameter* params, const std::function<void(cocos2d::Scene*)> &changeFunc)
{
    if (_sceneChangingStatus == SceneChangingStatus::TRANSITION_EXIT) {
        return nullptr;
    }
    if (_sceneChangingStatus == SceneChangingStatus::CHANGE_BLOCKED) {
        return nullptr;
    }
    
    cocos2d::Scene *pScene = createScene(sid, params);
    if (pScene)
    {
        SceneChangeInfo changeInfo;
        
        changeInfo.pScene = pScene;
        changeInfo.exitWithMask = false;
        changeInfo.enterWithMask =  false;
        changeInfo.fade = _isFade;
        changeInfo.fadeTime = 0.4f;
        changeInfo.changeFunc = changeFunc;
        
        // フラグ戻す
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
    
    return pScene;
}

void VitaminSceneManager::execSceneChange(const SceneChangeInfo &info)
{
    info.changeFunc(info.pScene);
}

void VitaminSceneManager::onSceneChangeFinished(float dt)
{
    auto beforeStatus = _sceneChangingStatus;
    _sceneChangingStatus = SceneChangingStatus::NOT_CHANGING;
    
    if (beforeStatus == SceneChangingStatus::CHANGE_BLOCKED) {
        execSceneChange(_nextSceneChangeInfo);
        _nextSceneChangeInfo.pScene->release();
    }
}

cocos2d::Scene* VitaminSceneManager::runWithScene(const SceneID sid, SceneParameter* params /* = nullptr */)
{
    return setupScene(sid, params, [](Scene *scene) {
        Director::getInstance()->runWithScene(scene);
    });
}

cocos2d::Scene* VitaminSceneManager::changeScene(const SceneID sid, SceneParameter* params /* = nullptr */)
{
    return setupScene(sid, params, [](Scene *scene) {
        Director::getInstance()->replaceScene(scene);
    });
}

cocos2d::Scene* VitaminSceneManager::pushScene(SceneID sid, SceneParameter* params)
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

cocos2d::Layer* VitaminSceneManager::createTopLayer(SceneID sid, SceneParameter* params)
{
    cocos2d::Layer*  topLayer = NULL;
    sceneId = sid;
    switch (sid)
    {
        case SCENE_MAINTENANCE:
            _isFade = false;
            topLayer = readSpriteBuilder("ccbi/MaintenanceLayer");
            break;
    }
    
    return topLayer;
}


cocos2d::Layer* VitaminSceneManager::readSpriteBuilder(const char *fileName)
{
    cocos2d::Layer* layer;
    spritebuilder::CCBReader* reader = new spritebuilder::CCBReader(spritebuilder::NodeLoaderLibrary::getInstance());
    layer = (Layer*)reader->readNodeGraphFromFile(fileName, nullptr, Director::getInstance()->getWinSize());
    CC_SAFE_DELETE(reader);
    return layer;

}

VitaminSceneType VitaminSceneManager::getCurrentVitaminSceneType()
{
    return static_cast<VitaminSceneType>(sceneId);
}

std::string VitaminSceneManager::getCurrentVitaminSceneTypeToString()
{
    VitaminSceneType type = getCurrentVitaminSceneType();
#define DEF_SCENE_TYPE(name) {name, #name},
#define DEF_SCENE_TYPE_1(name, val) {name, #name},
    static std::map<int, std::string> _sceneTypeName = {
#include "VitaminSceneID.h"
    };
    if (_sceneTypeName.count(type))
        return _sceneTypeName[type];
    return "invalid scene type";
}
