
#include "lyUIRole.h"
#include "lyActionGroup.h"
#include "lyActionManager.h"





lyUIRole::lyUIRole()
:lyUIBase()
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
    lyUIRole* pCtrl = new lyUIRole();
    if (pCtrl && pCtrl->init()) {
        return pCtrl;
    }
    return NULL;
}
bool lyUIRole::init()
{
    setTouchEnabled(true);
    return true;
}
void lyUIRole::Clear()
{
    
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

bool lyUIRole::onTouchBegan(cocos2d::Touch *touches, cocos2d::Event *event)
{
    CCLOG("------------------------------------------");
    CCPoint touchesPoint = touches->getLocation();
    CCPoint touchNodePoint = this->convertTouchToNodeSpace(touches);
    CCPoint NodePoint = this->getPosition();
    //CCLOG("onTouchBegan touchesPoint x=%f, y=%f",touchesPoint.x,touchesPoint.y);
    CCLOG("onTouchBegan touchNodePoint x=%f, y=%f",touchNodePoint.x,touchNodePoint.y);
    CCLOG("onTouchBegan NodePoint    x=%f, y=%f",NodePoint.x,NodePoint.y);
    
    if (lyCocosFunc::isTouchInWin(this, touches)) {
        m_bIsTouched = true;
        m_TouchBeginPoint = touchNodePoint;
        CCLOG("lyUIDrag 点中了");
        CCLOG("------------------------------------------");
        return true;
    }
    CCLOG("------------------------------------------");
    return false;
}

void lyUIRole::onTouchMoved(cocos2d::Touch *touches, cocos2d::Event *event)
{
    if (m_bIsTouched) {
        CCLOG("****************************************");
        CCPoint touchNodePoint = this->convertTouchToNodeSpace(touches);
        CCLOG("touchNodePoint  x=%f, y=%f",touchNodePoint.x,touchNodePoint.y);
        CCPoint diffNodePoint = touchNodePoint - m_TouchBeginPoint;
        CCLOG("diffNodePoint  x=%f, y=%f",diffNodePoint.x,diffNodePoint.y);
        CCLOG("****************************************");
        this->setPosition(this->getPosition()+diffNodePoint);
    }
}

void lyUIRole::onTouchEnded(cocos2d::Touch *touches, cocos2d::Event *event)
{
    if (!m_bIsTouched) {
        return;
    }
    m_bIsTouched = false;
}
void lyUIRole::onTouchCancelled(cocos2d::Touch *touches, cocos2d::Event *event)
{
    
}
