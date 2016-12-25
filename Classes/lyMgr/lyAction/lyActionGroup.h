/***************************************************************
*	lyActionGroup
*	by Shixc 2014-05-05
***************************************************************/
#ifndef _lyActionGROUP_H_
#define _lyActionGROUP_H_

#include "lyAction.h"
#include "lyEnum.h"

class lyActionGroup
{
public:
	lyActionGroup();
	~lyActionGroup();

	static lyActionGroup* Create();
	void AddAction(lyAction* pAction, unsigned char byState );
	lyAction* GetAction(unsigned char byState);
    
private:
	lyAction*	m_szActObj[enActState_Max];
};

#endif //_lyActionGROUP_H_
