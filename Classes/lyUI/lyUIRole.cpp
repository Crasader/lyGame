
#include "lyUIRole.h"
#include "lyActionGroup.h"
#include "lyActionManager.h"


lyUIRole::lyUIRole()
{
	m_nRoleId		= (unsigned int)-1;
	m_nActionGroupId	= (unsigned int)-1;
	m_pAction		= NULL;
	m_pCurrFrame		= NULL;

	m_byCurrInterval = 0;
	m_byInterval = 4;

}

lyUIRole::~lyUIRole()
{

}

lyUIRole* lyUIRole::Create()
{
	return new lyUIRole();
}
/*

void lyUIRole::OnFrame( float fDeltaTime )
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

void lyUIRole::OnDraw( float fx,float fy,float fScale,unsigned char alpha )
{
	if(!m_bIsCtrlVisible)
		return;
	if ( m_pCurrFrame )
	{
		m_pCurrFrame->OnDraw( fx + m_fCtrlX, fy + m_fCtrlY, fScale, alpha );
	}
}
 */
void lyUIRole::onEnter()
{
    lyUIBase::onEnter();
}

void lyUIRole::onExit()
{
    lyUIBase::onExit();
}

void lyUIRole::update(float delta)
{
    lyUIBase::update(delta);
}

void lyUIRole::setRoleId( unsigned int nRoleId )
{
	if (nRoleId < 0 || nRoleId == (unsigned int)-1 )
	{
		return ;
	}
	m_nRoleId = nRoleId;
}

unsigned int lyUIRole::getRoleId( void )
{
	return m_nRoleId;
}

void lyUIRole::setGroupId( unsigned int Id )
{
	m_nActionGroupId = Id;
	lyActionGroup* pActGroup = lyActionManager::GetInstance()->GetGroup(m_nActionGroupId);
	if (pActGroup)
	{
		m_pAction = pActGroup->GetAction(enActState_Wait);
	}
}

void lyUIRole::setActState( unsigned char byState )
{
	lyActionGroup* pActGroup = lyActionManager::GetInstance()->GetGroup(m_nActionGroupId);
	if (pActGroup)
	{
		m_pAction = pActGroup->GetAction(byState);
	}
}

