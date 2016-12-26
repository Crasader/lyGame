//
//  PartsBase.cpp
//
//  ly-Game
//
//  Created by loveyur on 2016/11/11
//  Copyright 2016 loveyur. All rights reserved.
//
//

#include "PartsBase.h"
#include "cocosbuilder/CCBMemberVariableAssigner.h"
//#include "CardDaoEnum.h"
//#include "VitaminImageID.h"
#include "lyJsonConverter.h"
//#include "PlatformUtils.h"

USING_NS_CC;
using namespace cocosbuilder;

//テキストカラー
cocos2d::Color3B PartsBaseObj::_color3BSun          = cocos2d::Color3B(233,159, 16);
cocos2d::Color3B PartsBaseObj::_color3BMoon         = cocos2d::Color3B(163, 99,238);
cocos2d::Color3B PartsBaseObj::_color3BMain         = cocos2d::Color3B( 64, 38,  0);
cocos2d::Color3B PartsBaseObj::_color3BSub          = cocos2d::Color3B(255,255,255);
cocos2d::Color3B PartsBaseObj::_color3BSubBeige     = cocos2d::Color3B(180,129, 66);
cocos2d::Color3B PartsBaseObj::_color3BGreen        = cocos2d::Color3B( 21,227,116);
cocos2d::Color3B PartsBaseObj::_color3BCool         = cocos2d::Color3B( 64, 94,175);
cocos2d::Color3B PartsBaseObj::_color3BPassion      = cocos2d::Color3B(193, 14,  1);
cocos2d::Color3B PartsBaseObj::_color3BGentle       = cocos2d::Color3B( 68,153, 85);
cocos2d::Color3B PartsBaseObj::_color3BCute         = cocos2d::Color3B(228,119, 12);
cocos2d::Color3B PartsBaseObj::_color3BSexy         = cocos2d::Color3B(224,126,232);
cocos2d::Color3B PartsBaseObj::_color3BGray         = cocos2d::Color3B(128,128,128);
cocos2d::Color3B PartsBaseObj::_color3BRed          = cocos2d::Color3B(255,209, 47);
cocos2d::Color3B PartsBaseObj::_color3BWhite        = cocos2d::Color3B(255,255,255);
cocos2d::Color3B PartsBaseObj::_color3BAttention    = cocos2d::Color3B(244, 71, 62);
cocos2d::Color3B PartsBaseObj::_color3BBtnEnable    = cocos2d::Color3B(255,255,255);
cocos2d::Color3B PartsBaseObj::_color3BBtnDisable   = cocos2d::Color3B(102,102,102);
cocos2d::Color3B PartsBaseObj::_color3BPopupBeige   = cocos2d::Color3B(180,129, 66);
cocos2d::Color3B PartsBaseObj::_color3BPopupBrown   = cocos2d::Color3B(102, 51,  0);
cocos2d::Color3B PartsBaseObj::_color3BPopupGreen   = cocos2d::Color3B( 10,184,116);


//static関数返却用
cocos2d::ValueVector    PartsBaseObj::_retVec;
cocos2d::ValueMap       PartsBaseObj::_retMap;

/**
 *  コンストラクタ
 */
PartsBase::PartsBase():
_animationManager(nullptr),
_callFuncCcb(nullptr),
_callFuncCcb2(nullptr),
_callFuncCcb3(nullptr),
_callFuncCcb4(nullptr),
_callbackOnClickBtn(nullptr)
{
}

/**
 *  デストラクタ
 */
PartsBase::~PartsBase()
{
    stopAllActions();
    clearAnimationManagerDelegate();
}

/**
 * ccbiを読み込む関数
 */
Node* PartsBase::loadUI(const char* ccbiName)
{
    //CCLOG("ccbfile:%s",ccbiName);
    cocosbuilder::CCBReader * ccbReader = new cocosbuilder::CCBReader(cocosbuilder::NodeLoaderLibrary::getInstance());
    Node* node = ccbReader->readNodeGraphFromFile(ccbiName);
    CC_SAFE_DELETE(ccbReader);
    return node;
}

/**
 * レイアーが表示された時に呼び出される関数
 */
void PartsBase::onEnter()
{
    Node::onEnter();
}

void PartsBase::onExit()
{
    clearAnimationManagerDelegate();
    Node::onExit();
}

void PartsBase::cleanup()
{
    clearAnimationManagerDelegate();
    lyCCBNode::cleanup();
}

