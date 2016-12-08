/**
 
 @file Caption.h
 
 @brief TODO: 概要を書いてください
 
 @author 横山 充
 @date 2014/07/01
 
 */

#ifndef __VitaminProject__Caption__
#define __VitaminProject__Caption__

#include "CoreLayer.h"
#include "cocos2d.h"
#include "editor-support/spritebuilder/SpriteBuilder.h"

class Caption;

class CaptionDelegate
{
public:
	virtual ~CaptionDelegate() {};
    virtual void pressedBack(Caption *sender) = 0;
    virtual void notifyCaptionStartComplete(Caption *sender) = 0;
    virtual void notifyCaptionEndComplete(Caption *sender) = 0;
};

class Caption
: public CoreLayer
, public spritebuilder::CCBSelectorResolver
, public spritebuilder::CCBMemberVariableAssigner
, public spritebuilder::CCBAnimationManagerDelegate
{
public:

	SB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(Caption, create);
	
    //! constructor
    Caption();
	
    //! destructor
    virtual ~Caption();
    
    virtual void onEnter();
    virtual void onEnterTransitionDidFinish();
    virtual void onExit();
    virtual void onExitTransitionDidStart();
    
    virtual bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event);
    virtual void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *unused_event);
    virtual void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event);

    virtual void completedAnimationSequenceNamed(const char *name);
    virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector(cocos2d::Ref * pTarget, const char* pSelectorName){ return nullptr;};
    virtual cocos2d::SEL_CallFuncN onResolveCCBCCCallFuncSelector(cocos2d::Ref * pTarget, const char* pSelectorName) { return nullptr; };
    virtual cocos2d::extension::Control::Handler onResolveCCBCCControlSelector(cocos2d::Ref * pTarget, const char* pSelectorName);
    virtual bool onAssignCCBMemberVariable(cocos2d::Ref * pTarget, const char * pMemberVariableName, cocos2d::Node * pNode);

	CaptionDelegate* getDelegate();
    void setDelegate(CaptionDelegate* pDelegate);

public:
    void setBackVisible(bool visible);
    void setCaptionName(std::string captionName);
    
    void setCaptionTileImgVisible(bool visible);
    
    void setButtonEnable(bool enable);
    bool getButtonEnable();
    
    void show();
    void hide();
    
    /**
     * 戻るボタンの位置を取得
     */
    cocos2d::Point getBackBtnPosition();
    
    /**
     * 戻るボタンのサイズを取得
     */
    cocos2d::Size getBackBtnSize();
    
private:
    void pressedBack(cocos2d::Ref *pSender, cocos2d::extension::Control::EventType type);

private:
    spritebuilder::CCBAnimationManager *_animationManager;

    CaptionDelegate* _delegate;
    
    cocos2d::extension::ControlButton *_backButton;
    cocos2d::Label *_backButtonTxt;
    cocos2d::Label *_captionName;
    cocos2d::Sprite *_captionTitleImg;
};

CREATE_SPRITEBUILDER_LOADER_CLASS(CaptionLoader, Caption);

#endif /* defined(__VitaminProject__Caption__) */
