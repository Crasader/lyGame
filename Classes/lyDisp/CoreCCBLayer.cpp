//
//  CoreCCBLayer.cpp
//
//  Created by loveyur on 2016/12/11.
//  Copyright 2016 loveyur All rights reserved.
//
//

#include "CoreCCBLayer.h"
#include "ApplicationID.h"
#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "cocosbuilder/CCNodeLoaderLibrary.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace cocosbuilder;

/**
 * CoreCCBLayer Constructor
 */
CoreCCBLayer::CoreCCBLayer()    :
    CoreLayer(),
_animationManager(nullptr)
{
    
}

/**
 * CoreCCBLayer Destructor
 */
CoreCCBLayer::~CoreCCBLayer()
{
    
}

/**
 * 初期化処理
 */
bool CoreCCBLayer::init()
{
    if (!CoreLayer::init())
    {
        return false;
    }
    
    return true;
}

/**
 * CoreCCBNode create処理
 */
CoreCCBLayer* CoreCCBLayer::create()
{
    CoreCCBLayer *layer = new CoreCCBLayer();
    if (layer && layer->init())
    {
        layer->autorelease();
        return layer;
    }
    CC_SAFE_DELETE(layer);
    return nullptr;
}

void CoreCCBLayer::onExit()
{
    if (_animationManager) {
        _animationManager->setDelegate(nullptr);
    }

    CoreLayer::onExit();
}

void CoreCCBLayer::setAnimationManager()
{
    if (this->getUserObject() != nullptr) {
        // アニメーションマネージャー設定
        _animationManager = (cocosbuilder::CCBAnimationManager *)this->getUserObject();
        _animationManager->setDelegate(this);
    }
}

cocosbuilder::CCBAnimationManager *CoreCCBLayer::getAnimationManager()
{
    return _animationManager;
}

//----------------------------------------------------
// CCBSelectorResolverクラスのインターフェース
//----------------------------------------------------

/**
 * onResolveCCBCCMenuItemSelector
 */
cocos2d::SEL_MenuHandler CoreCCBLayer::onResolveCCBCCMenuItemSelector(cocos2d::Ref * pTarget, const char* pSelectorName)
{
    return nullptr;
}

/**
 * onResolveCCBCCCallFuncSelector
 */
cocos2d::SEL_CallFuncN CoreCCBLayer::onResolveCCBCCCallFuncSelector(cocos2d::Ref * pTarget, const char* pSelectorName)
{
    return nullptr;
}

/**
 * onResolveCCBCCControlSelector
 */
cocos2d::extension::Control::Handler CoreCCBLayer::onResolveCCBCCControlSelector(cocos2d::Ref * pTarget, const char* pSelectorName)
{
    return nullptr;
}


//----------------------------------------------------
// CCBMemberVariableAssignerクラスのインターフェース
//----------------------------------------------------

/**
 * onAssignCCBMemberVariable
 */
bool CoreCCBLayer::onAssignCCBMemberVariable(cocos2d::Ref* target, const char* memberVariableName, cocos2d::Node* node)
{
    return false;
}


/**
 * CCBMemberVariableAssignerクラスのインターフェース
 * onAssignCCBCustomProperty
 */
bool CoreCCBLayer::onAssignCCBCustomProperty(cocos2d::Ref* target, const char* memberVariableName, const cocos2d::Value& value)
{
    return false;
};

//----------------------------------------------------
// CCBAnimationManagerDelegateクラスのインターフェース
//----------------------------------------------------

/**
 * completedAnimationSequenceNamed
 */
void CoreCCBLayer::completedAnimationSequenceNamed(const char *name)
{
    return;
}




//----------------------------------------------------
/**
 * このクラスのLoaderを取得
 *   サブクラスを作成時は、このgetLoader()をオーバーライドして下さい。
 */
NodeLoader* CoreCCBLayer::getLoader()
{
    return CoreCCBLayerLoader::loader();
}

/**
 * ccbiファイルからデータ読み込み
 */
Node* CoreCCBLayer::readObject(const char* ccbiName)
{
    return readObjectFromFile(ccbiName, getLoader());
}

/**
 * ccbiファイルから指定されたクラスのデータ読み込み
 */
Node* CoreCCBLayer::readObject(const char* ccbiName, const char* className)
{
    return readObjectFromFile(ccbiName, className, getLoader());
}


/**
 * ccbiファイルからデータ読み込み
 */
Node* CoreCCBLayer::readObjectFromFile(const char* ccbiName, NodeLoader* loader)
{
    // ローダーの登録
    NodeLoaderLibrary::getInstance()->registerNodeLoader(ccbiName, loader);
    
    // 読み込みファイル文字列の取得
    std::string ccbiFileName = StringUtils::format("%s.ccbi", ccbiName);
    
    // CCBReaderの取得
    CCBReader* ccbReader = new CCBReader(NodeLoaderLibrary::getInstance());
    ccbReader->autorelease();
    
    // ccbiファイルの読み込み
    Node* node = ccbReader->readNodeGraphFromFile(ccbiFileName.c_str());
    
    return node;
}

/**
 * ccbiファイルから指定されたクラスのデータ読み込み
 */
Node* CoreCCBLayer::readObjectFromFile(const char* ccbiName, const char* className, NodeLoader* loader)
{
    // ローダーの登録
    NodeLoaderLibrary::getInstance()->registerNodeLoader(className, loader);
    
    // 読み込みファイル文字列の取得
    std::string ccbiFileName = StringUtils::format("%s.ccbi", ccbiName);
    
    // CCBReaderの取得
    CCBReader* ccbReader = new CCBReader(NodeLoaderLibrary::getInstance());
    
    //Read CCBI File
    Node* node = ccbReader->readNodeGraphFromFile(ccbiFileName.c_str());
    CC_SAFE_RELEASE(ccbReader);
    
    return node;
}


// TODO cocosbuilderの名前検索は、まだ未実装なので正しくデータを取得できません。2014/6/27 Hiramatsu
/**
 * 名前から対象となるNodeを検索
 */
cocos2d::Node* CoreCCBLayer::getUIItemByName(const std::string& name, Node* startWidget, bool isRecursive)
{
    if (_layoutFormat != LayoutFormat_cocosbuilder)
    {
        return CoreLayer::getUIItemByName(name, startWidget, isRecursive);
    }

    Node*   findStartItem = startWidget;
    if (!findStartItem)
    {
        findStartItem = this;
    }
    
    if (!findStartItem)
        return nullptr;
    
    Node*  target = nullptr;
    for (auto child : findStartItem->getChildren())
    {
        Node* subNode = child;
        ValueMap* userObject = dynamic_cast<ValueMap*>(child->getUserObject());
        if (userObject)
        {
            
        }
        
        if (subNode->getDescription() == name)
        {
            target = subNode;
            break;
        }
        else
        {
            target = dynamic_cast<Node*>(getUIItemByName(name, subNode, isRecursive));
            if (target)
            {
                break;
            }
        }
    }
    return target;
}
