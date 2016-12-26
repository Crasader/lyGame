//
//  lyCCBNode.cpp
//
//  ly-Game
//
//  Created by loveyur on 2016/12/14
//  Copyright 2016 loveyur. All rights reserved.
//
//

#include "lyCCBNode.h"
#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "cocosbuilder/CCNodeLoaderLibrary.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace cocosbuilder;

/**
 * lyCCBNode Constructor
 */
lyCCBNode::lyCCBNode()
: Node()
, _animationManager(nullptr)
{
    
}

/**
 * lyCCBNode Destructor
 */
lyCCBNode::~lyCCBNode()
{
    
}

/**
 * 初期化処理
 */
bool lyCCBNode::init()
{
    if (!Node::init())
    {
        return false;
    }
    
    return true;
}

/**
 * lyCCBNode create処理
 */
lyCCBNode* lyCCBNode::create()
{
    lyCCBNode *node = new lyCCBNode();
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
cocos2d::SEL_MenuHandler lyCCBNode::onResolveCCBCCMenuItemSelector(cocos2d::Ref * pTarget, const char* pSelectorName)
{
    return nullptr;
}

/**
 * onResolveCCBCCCallFuncSelector
 */
cocos2d::SEL_CallFuncN lyCCBNode::onResolveCCBCCCallFuncSelector(cocos2d::Ref * pTarget, const char* pSelectorName)
{
    return nullptr;
}

/**
 * onResolveCCBCCControlSelector
 */
cocos2d::extension::Control::Handler lyCCBNode::onResolveCCBCCControlSelector(cocos2d::Ref * pTarget, const char* pSelectorName)
{
    return nullptr;
}


//----------------------------------------------------
// CCBMemberVariableAssignerクラスのインターフェース
//----------------------------------------------------

/**
 * onAssignCCBMemberVariable
 */
bool lyCCBNode::onAssignCCBMemberVariable(cocos2d::Ref* target, const char* memberVariableName, cocos2d::Node* node)
{
    return false;
}


/**
 * CCBMemberVariableAssignerクラスのインターフェース
 * onAssignCCBCustomProperty
 */
bool lyCCBNode::onAssignCCBCustomProperty(cocos2d::Ref* target, const char* memberVariableName, const cocos2d::Value& value)
{
    return false;
};

//----------------------------------------------------
// CCBAnimationManagerDelegateクラスのインターフェース
//----------------------------------------------------

/**
 * completedAnimationSequenceNamed
 */
void lyCCBNode::completedAnimationSequenceNamed(const char *name)
{
    return;
}



//----------------------------------------------------
/**
 * このクラスのLoaderを取得
 *   サブクラスを作成時は、このgetLoader()をオーバーライドして下さい。
 */
NodeLoader* lyCCBNode::getLoader()
{
    return lyCCBNodeLoader::loader();
}

/**
 * ccbiファイルからデータ読み込み
 */
Node* lyCCBNode::readObject(const char* ccbiName)
{
    return readObjectFromFile(ccbiName, getLoader());
}

/**
 * ccbiファイルから指定されたクラスのデータ読み込み
 */
Node* lyCCBNode::readObject(const char* ccbiName, const char* className)
{
    return readObjectFromFile(ccbiName, className, getLoader());
}


/**
 * ccbiファイルからデータ読み込み
 */
Node* lyCCBNode::readObjectFromFile(const char* ccbiName, NodeLoader* loader)
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
Node* lyCCBNode::readObjectFromFile(const char* ccbiName, const char* className, NodeLoader* loader)
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
cocos2d::Node* lyCCBNode::getUIItemByName(const std::string& name, Node* startWidget, bool isRecursive)
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

void lyCCBNode::onEnter()
{
    Node::onEnter();
    
    if (this->getUserObject() != nullptr) {
        // アニメーションマネージャー設定
        _animationManager = (cocosbuilder::CCBAnimationManager *)this->getUserObject();
        _animationManager->setDelegate(this);
    }
}

void lyCCBNode::onExit()
{
    if (_animationManager != nullptr) {
        _animationManager->setDelegate(nullptr);
        _animationManager = nullptr;
    }
    
    Node::onExit();
}

cocosbuilder::CCBAnimationManager* lyCCBNode::getAnimationManager()
{
    return _animationManager;
}
