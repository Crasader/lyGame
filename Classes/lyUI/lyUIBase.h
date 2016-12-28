/***************************************************************
*	lyUIBase
*	by Shixc 2014-04-10
***************************************************************/
#ifndef __lyGame__lyUIBase__
#define __lyGame__lyUIBase__



#include "lyLink.h"
#include "lyInclude.h"
#include "lyCocosNode.h"

USING_NS_CC;

#define CTRL_NAME_SIZE 16

#define TEST_COLLISION
#ifdef TEST_COLLISION
extern bool gShowTestCollition;
#endif

class lyUIBase :
public lyCocosNode
, public lyLinkItem<lyUIBase>
, public lyLinkMgr<lyUIBase>
{
public:
	lyUIBase();
	virtual ~lyUIBase();

	static lyUIBase* Create();

    virtual void onEnter();
    virtual void onExit();
    virtual void update(float delta);
    

	void SetCtrlName(const char* strCtrlName);
	long GetObjID();



protected:

	bool    m_bIsCtrlVisible;
	bool    m_bIsTouchDown;
	bool    m_bCtrlEnable;
	bool    m_bAdjustCtrlSpr;
	char	m_szCtrlName[CTRL_NAME_SIZE];


};


#endif //__lyGame__lyUIBase__
