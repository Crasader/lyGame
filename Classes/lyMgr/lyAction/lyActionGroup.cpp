
#include "lyActionGroup.h"

lyActionGroup::lyActionGroup()
{
	for ( unsigned char byIndex = enActState_Wait; byIndex < enActState_Max; byIndex++ )
	{
		m_szActObj[byIndex] = NULL;
	}
}

lyActionGroup::~lyActionGroup()
{

}

lyActionGroup* lyActionGroup::Create()
{
	return new lyActionGroup();
}

void lyActionGroup::AddAction( lyAction* pAction, unsigned char byState )
{
	if ( pAction && byState < enActState_Max )
	{
		m_szActObj[byState] = pAction;
	}
}
lyAction* lyActionGroup::GetAction( unsigned char byState )
{
	return m_szActObj[byState];
}