//_animationManagerのdelegateのクリア
void PartsBase::clearAnimationManagerDelegate()
{
    if(_animationManager && _animationManager->getDelegate())
    {
        _animationManager->setDelegate(nullptr);
    }
}

///CCBMemberVariableAssigner
bool PartsBase::onAssignCCBMemberVariable(cocos2d::Ref* pTarget, const char* pMemberVariableName, cocos2d::Node* pNode)
{
    return PartsBaseObj::onAssignCCBMemberVariable(pMemberVariableName, pNode);
}

cocos2d::extension::Control::Handler PartsBase::onResolveCCBCCControlSelector(cocos2d::Ref * pTarget, const char* pSelectorName)
{
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "btnEvent:",  PartsBase::btnEvent);
    return nullptr;
}

/**
 *  ボタンイベント
 */
void PartsBase::btnEvent(Ref* sender, cocos2d::extension::Control::EventType eventType)
{
    if(_callbackOnClickBtn)
    {
        _callbackOnClickBtn(this,sender,eventType);
    }
}

// タイムライン終了
void PartsBase::completedAnimationSequenceNamed(const char *name)
{
    if (_animCallback != nullptr)
    {
        _animCallback(name);
    }
}

void PartsBase::show(float delay)
{
    runAction(Sequence::create(DelayTime::create(delay),CallFunc::create([this](){
        getAnimationManager()->runAnimationsForSequenceNamed("start");
        this->setVisible(true);
    }), nullptr));
}

void PartsBase::hide(float delay)
{
    runAction(Sequence::create(DelayTime::create(delay),CallFunc::create([this](){
        getAnimationManager()->runAnimationsForSequenceNamed("end");
    }), nullptr));
}

void PartsBase::runAnimationsForSequenceNamed(const char* name, float delay)
{
    if (delay > 0.f)
    {
        runAction(Sequence::create(DelayTime::create(delay),CallFunc::create([this, name](){
            getAnimationManager()->runAnimationsForSequenceNamed(name);
        }), nullptr));
    }
    else
    {
        getAnimationManager()->runAnimationsForSequenceNamed(name);
    }
}

// AnimationManagerの取得
cocosbuilder::CCBAnimationManager* PartsBase::getAnimationManager()
{
    if (_animationManager == nullptr)
    {
        if (this->getUserObject() != nullptr)
        {
            // アニメーションマネージャー設定
            _animationManager = (cocosbuilder::CCBAnimationManager *)this->getUserObject();
            _animationManager->setDelegate(this);
        }
    }
    return _animationManager;
}

//タイムライン完了コールバックの設定
void PartsBase::setAnimCallback(std::function<void(const char* name)> carllback)
{
    _animCallback = carllback;
}

/**
 * onResolveCCBCCCallFuncSelector
 */
cocos2d::SEL_CallFuncN PartsBase::onResolveCCBCCCallFuncSelector(cocos2d::Ref * pTarget, const char* pSelectorName)
{
    CCB_SELECTORRESOLVER_CALLFUNC_GLUE(this, "callFunc", PartsBase::callFunc);
    CCB_SELECTORRESOLVER_CALLFUNC_GLUE(this, "callFunc2", PartsBase::callFunc2);
    CCB_SELECTORRESOLVER_CALLFUNC_GLUE(this, "callFunc3", PartsBase::callFunc3);
    CCB_SELECTORRESOLVER_CALLFUNC_GLUE(this, "callFunc4", PartsBase::callFunc4);
    return nullptr;
}

//ccbでcallBackされたときに呼ばれる関数
void PartsBase::callFunc(Node* node)
{
    if(_callFuncCcb)
    {
        _callFuncCcb(node,this);
    }
}

//ccbでcallBackされたときに呼ばれる関数
void PartsBase::callFunc2(Node* node)
{
    if(_callFuncCcb2)
    {
        _callFuncCcb2(node,this);
    }
}
void PartsBase::callFunc3(Node* node)
{
    if(_callFuncCcb3) {
        _callFuncCcb3(node, this);
    }
}
void PartsBase::callFunc4(Node* node)
{
    if(_callFuncCcb4) {
        _callFuncCcb4(node, this);
    }
}

/**
 *  ccb内のオブジェクトを取得する関数
 */
