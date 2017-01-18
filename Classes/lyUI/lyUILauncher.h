/***************************************************************
*	lyUILauncher
*	发射器
*	by Shixc 2014-05-05
***************************************************************/
#ifndef __lyGame__lyUILauncher__
#define __lyGame__lyUILauncher__

#include "lyUIBase.h"
#include "lyAction.h"
#include "lyFrame.h"



class lyUILauncher
	:public lyUIBase
{
public:
	lyUILauncher();
	~lyUILauncher();
	static lyUILauncher* Create();
    bool init();
    virtual void onEnter() override;
    virtual void onExit() override;
    virtual void update(float delta) override;
    virtual void visit(Renderer *renderer, const Mat4 &parentTransform, uint32_t parentFlags) override;
    virtual void draw(Renderer *renderer, const Mat4 &transform, uint32_t flags) override;
    
    virtual bool onTouchBegan(cocos2d::Touch *touches, cocos2d::Event *event);
    virtual void onTouchMoved(cocos2d::Touch *touches, cocos2d::Event *event);
    virtual void onTouchEnded(cocos2d::Touch *touches, cocos2d::Event *event);
    virtual void onTouchCancelled(cocos2d::Touch *touches, cocos2d::Event *event);
    
    
    void setId(int nLauncherId,int nBulletId);
    void InitSpritePath(const char* strPath);
    void InitSpriteName(const char* strName);
private:
    int         m_nLauncherId;  //发射器id
    int         m_nBulletId;    //发射物id
    
    
};

#endif //__lyGame__lyUILauncher__
