/***************************************************************
*	lyNode
*	by Shixc 2014-04-10
***************************************************************/
#ifndef _lyNode_H_
#define _lyNode_H_

#include "lyInclude.h"

USING_NS_CC;

class lyNode :public cocos2d::CCNode
{
public:
	lyNode();
	~lyNode();

	static lyNode* GetInstance();

	virtual void onEnter();
	virtual void onExit();

	void OnFrame(float fDeltaTime);
	void OnDraw(float fx,float fy,float fScale,unsigned char alpha);

private:
	static lyNode* m_pNodeInstance;
};


#endif  //_lyNode_H_
