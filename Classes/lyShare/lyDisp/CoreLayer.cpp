//
//  CoreLayer.cpp
//  CoreAppFramework
//
//  Created by Shinji Hiramatsu on 2014/05/24.
//  Copyright 2014 GCREST,Inc. All rights reserved.
//

#include "CoreLayer.h"
#include "StrUtil.h"
#include "Subject.h"
#include "IObserver.h"
#include "ApplicationID.h"
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"
#include "extensions/cocos-ext.h"
#include "spritebuilder/CCNodeLoaderLibrary.h"
#include "cocosbuilder/CCNodeLoaderLibrary.h"
#include "ApplicationManager.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace ui;
using namespace cocostudio;


CoreLayer::CoreLayer()
    : LayerColor(),
    _useTouchEvent(true),
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    _useKeyboardEvent(true),
#endif
    _autoStart(true),
    _autoScheduleUpdate(false),
    _backgroundColor(Color4B(0, 0, 0, 0)),
    _topLayout(nullptr),
    touchBeganFunc(nullptr),
    touchMovedFunc(nullptr),
    touchEndedFunc(nullptr),
    _layoutFormat(LayoutFormat_Unknown)
{
    
}

CoreLayer::~CoreLayer()
{
    
}

bool CoreLayer::init()
{
    // レイヤーの初期化　背景を黒に設定
    if (!LayerColor::initWithColor(Color4B(0,0,0,0)))
    {
        return false;
    }

    _layoutFormat = LayoutFormat_Dynamic;

    // 表示データの構築
    buildViews();
    
    notify(SceneEvent_Init, nullptr);
    
    return true;
}

bool CoreLayer::initWithFormatFile(std::string& formatFile, void* params)
{
    // レイヤーの初期化　背景を黒に設定
    if (!LayerColor::initWithColor(Color4B(0,0,0,0)))
    {
        return false;
    }

    // 表示データの構築
    buildViews();
    
    return true;
}

bool CoreLayer::initWithCocoStudioFile(std::string& formatFile, void* params)
{
    // レイヤーの初期化　背景を黒に設定
    if (!LayerColor::initWithColor(Color4B(0,0,0,0)))
    {
        return false;
    }
  
    // レイヤーのレイアウト情報を取得
    if (formatFile.size() > 0)
    {
        _topLayout = dynamic_cast<Layout*>(GUIReader::getInstance()->widgetFromJsonFile(formatFile.c_str()));
        
        if (_topLayout)
        {
            this->addChild(_topLayout);
            _layoutFormat = LayoutFormat_CocoStudio;
        }
    }
    
    // 表示データの構築
    buildViews();
    
    return true;
}

bool CoreLayer::initWithCocoStudioSceneFile(std::string& formatFile, void* params)
{
    // レイヤーの初期化　背景を黒に設定
    if (!LayerColor::initWithColor(Color4B(0,0,0,0)))
    {
        return false;
    }
    
    // レイヤーのレイアウト情報を取得
    if (formatFile.size() > 0)
    {
        _topLayout = dynamic_cast<Layout*>(SceneReader::getInstance()->createNodeWithSceneFile(formatFile.c_str()));
        
        if (_topLayout)
        {
            this->addChild(_topLayout);
            _layoutFormat = LayoutFormat_CocoStudio;
        }
    }
    
    // 表示データの構築
    buildViews();
    
    return true;
}


bool CoreLayer::initWithSpriteBuilderFile(std::string& formatFile, cocos2d::Ref* owner, const cocos2d::Size rectSize, void* params)
{
    // レイヤーの初期化　背景を黒に設定
    if (!LayerColor::initWithColor(Color4B(0,0,0,0)))
    {
        return false;
    }
    
    
    // SpriteBuilderのレイヤーのレイアウト情報を取得
    if (formatFile.size() > 0)
    {
        Size nodeSize = rectSize;
        if (nodeSize.width == 0 && nodeSize.height == 0)
            nodeSize = Director::getInstance()->getWinSize();
        
        // SpriteBuilderのCCBをロード
        spritebuilder::CCBReader* reader = new spritebuilder::CCBReader(spritebuilder::NodeLoaderLibrary::getInstance());
        _topLayout = (Node*)reader->readNodeGraphFromFile(formatFile.c_str(), owner, nodeSize);
        CC_SAFE_DELETE(reader);
        
        if (_topLayout)
        {
            this->addChild(_topLayout);
            _layoutFormat = LayoutFormat_SpriteBuilder;
        }
    }
    
    // 表示データの構築
    buildViews();
    
    return true;
}



