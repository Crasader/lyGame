/***************************************************************
*	lyCocosNode
*	by Shixc 2014-04-10
***************************************************************/
#ifndef _lyCocosNode_H_
#define _lyCocosNode_H_

#include "lyInclude.h"

USING_NS_CC;

class lyCocosNode :public cocos2d::CCNode
{
public:
	lyCocosNode();
	~lyCocosNode();
    static lyCocosNode* Create();
    

    virtual void onEnter();
    virtual void onExit();
    
    virtual void visit(Renderer *renderer, const Mat4 &parentTransform, uint32_t parentFlags) override;
    virtual void draw(Renderer *renderer, const Mat4 &transform, uint32_t flags) override;
    
	void OnFrame(float fDeltaTime);
	void OnDraw(float fx,float fy,float fScale,unsigned char alpha);

};


#endif  //_lyCocosNode_H_