Ref* PartsBaseObj::getObject(const char* name)
{
    if(_mapObject.size() && _mapObject[name])
    {
        return _mapObject[name];
    }
    
    return nullptr;
}

/**
 *  Lavelにテキストを設定する関数
 */
void PartsBaseObj::setText(const char* name, const std::string &text)
{
    if(dynamic_cast<cocos2d::Label*>(getObject(name)))
    {
        cocos2d::Label* label = dynamic_cast<cocos2d::Label*>(getObject(name));
        label->setString(text);
    }
    else if(dynamic_cast<cocos2d::LabelBMFont*>(getObject(name)))
    {
        cocos2d::LabelBMFont* label = dynamic_cast<cocos2d::LabelBMFont*>(getObject(name));
        label->setString(text);
    }
    else
    {
        CCLOG("setText:name:%sが無い",name);
    }
}

/**
 *  Lavelにテキストカラーを設定する関数
 */
void PartsBaseObj::setTextColor(const char* name, const cocos2d::Color3B& color)
{
    if(dynamic_cast<cocos2d::Label*>(getObject(name)))
    {
        cocos2d::Label* label = dynamic_cast<cocos2d::Label*>(getObject(name));
        label->setColor(color);
    }
    else if(dynamic_cast<cocos2d::LabelBMFont*>(getObject(name)))
    {
        cocos2d::LabelBMFont* label = dynamic_cast<cocos2d::LabelBMFont*>(getObject(name));
        label->setColor(color);
    }
    else
    {
        CCLOG("setText:name:%sが無い",name);
    }
}

/**
 *  Spriteに画像を設定する関数
 */
void PartsBaseObj::setImg(const char* name, const char* fileName)
{
    if(dynamic_cast<cocos2d::Sprite*>(getObject(name)))
    {
        cocos2d::Sprite* sprite = dynamic_cast<cocos2d::Sprite*>(getObject(name));
        setImg(sprite,fileName);
    }
    else
    {
        CCLOG("setImg:name:%sが無い",name);
    }
}

void PartsBaseObj::setImg(cocos2d::Sprite* sprite, const char* fileName)
{
    if(!sprite || !fileName)
    {
        return;
    }
    
    Texture2D *texture = Director::getInstance()->getTextureCache()->addImage(fileName);
    if (texture)
    {
        sprite->setTexture(fileName);
    }
    else
    {
        CCLOG("setImg:fileName:%sが無い",fileName);
    }
}

/**
 *  ボタンのテキストを設定する関数
 */
void PartsBaseObj::setBtnText(const char* name, const char* text)
{
    cocos2d::extension::ControlButton* controlButton = dynamic_cast<cocos2d::extension::ControlButton*>(getObject(name));
    if(controlButton)
    {
        controlButton->setTitleForState(text,cocos2d::extension::ControlButton::State::NORMAL);
        controlButton->setTitleForState(text,cocos2d::extension::ControlButton::State::HIGH_LIGHTED);
        controlButton->setTitleForState(text,cocos2d::extension::ControlButton::State::DISABLED);
        controlButton->setTitleForState(text,cocos2d::extension::ControlButton::State::SELECTED);
    }
    else
    {
        CCLOG("setBtnText:name:%sが無い",name);
    }
}

/**
 *  ボタンの画像を設定する関数
 */
void PartsBaseObj::setBtnimg(const char* name, const char* fileName)
{
    cocos2d::extension::ControlButton* controlButton = dynamic_cast<cocos2d::extension::ControlButton*>(getObject(name));
    if(controlButton)
    {
        Texture2D *texture = Director::getInstance()->getTextureCache()->addImage(fileName);
        if (texture)
        {
            controlButton->setBackgroundSpriteForState(cocos2d::extension::Scale9Sprite::create(fileName),cocos2d::extension::ControlButton::State::NORMAL);
            controlButton->setBackgroundSpriteForState(cocos2d::extension::Scale9Sprite::create(fileName),cocos2d::extension::ControlButton::State::HIGH_LIGHTED);
            controlButton->setBackgroundSpriteForState(cocos2d::extension::Scale9Sprite::create(fileName),cocos2d::extension::ControlButton::State::DISABLED);
            controlButton->setBackgroundSpriteForState(cocos2d::extension::Scale9Sprite::create(fileName),cocos2d::extension::ControlButton::State::SELECTED);
        }
        else
        {
            CCLOG("setImg:fileName:%sが無い",fileName);
        }
    }
    else
    {
        CCLOG("setBtnText:name:%sが無い",name);
    }
}