void CoreLayer::preloadItems()
{
    
}

void CoreLayer::unloadItems()
{
    
}

void CoreLayer::buildViews()
{
}

void CoreLayer::start()
{
    addTouchEvents();
    
    if (_autoScheduleUpdate)
        startUpdate();
    
    notify(SceneEvent_Start, nullptr);
}

void CoreLayer::update(float t)
{
}

void CoreLayer::startUpdate()
{
    this->scheduleUpdate();
}

void CoreLayer::endUpdate()
{
    this->unscheduleUpdate();
}

void CoreLayer::end()
{
    this->stopAllActions();
    removeTouchEvents();
    
    notify(SceneEvent_End, nullptr);
}

void CoreLayer::pause()
{
    this->stopAllActions();
    removeTouchEvents();
}

void CoreLayer::resume()
{
    addTouchEvents();
}


void CoreLayer::onEnter()
{
    preloadItems();
	LayerColor::onEnter();
    
    notify(SceneEvent_Enter, nullptr);
}

void CoreLayer::onEnterTransitionDidFinish()
{
	LayerColor::onEnterTransitionDidFinish();

    if (_autoStart)
    {   // EnterTransition完了後に自動的に開始
        start();
    }
    else
    {   // EnterTransition完了後にサブクラス側で制御する場合は、
        // 任意の場所で、start()を呼んで下さい。
        
    }
    notify(SceneEvent_EnterTransitionDidFinish, nullptr);
}

void CoreLayer::onExit()
{
    notify(SceneEvent_Exit, nullptr);
    
    end();
    unloadItems();
	LayerColor::onExit();
}

void CoreLayer::onExitTransitionDidStart()
{
    notify(SceneEvent_ExitTransitionDidStart, nullptr);
    
	LayerColor::onExitTransitionDidStart();
}

bool CoreLayer::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event)
{
    return true;
}

void CoreLayer::onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *unused_event)
{
    
}

void CoreLayer::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event)
{
    
}

void CoreLayer::addTouchEvents()
{
    if (_useTouchEvent)
    {
        // Register Touch Event
        auto listener = EventListenerTouchOneByOne::create();
        listener->setSwallowTouches(_swallowsTouches);
        
        listener->onTouchBegan = CC_CALLBACK_2(CoreLayer::onTouchBegan, this);
        listener->onTouchMoved = CC_CALLBACK_2(CoreLayer::onTouchMoved, this);
        listener->onTouchEnded = CC_CALLBACK_2(CoreLayer::onTouchEnded, this);
        listener->onTouchCancelled = CC_CALLBACK_2(CoreLayer::onTouchCancelled, this);
        
        _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
        _touchListener = listener;
    }
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    addKeyboardEvents();
#endif
}

void CoreLayer::removeTouchEvents()
{
    if (_useTouchEvent && _touchListener != nullptr)
    {
        _eventDispatcher->removeEventListener(_touchListener);
        _touchListener = nullptr;
    }
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    removeKeyboardEvents();
#endif
}

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
void CoreLayer::addKeyboardEvents()
{
	if (_useKeyboardEvent)
	{
        auto keyboardListener = EventListenerKeyboard::create();
		keyboardListener->onKeyReleased = CC_CALLBACK_2(CoreLayer::onKeyReleased, this);
		_eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener, this);
		_keyboardListener = keyboardListener;
	}
}

void CoreLayer::removeKeyboardEvents()
{
    if (_useKeyboardEvent && _keyboardListener != nullptr)
    {
        _eventDispatcher->removeEventListener(_keyboardListener);
        _keyboardListener = nullptr;
    }
}

void CoreLayer::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{
	if (keyCode == EventKeyboard::KeyCode::KEY_ESCAPE)
	{
		keyBackClicked(event);
	}
}

void CoreLayer::keyBackClicked(cocos2d::Event* event)
{
    CCLOG("Pressed Backkey");
}
#endif

/**
 * 画面の表示データを集計する
 */
int CoreLayer::getDispViewCount(cocos2d::Node* node)
{
    int     count = 0;
    if (node)
    {
        count = static_cast<int>(node->getChildrenCount());
        
        auto children = node->getChildren();
        if (children.size() > 0)
        {
            ssize_t     len = children.size();
            for (ssize_t i = 0; i < len; i++)
            {
                Node* content = (Node *)children.at(i);
                if (content)
                {
                    count += getDispViewCount(content);
                }
            }
        }
    }
    
    return count;
}

