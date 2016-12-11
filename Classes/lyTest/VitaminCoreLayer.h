//
//  VitaminCoreLayer.h
//  vitaminProject
//
//  Created by Shinji Hiramatsu on 2014/05/24.
//  Copyright 2014 GCREST,Inc. All rights reserved.
//

#ifndef __vitaminProject__VitaminCoreLayer__
#define __vitaminProject__VitaminCoreLayer__

#include "CoreCCBLayer.h"
#include "Caption.h"
#include "lySceneManager.h"
#include "cocosbuilder/cocosbuilder.h"
#include "UISceneID.h"


#define RESULT_LOGIN_OTHER_DEVICE 20001
#define SESSION_PARAM_EXCEPTION 20002

class VitaminCoreLayerModule;

#define REGISTER_MODULE(T) registerModule<T>(#T)
#define GET_MODULE(T) getModule<T>(#T)

class VitaminCoreLayer : public CoreCCBLayer
, public cocosbuilder::NodeLoaderListener
, public CaptionDelegate
{
public:
    VitaminCoreLayer();
    virtual ~VitaminCoreLayer();
    
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
    VitaminCoreLayerModule *getModule(const std::string& name) {
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
     virtual void keyBackClicked(cocos2d::Event* event) { CCLOG("VitaminCoreLayer::keyBackClicked"); };

    cocos2d::Rect getMenuRect(const char* objectName);
    
      void moveMaintenenceScene();

protected:
    // キャプション
    Caption *_caption;
    LayerColor* _fadeLayer;

    bool _retryFlg;

    cocos2d::EventListenerTouchOneByOne* _multiTouchFilter;
    bool _enableMultiTouch;
    
     int _errorCodeNode;
    // モジュール
    std::unordered_map<std::string, VitaminCoreLayerModule*> _modules;
    
};

#endif /* defined(__vitaminProject__VitaminCoreLayer__) */