/**
 *  ボタンの有効／無効を切り替える
 */
void PartsBaseObj::setBtnEnable(const char* name, bool flg)
{
    auto controlButton = getObject<cocos2d::extension::ControlButton*>(name);
    if(controlButton)
    {
        controlButton->setEnabled(flg);
    }
}

void PartsBaseObj::setButtonTouchFilterFunc(const char* name, std::function<bool(Touch*)> func)
{
    auto controlButton = getObject<cocos2d::extension::ControlButton*>(name);
    if(controlButton)
    {
        //controlButton->setTouchFilterFunc(func);
    }
}

/**
 *  レアリティ画像を設定する関数
 */
int32_t PartsBaseObj::setRarity(int32_t cardRarity)
{
    int32_t rarity = 0;
    return rarity;
}

/**
 *  Visibleを設定する関数
 */
void PartsBaseObj::setNodeVisible(const char* name, bool isVisible)
{
    if(dynamic_cast<cocos2d::Node*>(getObject(name)))
    {
        dynamic_cast<cocos2d::Node*>(getObject(name))->setVisible(isVisible);
    }
    else
    {
        CCLOG("setNodeVisible:name:%sが無い",name);
    }
}
bool PartsBaseObj::getNodeVisible(const char* name)
{
    if(dynamic_cast<cocos2d::Node*>(getObject(name)))
    {
        return dynamic_cast<cocos2d::Node*>(getObject(name))->isVisible();
    }
    else
    {
        CCLOG("getNodeVisible:name:%sが無い",name);
    }
    return false;
}

/**
 *  Nodeにテキストカラーを設定する関数
 */
void PartsBaseObj::setNodeColor(const char* name, const cocos2d::Color3B& color)
{
    if(dynamic_cast<cocos2d::Node*>(getObject(name)))
    {
        dynamic_cast<cocos2d::Node*>(getObject(name))->setColor(color);
    }
    else
    {
        CCLOG("setNodeColor:name:%sが無い",name);
    }
}

void PartsBaseObj::setNodeOpacity(const char* name, GLbyte opacity)
{
    auto node = getObject<cocos2d::Node*>(name);
    if (node)
    {
        node->setOpacity(opacity);
    }
    else
    {
        CCLOG("setNodeColor:name:%sが無い",name);
    }
}

void PartsBaseObj::setNodeScale(const char* name, float x, float y)
{
    auto node = getObject<cocos2d::Node*>(name);
    if (node)
    {
        node->setScale(x, y);
    }
    else
    {
        CCLOG("setNodeColor:name:%sが無い",name);
    }
}

/**
 *  ボタンの押された時のズーム設定
 */
void PartsBaseObj::setBtnZoomOnTouchDown(const char* name, bool isZoom)
{
    cocos2d::extension::ControlButton* button = dynamic_cast<cocos2d::extension::ControlButton*>(getObject(name));
    if(button)
    {
        //ボタンがクリックされたときに大きくならない様に設定
        button->setZoomOnTouchDown(isZoom);
    }
    else
    {
        CCLOG("setZoomOnTouchDown:name:%sが無い",name);
    }
}

/**
 *  ボタンのEnable
 */
void PartsBaseObj::setBtnEnabled(const char* name, bool isEnable)
{
    cocos2d::extension::ControlButton* button = dynamic_cast<cocos2d::extension::ControlButton*>(getObject(name));
    if(button)
    {
        button->setEnabled(isEnable);
    }
    else
    {
        CCLOG("setBtnEnabled:name:%sが無い",name);
    }
}

/**
 *  データ取得
 */
const cocos2d::ValueVector& PartsBaseObj::getDataVec(const cocos2d::ValueMap& valueMap, const char* key)
{
    if(valueMap.find(key) != valueMap.end())
    {
        return valueMap.at(key).asValueVector();
    }
    else
    {
        CCLOG("getDataVec:key:%sが無い",key);
    }
    
    return _retVec;
}
const cocos2d::ValueMap& PartsBaseObj::getDataMap(const cocos2d::ValueMap& valueMap, const char* key)
{
    if(valueMap.find(key) != valueMap.end())
    {
        return valueMap.at(key).asValueMap();
    }
    else
    {
        CCLOG("getDataMap:key:%sが無い",key);
    }
    
    return _retMap;
}
int PartsBaseObj::getDataInt(const cocos2d::ValueMap& valueMap, const char* key)
{
    if(valueMap.find(key) != valueMap.end())
    {
        return valueMap.at(key).asInt();
    }
    else
    {
        CCLOG("getDataInt:key:%sが無い",key);
    }
    
    int ret = 0;
    return ret;
}

