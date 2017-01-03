/***************************************************************
*	lyCocosNode
*	by Shixc 2014-04-10
***************************************************************/
#ifndef _lyCocosNode_H_
#define _lyCocosNode_H_

#include "lyInclude.h"
#include "lyTouchElement.h"

USING_NS_CC;

class lyCocosNode :
public cocos2d::CCNode
,public lyTouchElement
{
public:
	lyCocosNode();
	~lyCocosNode();
    static lyCocosNode* Create();
     bool init();
    

    virtual void onEnter();
    virtual void onExit();
    virtual void visit(Renderer *renderer, const Mat4 &parentTransform, uint32_t parentFlags) override;
    virtual void draw(Renderer *renderer, const Mat4 &transform, uint32_t flags) override;

    virtual bool onTouchBegan(cocos2d::Touch *touches, cocos2d::Event *event);
    virtual void onTouchMoved(cocos2d::Touch *touches, cocos2d::Event *event);
    virtual void onTouchEnded(cocos2d::Touch *touches, cocos2d::Event *event);
    virtual void onTouchCancelled(cocos2d::Touch *touches, cocos2d::Event *event);
    
};


#endif  //_lyCocosNode_H_
