//
//  PartsBase.h
//  client-vitamin
//
//  Created by 井戸 大拙 on 2014/06/04.
//
//
#ifndef __VitaminProject__PartsBase__
#define __VitaminProject__PartsBase__

#include "cocos2d.h"
#include "extensions/cocos-ext.h"

#include "cocosbuilder/CCBSelectorResolver.h"
#include "cocosbuilder/CCBMemberVariableAssigner.h"
#include "cocosbuilder/CCBAnimationManager.h"
#include "cocosbuilder/CCBReader.h"
#include "cocosbuilder/CCNodeLoader.h"
#include "cocosbuilder/CCNodeLoaderLibrary.h"
#include "CoreCCBNode.h"

class PartsBaseObj
{
public:
    /**
     *  コンストラクタ
     */
    PartsBaseObj():_isMovePage(false){};
    
    /**
     *  デストラクタ
     */
    virtual ~PartsBaseObj();
    
    /**
     *  オブジェクトの割当
     */
    bool onAssignCCBMemberVariable(const char* pMemberVariableName, cocos2d::Node* pNode);
    
    /**
     *  ccb内のオブジェクトを取得する関数
     */
    cocos2d::Ref* getObject(const char* name);

    template <typename T>
    T getObject(const char* name) {
        return dynamic_cast<T>(getObject(name));
    }

    template <typename T>
    T getObject(const std::string& name) {
        return dynamic_cast<T>(getObject(name.c_str()));
    }
    
    /**
     *  Lavelにテキストを設定する関数
     */
    void setText(const char* name, const std::string &text);
    
    /**
     *  Labelにテキストカラーを設定する関数
     */
    void setTextColor(const char* name, const cocos2d::Color3B& color);
    
    /**
     *  Spriteに画像を設定する関数
     */
    void setImg(const char* name, const char* fileName);
    void setImg(cocos2d::Sprite* sprite, const char* fileName);
    
    /**
     *  ボタンのテキストを設定する関数
     */
    void setBtnText(const char* name, const char* text);
    
    /**
     *  ボタンの画像を設定する関数
     */
    void setBtnimg(const char* name, const char* fileName);

    /**
     *  ボタンの有効／無効を切り替える
     */
    void setBtnEnable(const char* name, bool flg);

    /**
     *  ボタンイベントのフィルター関数を設定する
     */
    void setButtonTouchFilterFunc(const char* name, std::function<bool(cocos2d::Touch*)> func);
    
    /**
     *  レアリティ画像を設定する関数
     */
    int32_t setRarity(int32_t cardRarity);
    
    /**
    *  NodeにVisibleを設定する関数
    */
    void setNodeVisible(const char* name, bool isVisible);
    bool getNodeVisible(const char* name);
    
    /**
     *  Nodeにテキストカラーを設定する関数
     */
    void setNodeColor(const char* name, const cocos2d::Color3B& color);
    
    /**
     *  ボタンの押された時のズーム設定
     */
    void setBtnZoomOnTouchDown(const char* name, bool isZoom);
    
    /**
     *  ボタンのEnable
     */
    void setBtnEnabled(const char* name, bool isEnable);

    void setNodeOpacity(const char* name, GLbyte opacity);
    void setNodeScale(const char* name, float x, float y);
    
    /**
     *  データ取得
     */
    static const cocos2d::ValueVector& getDataVec(const cocos2d::ValueMap& valueMap, const char* key);
    static const cocos2d::ValueMap& getDataMap(const cocos2d::ValueMap& valueMap, const char* key);
    static int getDataInt(const cocos2d::ValueMap& valueMap, const char* key);
    static int64_t getDataLL(const cocos2d::ValueMap& valueMap, const char* key);
    static std::string getDataStr(const cocos2d::ValueMap& valueMap, const char* key);
    static bool getDataBool(const cocos2d::ValueMap& valueMap, const char* key);
    static float getDataFloat(const cocos2d::ValueMap& valueMap, const char* key);

    /**
     *  カンマ付きの数値にかえる
     */
    static std::string longToStringWithComma(int64_t val, bool addSymbol);
    
    /**
     *  ValueMapの中身表示
     */
    static void dispValueMap(const cocos2d::ValueMap& valueMap);
    
    /**
     *  文字列トリム
     */
    std::string trim(const std::string& s);
    
    /**
     *  文字数計算
     */
    int wlen(const char *buff);
    
    /**
     *  最大文字数に大して何文字までとれるか
     */
    unsigned int wlentobyte(const char *buff,unsigned int maxlength);
    
    /**
     *  指定位置に改行コードを挿入
     */
    std::string insertNewLine(const char *buff, int32_t index);
public:
    
    //ページ遷移中フラグ
    CC_SYNTHESIZE(bool, _isMovePage, IsMovePage);
    
