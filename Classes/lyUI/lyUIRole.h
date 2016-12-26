/***************************************************************
*	lyUIRole
*	角色类
*	by Shixc 2014-05-05
***************************************************************/
#ifndef __lyGame__lyUIRole__
#define __lyGame__lyUIRole__

#include "lyUIBase.h"
#include "lyAction.h"
#include "lyFrame.h"

class lyUIRole
	:public lyUIBase
{
public:
	lyUIRole();
	~lyUIRole();
	static lyUIRole* Create();

    virtual void onEnter();
    virtual void onExit();
    virtual void update(float delta);
    
    
	void setRoleId(unsigned int nRoleId);
	unsigned int getRoleId(void);
	void setGroupId(unsigned int Id);
	void setActState( unsigned char byState );


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

#endif //__lyGame__lyUIRole__
