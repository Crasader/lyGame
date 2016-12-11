//
//  CoreCCBNode.cpp
//
//  Created by loveyur on 2016/12/11.
//  Copyright 2016 loveyur All rights reserved.
//
//

#include "CoreCCBNode.h"
#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "cocosbuilder/CCNodeLoaderLibrary.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace cocosbuilder;

/**
 * CoreCCBNode Constructor
 */
CoreCCBNode::CoreCCBNode()
: Node()
, _animationManager(nullptr)
{
    
}

/**
 * CoreCCBNode Destructor
 */
CoreCCBNode::~CoreCCBNode()
{
    
}

/**
 * 初期化処理
 */
bool CoreCCBNode::init()
{
    if (!Node::init())
    {
        return false;
    }
    
    return true;
}

/**
 * CoreCCBNode create処理
 */
CoreCCBNode* CoreCCBNode::create()
{
    CoreCCBNode *node = new CoreCCBNode();
    if (node && node->init())
    {
        node->autorelease();
        return node;
    }
    CC_SAFE_DELETE(node);
    return nullptr;
}


//----------------------------------------------------
// CCBSelectorResolverクラスのインターフェース
//----------------------------------------------------

/**
 * onResolveCCBCCMenuItemSelector
 */
cocos2d::SEL_MenuHandler CoreCCBNode::onResolveCCBCCMenuItemSelector(cocos2d::Ref * pTarget, const char* pSelectorName)
{
    return nullptr;
}

/**
 * onResolveCCBCCCallFuncSelector
 */
cocos2d::SEL_CallFuncN CoreCCBNode::onResolveCCBCCCallFuncSelector(cocos2d::Ref * pTarget, const char* pSelectorName)
{
    return nullptr;
}

/**
 * onResolveCCBCCControlSelector
 */
cocos2d::extension::Control::Handler CoreCCBNode::onResolveCCBCCControlSelector(cocos2d::Ref * pTarget, const char* pSelectorName)
{
    return nullptr;
}


//----------------------------------------------------
// CCBMemberVariableAssignerクラスのインターフェース
//----------------------------------------------------

/**
 * onAssignCCBMemberVariable
 */
bool CoreCCBNode::onAssignCCBMemberVariable(cocos2d::Ref* target, const char* memberVariableName, cocos2d::Node* node)
{
    return false;
}


/**
 * CCBMemberVariableAssignerクラスのインターフェース
 * onAssignCCBCustomProperty
 */
bool CoreCCBNode::onAssignCCBCustomProperty(cocos2d::Ref* target, const char* memberVariableName, const cocos2d::Value& value)
{
    return false;
};

//----------------------------------------------------
// CCBAnimationManagerDelegateクラスのインターフェース
//----------------------------------------------------

/**
 * completedAnimationSequenceNamed
 */
void CoreCCBNode::completedAnimationSequenceNamed(const char *name)
{
    return;
}



//----------------------------------------------------
/**
 * このクラスのLoaderを取得
 *   サブクラスを作成時は、このgetLoader()をオーバーライドして下さい。
 */
NodeLoader* CoreCCBNode::getLoader()
{
    return CoreCCBNodeLoader::loader();
}

/**
 * ccbiファイルからデータ読み込み
 */
Node* CoreCCBNode::readObject(const char* ccbiName)
{
    return readObjectFromFile(ccbiName, getLoader());
}

/**
 * ccbiファイルから指定されたクラスのデータ読み込み
 */
Node* CoreCCBNode::readObject(const char* ccbiName, const char* className)
{
    return readObjectFromFile(ccbiName, className, getLoader());
}


/**
 * ccbiファイルからデータ読み込み
 */
Node* CoreCCBNode::readObjectFromFile(const char* ccbiName, NodeLoader* loader)
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
Node* CoreCCBNode::readObjectFromFile(const char* ccbiName, const char* className, NodeLoader* loader)
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

//----------------------------------------------------

/**
 * 名前から対象となるNodeを検索
 */
cocos2d::Node* CoreCCBNode::getUIItemByName(const std::string& name, Node* startWidget, bool isRecursive)
{
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

void CoreCCBNode::onEnter()
{
    Node::onEnter();
    
    if (this->getUserObject() != nullptr) {
        // アニメーションマネージャー設定
        _animationManager = (cocosbuilder::CCBAnimationManager *)this->getUserObject();
        _animationManager->setDelegate(this);
    }
}

void CoreCCBNode::onExit()
{
    if (_animationManager != nullptr) {
        _animationManager->setDelegate(nullptr);
        _animationManager = nullptr;
    }
    
    Node::onExit();
}

cocosbuilder::CCBAnimationManager* CoreCCBNode::getAnimationManager()
{
    return _animationManager;
}