    //テキストカラー
    static cocos2d::Color3B _color3BSun;
    static cocos2d::Color3B _color3BMoon;
    static cocos2d::Color3B _color3BMain;
    static cocos2d::Color3B _color3BSub;
    static cocos2d::Color3B _color3BSubBeige;
    static cocos2d::Color3B _color3BGreen;
    static cocos2d::Color3B _color3BCool;
    static cocos2d::Color3B _color3BPassion;
    static cocos2d::Color3B _color3BGentle;
    static cocos2d::Color3B _color3BCute;
    static cocos2d::Color3B _color3BSexy;
    static cocos2d::Color3B _color3BGray;
    static cocos2d::Color3B _color3BRed;
    static cocos2d::Color3B _color3BWhite;

    static cocos2d::Color3B _color3BAttention;      // 注目、警告文字色
    static cocos2d::Color3B _color3BBtnEnable;      // 無効ボタンベース色
    static cocos2d::Color3B _color3BBtnDisable;     // 有効ボタンベース色
    static cocos2d::Color3B _color3BPopupBeige;     // ポップアップ文字のうす茶色文字
    static cocos2d::Color3B _color3BPopupBrown;     // ポップアップのこげ茶文字
    static cocos2d::Color3B _color3BPopupGreen;     // ポップアップの緑文字 _color3BGreen より少し暗い
    
private:

    ///ccbの名前が設定されたオブジェクト一覧
    std::map<std::string, cocos2d::Ref*> _mapObject;
    ///返却用
    static cocos2d::ValueVector    _retVec;
    static cocos2d::ValueMap       _retMap;
};

class PartsBase
: public CoreCCBNode
, public PartsBaseObj
{
public:
    
    /**
     *  コンストラクタ
     */
    PartsBase();
    
    /**
     *  デストラクタ
     */
    virtual ~PartsBase();
    /**
     * レイアーが表示された時に呼び出される関数
     */
    virtual void onEnter();
    
    virtual void onExit();
    
    virtual void cleanup() override;
    
    ///CCBSelectorResolver
    virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector(cocos2d::Ref * pTarget, const char* pSelectorName){return nullptr;};
    virtual cocos2d::SEL_CallFuncN onResolveCCBCCCallFuncSelector(cocos2d::Ref * pTarget, const char* pSelectorName);
    virtual cocos2d::extension::Control::Handler onResolveCCBCCControlSelector(cocos2d::Ref * pTarget, const char* pSelectorName);
    
    ///CCBMemberVariableAssigner
    virtual bool onAssignCCBMemberVariable(cocos2d::Ref* target, const char* memberVariableName, cocos2d::Node* node);
    
    // タイムラインの終了を取得する
    virtual void completedAnimationSequenceNamed(const char *name);
    
    /**
     * ccbiを読み込む関数
     */
    static Node* loadUI(const char* ccbiName);
    
    /**
     *  クラス生成関数
     */
    CREATE_FUNC(PartsBase);
    
    /**
     *  ボタンイベント
     */
    virtual void btnEvent(Ref* sender, cocos2d::extension::Control::EventType eventType);
    
    // startタイムライン開始
    virtual void show(float delay = 0.0f);
    // endタイムライン開始
    virtual void hide(float delay = 0.0f);
    virtual void runAnimationsForSequenceNamed(const char* name, float delay=0.0f);
    
    //タイムライン完了コールバックの設定
    virtual void setAnimCallback(std::function<void(const char* name)>);
    
    //_animationManagerのdelegateのクリア
    void clearAnimationManagerDelegate();
    
    // AnimationManagerの取得
    virtual cocosbuilder::CCBAnimationManager* getAnimationManager();
    
    //ccbでcallBackされたときに呼ばれる関数
    void callFunc(Node* node);
    void callFunc2(Node* node);
    void callFunc3(Node* node);
    void callFunc4(Node* node);

    // ボタンが押されたことにしてコールバックを呼ぶ
    void invokeButtonEvent(const char *name);

protected:
    
    // アニメーションマネージャ
    cocosbuilder::CCBAnimationManager *_animationManager;
    
    std::function<void(const char* name)> _animCallback;

private:
    
    //ccbでcallBackされたときに呼ばれる関数を設定出来る
    CC_SYNTHESIZE(std::function<void(Node*, PartsBase*)>, _callFuncCcb,  CallFuncCcb);
    CC_SYNTHESIZE(std::function<void(Node*, PartsBase*)>, _callFuncCcb2,  CallFuncCcb2);
    CC_SYNTHESIZE(std::function<void(Node*, PartsBase*)>, _callFuncCcb3,  CallFuncCcb3);
    CC_SYNTHESIZE(std::function<void(Node*, PartsBase*)>, _callFuncCcb4,  CallFuncCcb4);
    
    //ボタンが押された場合の関数を設定出来る
    CC_SYNTHESIZE(std::function<void(PartsBase* node, Ref* sender, cocos2d::extension::Control::EventType eventType)>, _callbackOnClickBtn, CallbackOnClickBtn);
};
#endif /* defined(__VitaminProject__PartsBase__) */
