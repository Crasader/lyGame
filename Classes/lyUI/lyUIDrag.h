/***************************************************************
*	lyUIDrag
*   拖拽控件
*	by Shixc 2017-01-01
***************************************************************/
#ifndef __lyGame__lyUIDrag__
#define __lyGame__lyUIDrag__



#include "lyInclude.h"
#include "lyUIBase.h"

#include "lyFrame.h"
USING_NS_CC;

#define CTRL_NAME_SIZE 16

#define TEST_COLLISION
#ifdef TEST_COLLISION
extern bool gShowTestCollition;
#endif

class lyUIDrag :
public lyUIBase
{
public:
	lyUIDrag();
	virtual ~lyUIDrag();

	static lyUIDrag* Create();
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
    

    void InitSpr(const char* str);

private:
    lyFrame* m_pFrame;


};


#endif //__lyGame__lyUIDrag__
