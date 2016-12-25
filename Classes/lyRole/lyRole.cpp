
#include "lyRole.h"
#include "lyActionGroup.h"
#include "lyActionManager.h"


lyRole::lyRole()
{
	m_nRoleId		= (unsigned int)-1;
	m_nActionGroupId	= (unsigned int)-1;
	m_pAction		= NULL;
	m_pCurrFrame		= NULL;

	m_byCurrInterval = 0;
	m_byInterval = 4;

}

lyRole::~lyRole()
{

}

lyRole* lyRole::Create()
{
	return new lyRole();
}

void lyRole::OnFrame( float fDeltaTime )
{
	if (0 == m_byCurrInterval%m_byInterval)
	{
		if ( m_pAction )
		{
			m_pCurrFrame = m_pAction->GetNextFrame(m_pCurrFrame);
		}
		m_byCurrInterval = 0;
	}
	m_byCurrInterval = m_byCurrInterval + 1;
}

void lyRole::OnDraw( float fx,float fy,float fScale,unsigned char alpha )
{
	if(!m_bIsCtrlVisible)
		return;
	if ( m_pCurrFrame )
	{
		m_pCurrFrame->OnDraw( fx + m_fCtrlX, fy + m_fCtrlY, fScale, alpha );
	}
}

void lyRole::SetRoleId( unsigned int nRoleId )
{
	if (nRoleId < 0 || nRoleId == (unsigned int)-1 )
	{
		return ;
	}
	m_nRoleId = nRoleId;
}

unsigned int lyRole::GetRoleId( void )
{
	return m_nRoleId;
}

void lyRole::SetActGroupId( unsigned int Id )
{
	m_nActionGroupId = Id;
	lyActionGroup* pActGroup = lyActionManager::GetInstance()->GetGroup(m_nActionGroupId);
	if (pActGroup)
	{
		m_pAction = pActGroup->GetAction(enActState_Wait);
	}
}

void lyRole::SetActState( unsigned char byState )
{
	lyActionGroup* pActGroup = lyActionManager::GetInstance()->GetGroup(m_nActionGroupId);
	if (pActGroup)
	{
		m_pAction = pActGroup->GetAction(byState);
	}
}

