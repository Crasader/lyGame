//
//  CoreLayer.h
//
//  Created by loveyur on 2016/12/11.
//  Copyright 2016 loveyur All rights reserved.
//

#ifndef __CoreAppFramework__CoreLayer__
#define __CoreAppFramework__CoreLayer__

#include "Subject.h"
#include "cocos2d.h"
#include "ui/UIWidget.h"
#include "picojson.h"
#include "INetworkManager.h"
#include "IWaitManager.h"
#include "cocosbuilder/CCNodeLoaderLibrary.h"

/**
 * define a create function for a specific type, such as Layer
 * @param \__TYPE__  class type to add create(), such as Layer
 */
#define CREATE_WITH_FORMAT_FUNC(__TYPE__) \
static __TYPE__* create() \
{ \
__TYPE__ *pRet = new __TYPE__(); \
if (pRet && pRet->init()) \
{ \
pRet->autorelease(); \
return pRet; \
} \
else \
{ \
delete pRet; \
pRet = nullptr; \
return nullptr; \
} \
} \
static __TYPE__* createWithFile(std::string __PATH__, void* __PARAMS__ = nullptr) \
{ \
__TYPE__ *pRet = new __TYPE__(); \
if (pRet && pRet->initWithFormatFile(__PATH__, __PARAMS__)) \
{ \
pRet->autorelease(); \
return pRet; \
} \
else \
{ \
delete pRet; \
pRet = nullptr; \
return nullptr; \
} \
} \
static __TYPE__* createWithCocoStudioFile(std::string __PATH__, void* __PARAMS__ = nullptr) \
{ \
__TYPE__ *pRet = new __TYPE__(); \
if (pRet && pRet->initWithCocoStudioFile(__PATH__, __PARAMS__)) \
{ \
pRet->autorelease(); \
return pRet; \
} \
else \
{ \
delete pRet; \
pRet = nullptr; \
return nullptr; \
} \
} \
static __TYPE__* createWithCocoStudioSceneFile(std::string __PATH__, void* __PARAMS__ = nullptr) \
{ \
__TYPE__ *pRet = new __TYPE__(); \
if (pRet && pRet->initWithCocoStudioSceneFile(__PATH__, __PARAMS__)) \
{ \
pRet->autorelease(); \
return pRet; \
} \
else \
{ \
delete pRet; \
pRet = nullptr; \
return nullptr; \
} \
} \
static __TYPE__* createWithcocosbuilderFile(std::string __PATH__, cocos2d::Ref* __OWNER__, const cocos2d::Size __BOUNDS__, void* __PARAMS__ = nullptr) \
{ \
cocosbuilder::CCBReader* reader = new cocosbuilder::CCBReader(cocosbuilder::NodeLoaderLibrary::getInstance()); \
__TYPE__ *pRet = (__TYPE__*)reader->readNodeGraphFromFile(__PATH__.c_str(), __OWNER__, __BOUNDS__); \
CC_SAFE_DELETE(reader); \
return pRet; \
} \



// Data type
typedef enum {
    LayoutFormat_Dynamic,
    LayoutFormat_Custom,
    LayoutFormat_CocoStudio,
    LayoutFormat_cocosbuilder,
    
    LayoutFormat_Unknown
} LayoutFormat;


//class ConfigWidget;
class IObserver;

// CoreLayerクラス定義
class CoreLayer   : public cocos2d::LayerColor,
                    public Subject,
                    public INetworkManager,
                    public IWaitManager
{
public:
    CoreLayer();
    virtual ~CoreLayer();
    
    virtual bool init();
    virtual bool initWithFormatFile(std::string& formatFile, void* params = nullptr);
    virtual bool initWithCocoStudioFile(std::string& formatFile, void* params = nullptr);
    virtual bool initWithCocoStudioSceneFile(std::string& formatFile, void* params = nullptr);
    virtual bool initWithcocosbuilderFile(std::string& formatFile, cocos2d::Ref* owner=nullptr, const cocos2d::Size rectSize=cocos2d::Size(0, 0), void* params = nullptr);
    
    virtual void preloadItems();
    virtual void unloadItems();
    virtual void buildViews();
    virtual void start();
    virtual void update(float t);
    virtual void startUpdate();
    virtual void endUpdate();
    virtual void end();
    
    virtual void pause();
    virtual void resume();
    
    virtual void onGamePause(){}    ///< ゲーム特有の処理をしたいとき
    virtual void onGameResume(){}   ///< ゲーム特有の処理をしたいとき
    
    virtual void onEnter();
    virtual void onEnterTransitionDidFinish();
    virtual void onExit();
    virtual void onExitTransitionDidStart();
    
    virtual bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event);
    virtual void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *unused_event);
    virtual void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event);
    
    virtual void attachObserver(IObserver* observer, const int observerId);
    virtual void detachObserver(IObserver* observer, const int observerId);
    virtual bool isAttached(IObserver* observer, const int observerId);
    
    virtual void notify(const int observerId, void* changedBy = nullptr);
    virtual int executeCommand(int cmdID, void* param);
    
    virtual void eventConnectionStart(std::string tag){};
    virtual void eventConnectionEnd(std::string tag, cocos2d::Ref *config){};
    virtual void eventConnectionError(std::string tag, cocos2d::Ref *config){};
    virtual void eventConnectionReview(){};
    virtual void eventConnectionUpdateApplication(){};
    virtual void eventConnectionUpdateResource(){};
    virtual void eventConnectionUpdateMaster(bool refreshUserData){};
    virtual void eventConnectionRetryNotify(cocos2d::Ref *config, bool retryFlg){};
    
    virtual void waitrunWithScene(const SceneBuildInfo &sceneInfo){};
    virtual void waitchangeScene(const SceneBuildInfo &sceneInfo){};
    virtual void waitPushScene(const SceneBuildInfo &sceneInfo){};
    virtual void waitPopScene(){};
    virtual void waitChangePreviousScene(){};

protected:
    virtual cocos2d::Node* getNodeByTag(int tag);
    virtual cocos2d::Node* getNodeByName(const std::string& name);
    virtual cocos2d::Node* getTopLayer();
    virtual cocos2d::Node* getUIItemByName(const std::string& name, Node* startTarget=nullptr, bool isRecursive=true);
    
    void showParticle(std::string filePath, cocos2d::Point pos);
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    void addKeyboardEvents();
    void removeKeyboardEvents();
    void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
    virtual void keyBackClicked(cocos2d::Event* event);
#endif
    
private:
    void addTouchEvents();
    void removeTouchEvents();

    int getDispViewCount(cocos2d::Node* node);

public:
    // タッチイベント
    std::function<bool(cocos2d::Touch*, cocos2d::Event*)> touchBeganFunc;
    std::function<void(cocos2d::Touch*, cocos2d::Event*)> touchMovedFunc;
    std::function<void(cocos2d::Touch*, cocos2d::Event*)> touchEndedFunc;
    
protected:
    bool                _useTouchEvent;
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    bool                _useKeyboardEvent;
#endif
    bool                _autoStart;
    bool                _autoScheduleUpdate;
    cocos2d::Color4B    _backgroundColor;
    LayoutFormat        _layoutFormat;
    
    // Topレイアウト情報
    //cocos2d::ui::Widget*    _topLayout;
    cocos2d::Node*          _topLayout;
    
    // レイアウト配置情報
    //ConfigWidget*       _configFormat;
    
    std::string       _bgm;
    
    // オブザーバーリスト
    std::vector<IObserver *>   _observerList;

};

#endif /* defined(__CoreAppFramework__CoreLayer__) */
