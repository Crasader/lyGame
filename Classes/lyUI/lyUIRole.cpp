
#include "lyUIRole.h"
#include "lyActionGroup.h"
#include "lyActionManager.h"





lyUIRole::lyUIRole()
:lyUIBase()
,m_byInterval(4)
,m_byCurrInterval(0)
,m_pCurrFrame(nullptr)
,m_pAction(nullptr)
,m_nActionGroupId(0)
,m_nRoleId(0)
,m_nCurrState(-1)
,m_nNextState(-1)
{
}

lyUIRole::~lyUIRole()
{

}

lyUIRole* lyUIRole::Create()
{
	return new lyUIRole();
}

void lyUIRole::onEnter()
{
    lyUIBase::onEnter();
    if (m_pCurrFrame) {
        m_pCurrFrame->onEnter();
    }
   
}

void lyUIRole::onExit()
{
    lyUIBase::onExit();
    if (m_pCurrFrame) {
        m_pCurrFrame->onExit();
    }
}

void lyUIRole::update(float delta)
{
    lyUIBase::update(delta);
    if (m_pCurrFrame) {
       // m_pCurrFrame->update(delta);
    }


    
}
void lyUIRole::visit(Renderer* renderer, const Mat4 &parentTransform, uint32_t parentFlags)
{
    lyUIBase::visit(renderer, parentTransform, parentFlags);
    if (!_visible)
    {
        return;
    }
    if (m_pCurrFrame)
    {
        if (0 == m_byCurrInterval%m_byInterval)
        {
            m_pCurrFrame = m_pAction->GetNextFrame(m_pCurrFrame);
            if (m_nCurrState != m_nNextState && m_pCurrFrame == m_pAction->GetTailFrame())
            {
                updateNextAction();
            }
            m_byCurrInterval = 0;
        }
        m_byCurrInterval = m_byCurrInterval + 1;
    }
}
void lyUIRole::draw(Renderer* renderer, const Mat4 &transform, uint32_t flags)
{
    lyUIBase::draw(renderer, transform, flags);
    if (m_pCurrFrame) {
        m_pCurrFrame->lyVisit();
    }
    
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
    setAction(enActState_Wait);
    updateNextAction();
}

void lyUIRole::setAction( unsigned char byState )
{
    if (m_nCurrState == byState) {
        return;
    }
    m_nNextState = byState;
    
    if (m_pAction && m_pAction->isDelay()) {
        updateNextAction();
    }
}
void lyUIRole::updateNextAction()
{
    m_nCurrState = m_nNextState;
    lyActionGroup* pActGroup = lyActionManager::GetInstance()->GetGroup(m_nActionGroupId);
    if (pActGroup)
    {
        m_pAction = pActGroup->GetAction(m_nNextState);
        if (m_pAction) {
            m_pCurrFrame = m_pAction->GetHeaderFrame();
        }
    }
}

