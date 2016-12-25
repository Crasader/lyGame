/***************************************************************
*	lyRole
*	½ÇÉ«Àà£¬
*	by Shixc 2014-05-05
***************************************************************/
#ifndef _lyRole_H_
#define _lyRole_H_

#include "lyBaseCtrl.h"
#include "lyAction.h"
#include "lyFrame.h"

class lyRole
	:public lyBaseCtrl
{
public:
	lyRole();
	~lyRole();
	static lyRole* Create();

	virtual void OnFrame(float fDeltaTime);
	virtual void OnDraw(float fx,float fy,float fScale,unsigned char alpha);

	void SetRoleId(unsigned int nRoleId);
	unsigned int GetRoleId(void);
	void SetActGroupId(unsigned int Id);
	void SetActState( unsigned char byState );


protected:

private:

private:
	unsigned int	m_nRoleId;
	unsigned int	m_nActionGroupId;
	lyAction*		m_pAction;
	lyFrame*		m_pCurrFrame;
	unsigned char		m_byInterval;
	unsigned char		m_byCurrInterval;
	//end*/

};

#endif //_lyRole_H_