cocos2d::Node* CoreLayer::getNodeByTag(int tag)
{
    Node* target = this->getChildByTag(tag);
    
    if (!target)
    {
        for (auto child : this->getChildren())
        {
            Node*  findNode = child->getChildByTag(tag);
            if (findNode)
            {
                target = findNode;
                break;
            }
        }
    }
    
    return target;
}

cocos2d::Node* CoreLayer::getNodeByName(const std::string& name)
{
    Node*   target = nullptr;
    
    for (auto child : this->getChildren())
    {
        if (typeid(*child) == typeid(Widget))
        {
            Widget* item = dynamic_cast<Widget*>(child);
            if (item->getName() == name)
            {
                target = child;
                break;
            }
        }
    }
    
    return target;
}

cocos2d::Node* CoreLayer::getUIItemByName(const std::string& name, Node* startWidget, bool isRecursive)
{
    if (!startWidget)
    {   // 検索開始Widgetが未設定の場合、topLayoutから検索を行う
        startWidget = _topLayout;
    }
    
    Node*  target = nullptr;
    for (auto child : startWidget->getChildren())
    {
        if (typeid(*child) == typeid(Widget) ||
            typeid(*child) == typeid(ListView) ||
            typeid(*child) == typeid(Layout) ||
            typeid(*child) == typeid(ImageView) ||
            typeid(*child) == typeid(Button) ||
            typeid(*child) == typeid(CheckBox) ||
            typeid(*child) == typeid(TextAtlas) ||
            typeid(*child) == typeid(TextBMFont) ||
            typeid(*child) == typeid(Text) ||
            typeid(*child) == typeid(LoadingBar) ||
            typeid(*child) == typeid(Slider) ||
            typeid(*child) == typeid(TextField) ||
            typeid(*child) == typeid(ui::ScrollView) ||
            typeid(*child) == typeid(PageView))
        {
            Widget* item = dynamic_cast<Widget*>(child);
            if (item->getName() == name)
            {
                target = item;
                break;
            }
            else
            {
                target = dynamic_cast<Node*>(getUIItemByName(name, item, isRecursive));
                if (target)
                {
                    break;
                }
            }
        }
    }
    
    return target;
}

cocos2d::Node* CoreLayer::getTopLayer()
{
    Vector<Node *> nodeList = this->getChildren();
    Vector<Node *>::iterator iter = nodeList.begin();
    Node* target = (*iter);
    
    return target;
    
}

void CoreLayer::showParticle(std::string particlePath, cocos2d::Point pos)
{
    ParticleSystemQuad *particleSystem = ParticleSystemQuad::create(particlePath.c_str());
    if (particleSystem)
    {
        particleSystem->setPosition(pos);
        particleSystem->setAutoRemoveOnFinish(true);
        this->addChild(particleSystem);
    }
}


// Attach an observer that uses regular attachment to this subject.
void CoreLayer::attachObserver(IObserver* observer, const int observerId)
{
    bool    found = false;
    std::vector<IObserver *>::iterator iter = fObservers.begin();
    while (iter != fObservers.end())
    {
        IObserver*  target = *iter;
        if (target == observer)
        {
            found = true;
            break;
        }
        iter++;
    }
    
    if (!found)
        fObservers.push_back(observer);
}

// Detach an observer that uses regular attachment from this subject.
void CoreLayer::detachObserver(IObserver* observer, const int observerId)
{
    std::vector<IObserver *>::iterator iter = fObservers.begin();
    while (iter != fObservers.end())
    {
        IObserver*  target = *iter;
        if (target == observer)
        {
            iter = fObservers.erase( iter );
            break;
        }
        iter++;
    }
}

// Check whether the observer is attached to this subject.
bool CoreLayer::isAttached(IObserver* observer, const int observerId)
{
    return fObservers.size() > 0? true: false;
}

void CoreLayer::notify(const int observerId, void* changedBy)
{
    Subject::notify(observerId, changedBy);
}

int CoreLayer::executeCommand(int cmdID, void* param)
{
    int     errStatus = 0;
    
    switch (cmdID)
    {
        case 0:
            break;
    }
    
    return errStatus;
}
