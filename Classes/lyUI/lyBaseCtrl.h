/***************************************************************
*	lyBaseCtrl
*	by Shixc 2014-04-10
***************************************************************/
#ifndef _lyBaseCtrl_H_
#define _lyBaseCtrl_H_



#include "lyLink.h"
#include "lyInclude.h"


USING_NS_CC;

#define CTRL_NAME_SIZE 16

#define TEST_COLLISION
#ifdef TEST_COLLISION
extern bool gShowTestCollition;
#endif

class lyBaseCtrl : public Layer,
	public lyLinkItem<lyBaseCtrl>,
	public lyLinkMgr<lyBaseCtrl>
{
public:
	lyBaseCtrl();
	virtual ~lyBaseCtrl();

	static lyBaseCtrl* Create();

    virtual void onEnter();
    virtual void onExit();
    virtual void update(float delta);
    

	void addChild(lyBaseCtrl* pCtrl);
	void removeChild(lyBaseCtrl* pCtrl);

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



#endif //_lyBaseCtrl_H_