int64_t PartsBaseObj::getDataLL(const cocos2d::ValueMap& valueMap, const char* key)
{
    if(valueMap.find(key) != valueMap.end())
    {
        return atoll(valueMap.at(key).asString().c_str());
    }
    else
    {
        CCLOG("getDataInt:key:%sが無い",key);
    }
    
    int64_t ret = 0;
    return ret;
}

std::string PartsBaseObj::getDataStr(const cocos2d::ValueMap& valueMap, const char* key)
{
    if(valueMap.find(key) != valueMap.end())
    {
        return valueMap.at(key).asString();
    }
    else
    {
        CCLOG("getDataStr:key:%sが無い",key);
    }
    
    std::string ret;
    return ret;
}

bool PartsBaseObj::getDataBool(const cocos2d::ValueMap& valueMap, const char* key)
{
    if(valueMap.find(key) != valueMap.end())
    {
        return valueMap.at(key).asBool();
    }
    else
    {
        CCLOG("getDataBool:key:%sが無い",key);
    }
    
    bool ret = false;
    return ret;
}

float PartsBaseObj::getDataFloat(const cocos2d::ValueMap& valueMap, const char* key)
{
    if(valueMap.find(key) != valueMap.end())
    {
        return valueMap.at(key).asFloat();
    }
    else
    {
        CCLOG("getDataBool:key:%sが無い",key);
    }
    
    return 0;
}

/**
 *  デストラクタ
 */
PartsBaseObj::~PartsBaseObj()
{
    for (auto data : _mapObject)
    {
        Ref* ref = data.second;
        CC_SAFE_RELEASE(ref);
    }
    _mapObject.clear();
}

/**
 *  オブジェクトの割当
 */
bool PartsBaseObj::onAssignCCBMemberVariable(const char* pMemberVariableName, cocos2d::Node* pNode)
{
    //初期化
    if(strlen(pMemberVariableName)){
        //同じ名前のものが既にある場合は警告する
        if(_mapObject.size() && _mapObject[pMemberVariableName]){
            CCLOG("**********************");
            CCLOG("**********************");
            CCLOG("同じ名前のオブジェクトが定義されています。");
            CCLOG("%s", pMemberVariableName);
            CCLOG("**********************");
            CCLOG("**********************");
        } else {
            Ref* ref = nullptr;
            Ref* pOldVar = ref;
            ref = dynamic_cast<Ref*>(pNode);
            CC_ASSERT(ref);
            if (pOldVar != ref) {
                CC_SAFE_RELEASE(pOldVar);
                ref->retain();
            }
            //名前で検索出来るように名前設定
            Node* node = dynamic_cast<Node*>(ref);
            if(node)
            {
                node->setName(pMemberVariableName);
            }
            
            //設定されたものを保存する
            _mapObject[pMemberVariableName] = ref;
            return true;
        }
    }
    return false;
}

/**
 *  カンマ付きの数値にかえる
 */
std::string PartsBaseObj::longToStringWithComma(int64_t val, bool addSymbol)
{
    if(!val){
        return "0";
    }
    int64_t l = val;
    std::string s = "";
    int d = 0;
    int n;
    bool bMinus = false;
    if(l<0){
        l *= -1;
        bMinus = true;
    }
    do {
        // 3桁毎をチェックしてカンマ挿入
        if (d == 3) {
            s = ',' + s;
            d = 0;
        }
        d ++;
        
        // 　下一桁をバッファの先頭に追加
        n = l%10;
        s = char('0'+(n)) + s;
        
        // 　数値を1桁シフト(下一桁を取り除く)
        l /= 10;
    } while (l > 0);
    
    if(addSymbol){
        //マイナスの場合は戦闘に-をつける
        if(bMinus){
            s = "-" + s;
        } else {
            s = "+" + s;
        }
    }
    
    return s;
}

/**
 *  ValueMapの中身表示
 */
