//
//  lyBaseLayer.h
//
//  ly-Game
//
//  Created by loveyur on 2016/12/14
//  Copyright 2016 loveyur. All rights reserved.
//
//

#ifndef __lyGame__lyBaseLayer__
#define __lyGame__lyBaseLayer__

#include "CoreCCBLayer.h"
#include "Caption.h"
#include "lySceneManger.h"
#include "cocosbuilder/cocosbuilder.h"
#include "UISceneID.h"
#include "PartsBase.h"
#include "lyBaseLayerModule.h"

#define RESULT_LOGIN_OTHER_DEVICE 20001
#define SESSION_PARAM_EXCEPTION 20002

class lyBaseLayerModule;

#define REGISTER_MODULE(T) registerModule<T>(#T)
#define GET_MODULE(T) getModule<T>(#T)

class lyBaseLayer : public CoreCCBLayer
, public cocosbuilder::NodeLoaderListener
, public CaptionDelegate
{
public:
    enum LoadingType {
        NONE,
        TIPS,
        CONNECT,
        PRINCE,
    };
    lyBaseLayer();
    virtual ~lyBaseLayer();
    
    virtual void onEnter();
    virtual void onEnterTransitionDidFinish();
    virtual void onExit();
    virtual void onExitTransitionDidStart();

    virtual void eventConnectionStart(std::string tag);
    virtual void eventConnectionEnd(std::string tag, cocos2d::Ref *config);
    virtual void eventConnectionReview();
    virtual void eventConnectionError(std::string tag, cocos2d::Ref *config);
    virtual void eventConnectionUpdateApplication();
    virtual void eventConnectionUpdateResource();
    virtual void eventConnectionUpdateMaster(bool refreshUserData);
    virtual void eventConnectionMaintenance(const cocos2d::ValueMap &data);
    virtual void eventConnectionRetryNotify(cocos2d::Ref *config, bool retryFlg);
    
    virtual void waitrunWithScene(const SceneBuildInfo &sceneInfo);
    virtual void waitchangeScene(const SceneBuildInfo &sceneInfo);
    virtual void waitPushScene(const SceneBuildInfo &sceneInfo);
    virtual void waitPopScene();
    virtual void waitChangePreviousScene();

    virtual void onNodeLoaded(cocos2d::Node * pNode, cocosbuilder::NodeLoader * pNodeLoader) {};
    
    virtual void completedAnimationSequenceNamed(const char *name){};
    virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector(cocos2d::Ref * pTarget, const char* pSelectorName){ return nullptr;};
    virtual cocos2d::SEL_CallFuncN onResolveCCBCCCallFuncSelector(cocos2d::Ref * pTarget, const char* pSelectorName) { return nullptr; };
    virtual cocos2d::extension::Control::Handler onResolveCCBCCControlSelector(cocos2d::Ref * pTarget, const char* pSelectorName){ return nullptr; };
    virtual bool onAssignCCBMemberVariable(cocos2d::Ref * pTarget, const char * pMemberVariableName, cocos2d::Node * pNode){return false;};

    virtual void pressedBack(Caption *sender){};
    virtual void notifyCaptionStartComplete(Caption *sender){};
    virtual void notifyCaptionEndComplete(Caption *sender){};

    //loading
    void createLoadingLayer(LoadingType type, float fadeOutTime, float fadeInTime);
    void showLoadingLayer(float fadeOutTime = 0.2f, float fadeInTime = 0.2f);
    void hideLoadingLayer(float fadeout=0.2f, float fadein=0.2f);
    virtual void onFinishedLoadingLayer();
    
    
      // 機能モジュール
    template<typename T>
    T* registerModule(const std::string& name)
    {
        CC_ASSERT(_modules.count(name) == 0);
        T* module = new T;
        module->init(this);
        _modules[name] = module;
        return module;
    }
    lyBaseLayerModule *getModule(const std::string& name) {
        if (_modules.count(name)) return _modules[name];
        return nullptr;
    }
    template<typename T>
    T* getModule(const std::string& name)
    {
        return dynamic_cast<T*>(getModule(name));
    }

protected:
    void showCaption();
    void hideCaption();
    void hideCaptionTitle();

    void setCaption(SceneID sid, bool isStatusBarVisible, CaptionDelegate *delegate);
    void setCaptionEnable(bool enable);

    void toResourceDownloadPage(float t);
  

protected:
     virtual void keyBackClicked(cocos2d::Event* event) { CCLOG("lyBaseLayer::keyBackClicked"); };

    cocos2d::Rect getMenuRect(const char* objectName);
    
      void moveMaintenenceScene();

protected:
    // キャプション
    Caption *_caption;
    PartsBase* _loading;
    LayerColor* _fadeLayer;

    bool _retryFlg;

    cocos2d::EventListenerTouchOneByOne* _multiTouchFilter;
    bool _enableMultiTouch;
    
     int _errorCodeNode;
    // モジュール
    std::unordered_map<std::string, lyBaseLayerModule*> _modules;
    
};

#endif /* defined(__lyGame__lyBaseLayer__) */
