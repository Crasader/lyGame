//
//  lyCCBSprite.cpp
//
//  ly-Game
//
//  Created by loveyur on 2016/12/14
//  Copyright 2016 loveyur. All rights reserved.
//
//

#include "lyCCBSprite.h"
#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "cocosbuilder/CCNodeLoaderLibrary.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace cocosbuilder;

/**
 * lyCCBSprite Constructor
 */
lyCCBSprite::lyCCBSprite()    :
    Sprite()
{
    
}

/**
 * lyCCBSprite Destructor
 */
lyCCBSprite::~lyCCBSprite()
{
    
}

/**
 * 初期化処理
 */
bool lyCCBSprite::init()
{
    if (!Node::init())
    {
        return false;
    }
    
    return true;
}

/**
 * lyCCBSprite create処理
 */
lyCCBSprite* lyCCBSprite::create()
{
    lyCCBSprite *node = new lyCCBSprite();
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
cocos2d::SEL_MenuHandler lyCCBSprite::onResolveCCBCCMenuItemSelector(cocos2d::Ref * pTarget, const char* pSelectorName)
{
    return nullptr;
}

/**
 * onResolveCCBCCCallFuncSelector
 */
cocos2d::SEL_CallFuncN lyCCBSprite::onResolveCCBCCCallFuncSelector(cocos2d::Ref * pTarget, const char* pSelectorName)
{
    return nullptr;
}

/**
 * onResolveCCBCCControlSelector
 */
cocos2d::extension::Control::Handler lyCCBSprite::onResolveCCBCCControlSelector(cocos2d::Ref * pTarget, const char* pSelectorName)
{
    return nullptr;
}


//----------------------------------------------------
// CCBMemberVariableAssignerクラスのインターフェース
//----------------------------------------------------

/**
 * onAssignCCBMemberVariable
 */
bool lyCCBSprite::onAssignCCBMemberVariable(cocos2d::Ref* target, const char* memberVariableName, cocos2d::Node* node)
{
    return false;
}


/**
 * CCBMemberVariableAssignerクラスのインターフェース
 * onAssignCCBCustomProperty
 */
bool lyCCBSprite::onAssignCCBCustomProperty(cocos2d::Ref* target, const char* memberVariableName, const cocos2d::Value& value)
{
    return false;
};

//----------------------------------------------------
// CCBAnimationManagerDelegateクラスのインターフェース
//----------------------------------------------------

/**
 * completedAnimationSequenceNamed
 */
void lyCCBSprite::completedAnimationSequenceNamed(const char *name)
{
    return;
}



//----------------------------------------------------
/**
 * このクラスのLoaderを取得
 *   サブクラスを作成時は、このgetLoader()をオーバーライドして下さい。
 */
NodeLoader* lyCCBSprite::getLoader()
{
    return lyCCBSpriteLoader::loader();
}

/**
 * ccbiファイルからデータ読み込み
 */
Node* lyCCBSprite::readObject(const char* ccbiName)
{
    return readObjectFromFile(ccbiName, getLoader());
}

/**
 * ccbiファイルから指定されたクラスのデータ読み込み
 */
Node* lyCCBSprite::readObject(const char* ccbiName, const char* className)
{
    return readObjectFromFile(ccbiName, className, getLoader());
}


/**
 * ccbiファイルからデータ読み込み
 */
Node* lyCCBSprite::readObjectFromFile(const char* ccbiName, NodeLoader* loader)
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
Node* lyCCBSprite::readObjectFromFile(const char* ccbiName, const char* className, NodeLoader* loader)
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

