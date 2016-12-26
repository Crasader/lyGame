/***************************************************************
*	lyUIBase
*	by Shixc 2014-04-10
***************************************************************/
#ifndef __lyGame__lyUIBase__
#define __lyGame__lyUIBase__



#include "lyLink.h"
#include "lyInclude.h"
#include "CoreLayer.h"
#include "lyCCBInterface.h"

USING_NS_CC;

#define CTRL_NAME_SIZE 16

#define TEST_COLLISION
#ifdef TEST_COLLISION
extern bool gShowTestCollition;
#endif

class lyUIBase :
public CoreLayer
,   public lyCCBInterface
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
    

	void addChild(lyUIBase* pCtrl);
	void removeChild(lyUIBase* pCtrl);

	void SetCtrlName(const char* strCtrlName);
	void SetCtrlSize(float fw, float fh);
	void SetPosition(float fx, float fy);


	void SetCtrlVisible(bool bVisible );
	bool IsCtrlVisible( );
	long GetObjID();



protected:
	void DrawTestRect(float x,float y,ccColor3B& color);

	float m_fCtrlX;
	float m_fCtrlY;
	float m_fCtrlW;
	float m_fCtrlH;

	bool    m_bIsCtrlVisible;
	bool    m_bIsTouchDown;
	bool    m_bCtrlEnable;
	bool    m_bAdjustCtrlSpr;
	bool    m_bTouchEnable;
	char	m_szCtrlName[CTRL_NAME_SIZE];


};


#endif //__lyGame__lyUIBase__