void PartsBaseObj::dispValueMap(const cocos2d::ValueMap& valueMap)
{
#if COCOS2D_DEBUG >= 1
    char* str = lyJsonConverter::getInstance()->strFrom(valueMap);
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
    __android_log_print(ANDROID_LOG_DEBUG, "cocos2d-x debug info",  "%s", str);
#else
    printf("%s\n", str);
#endif
    free(str); // @TODO cJson_free で解放したほうが安全
#endif
}


/**
 *  文字列トリム
 */
std::string PartsBaseObj::trim(const std::string& s)
{
    std::string::const_iterator         left  = std::find_if(s.begin(), s.end(), std::not1(std::ptr_fun<int, int>(std::isspace)));
    std::string::const_reverse_iterator right = std::find_if(s.rbegin(), s.rend(), std::not1(std::ptr_fun<int, int>(std::isspace)));
    return (left < right.base()) ? std::string(left, right.base()) : std::string();
}

/**
 *  指定位置に改行コードを挿入
 */
std::string PartsBaseObj::insertNewLine(const char *buff, int32_t index)
{
    if( buff == NULL ) return 0;
    
    std::string ret = "";
    
    int count           = 0;
    int pos             = 0;
    int targetPos       = 0;
    size_t max_bytes    = strlen( buff );
    
    if( max_bytes >= 3 )
    {
        if( static_cast<unsigned char>( buff[0] ) == 0xEF &&
           static_cast<unsigned char>( buff[1] ) == 0xBB &&
           static_cast<unsigned char>( buff[2] ) == 0xBF )
        {
            pos += 3;
        }
    }
    
    while( pos < max_bytes )
    {
        ++count;
        
        if( ( buff[pos] & 0x80 ) == 0 )
        {
            ++pos;
        }
        else
        {
            for( char tmp = buff[pos] & 0xfc; (tmp & 0x80); tmp = tmp << 1 )
            {
                ++pos;
            }
        }
        
        if(count == index)
        {
            targetPos = pos;
            break;
        }
    }
    
    if(targetPos)
    {
        for(int i=0; i<max_bytes; i++)
        {
            if(i==targetPos)
            {
                ret += "\n";
            }
            ret += buff[i];
        }
    }
    else
    {
        ret = buff;
    }
    
    
    return ret;
}

/**
 *  文字数計算
 */
int PartsBaseObj::wlen(const char *buff)
{
    if( buff == NULL ) return 0;
    
    int count           = 0;
    int pos             = 0;
    size_t max_bytes    = strlen( buff );
    
    if( max_bytes >= 3 )
    {
        if( static_cast<unsigned char>( buff[0] ) == 0xEF &&
           static_cast<unsigned char>( buff[1] ) == 0xBB &&
           static_cast<unsigned char>( buff[2] ) == 0xBF )
        {
            pos += 3;
        }
    }
    
    while( pos < max_bytes )
    {
        ++count;
        
        if( ( buff[pos] & 0x80 ) == 0 )
        {
            ++pos;
        }
        else
        {
            for( char tmp = buff[pos] & 0xfc; (tmp & 0x80); tmp = tmp << 1 )
            {
                ++pos;
            }
        }
    }
    
    return count;
}

/**
 *  最大文字数に大して何文字までとれるか
 */
unsigned int PartsBaseObj::wlentobyte(const char *buff,unsigned int maxlength)
{
    if( buff == NULL ) return 0;
    
    int count = 0;
    int pos = 0;
    int max_bytes = strlen( buff );
    
    if( max_bytes >= 3 )
    {
        if( static_cast<unsigned char>( buff[0] ) == 0xEF &&
           static_cast<unsigned char>( buff[1] ) == 0xBB &&
           static_cast<unsigned char>( buff[2] ) == 0xBF )
        {
            pos += 3;
        }
    }
    
    while( pos < max_bytes )
    {
        ++count;
        
        if( ( buff[pos] & 0x80 ) == 0 )
        {
            ++pos;
        }
        else
        {
            for( char tmp = buff[pos] & 0xfc; (tmp & 0x80); tmp = tmp << 1 )
            {
                ++pos;
            }
        }
        
        if(maxlength == count){
            break;
        }
    }
    
    return pos;
}

void PartsBase::invokeButtonEvent(const char *name)
{
    auto sender = getObject(name);
    if (sender)
    {
        btnEvent(sender, cocos2d::extension::Control::EventType::TOUCH_UP_INSIDE);
    }
    else
    {
        CCLOG("invokeCallbackOnClickButton:name:%sが無い",name);
    }
}

