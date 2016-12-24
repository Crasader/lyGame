//
//  CoreCCBSprite.cpp
//
//  ly-Game
//
//  Created by loveyur on 2016/12/14
//  Copyright 2016 loveyur. All rights reserved.
//
//

#include "CoreCCBSprite.h"
#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "cocosbuilder/CCNodeLoaderLibrary.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace cocosbuilder;

/**
 * CoreCCBSprite Constructor
 */
CoreCCBSprite::CoreCCBSprite()    :
    Sprite()
{
    
}

/**
 * CoreCCBSprite Destructor
 */
CoreCCBSprite::~CoreCCBSprite()
{
    
}

/**
 * 初期化処理
 */
bool CoreCCBSprite::init()
{
    if (!Node::init())
    {
        return false;
    }
    
    return true;
}

/**
 * CoreCCBSprite create処理
 */
CoreCCBSprite* CoreCCBSprite::create()
{
    CoreCCBSprite *node = new CoreCCBSprite();
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
cocos2d::SEL_MenuHandler CoreCCBSprite::onResolveCCBCCMenuItemSelector(cocos2d::Ref * pTarget, const char* pSelectorName)
{
    return nullptr;
}

/**
 * onResolveCCBCCCallFuncSelector
 */
cocos2d::SEL_CallFuncN CoreCCBSprite::onResolveCCBCCCallFuncSelector(cocos2d::Ref * pTarget, const char* pSelectorName)
{
    return nullptr;
}

/**
 * onResolveCCBCCControlSelector
 */
cocos2d::extension::Control::Handler CoreCCBSprite::onResolveCCBCCControlSelector(cocos2d::Ref * pTarget, const char* pSelectorName)
{
    return nullptr;
}


//----------------------------------------------------
// CCBMemberVariableAssignerクラスのインターフェース
//----------------------------------------------------

/**
 * onAssignCCBMemberVariable
 */
bool CoreCCBSprite::onAssignCCBMemberVariable(cocos2d::Ref* target, const char* memberVariableName, cocos2d::Node* node)
{
    return false;
}


/**
 * CCBMemberVariableAssignerクラスのインターフェース
 * onAssignCCBCustomProperty
 */
bool CoreCCBSprite::onAssignCCBCustomProperty(cocos2d::Ref* target, const char* memberVariableName, const cocos2d::Value& value)
{
    return false;
};

//----------------------------------------------------
// CCBAnimationManagerDelegateクラスのインターフェース
//----------------------------------------------------

/**
 * completedAnimationSequenceNamed
 */
void CoreCCBSprite::completedAnimationSequenceNamed(const char *name)
{
    return;
}



//----------------------------------------------------
/**
 * このクラスのLoaderを取得
 *   サブクラスを作成時は、このgetLoader()をオーバーライドして下さい。
 */
NodeLoader* CoreCCBSprite::getLoader()
{
    return CoreCCBSpriteLoader::loader();
}

/**
 * ccbiファイルからデータ読み込み
 */
Node* CoreCCBSprite::readObject(const char* ccbiName)
{
    return readObjectFromFile(ccbiName, getLoader());
}

/**
 * ccbiファイルから指定されたクラスのデータ読み込み
 */
Node* CoreCCBSprite::readObject(const char* ccbiName, const char* className)
{
    return readObjectFromFile(ccbiName, className, getLoader());
}


/**
 * ccbiファイルからデータ読み込み
 */
Node* CoreCCBSprite::readObjectFromFile(const char* ccbiName, NodeLoader* loader)
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
Node* CoreCCBSprite::readObjectFromFile(const char* ccbiName, const char* className, NodeLoader* loader)
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

