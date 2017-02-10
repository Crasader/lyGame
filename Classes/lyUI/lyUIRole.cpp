
#include "lyUIRole.h"
#include "lyActionGroup.h"
#include "lyActionManager.h"





lyUIRole::lyUIRole()
:lyUIBase()
{
    m_pAction = NULL;
    m_pCurrFrame = NULL;
    m_nActionGroupId = 0;
    m_nRoleId = 0;
    m_nCurrState = -1;
    m_nNextState = -1;
    
    m_nCurrBlood = 0;
    m_nMaxBlood = 0;
    
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
    if (!_visible)
    {
        return;
    }
    if (m_pCurrFrame) {
        m_pCurrFrame->setScale(this->getContentSize().width/m_pCurrFrame->getContentSize().width, this->getContentSize().height/m_pCurrFrame->getContentSize().height);
        m_pCurrFrame->setAnchorPoint(this->getAnchorPoint());
        m_pCurrFrame->lyVisit();
    }
    
}
bool lyUIRole::onTouchBegan(cocos2d::Touch *touches, cocos2d::Event *event)
{
    if (m_bPause) {
        return false;
    }
    
    if (lyCocosFunc::isTouchInWin(this, touches)) {
        m_bIsTouched = true;
        m_TouchBeginPoint = this->convertTouchToNodeSpace(touches);
        CCLOG("x=======%f,y========%f",this->getPosition().x, this->getPosition().y);
        lyEventManager::ExecuteEventCPP(UIEventType::UI_TOUCH_DOWN, this->GetObjID(),0);
        return true;
    }
    
    return false;
}

void lyUIRole::onTouchMoved(cocos2d::Touch *touches, cocos2d::Event *event)
{
    if (m_bIsTouched) {
        Vec2 touchNodePoint = this->convertTouchToNodeSpace(touches);
        
        Vec2 targetPoint = this->getPosition() + touchNodePoint - m_TouchBeginPoint;
        if (m_bHadSpan) {
            if (targetPoint.x < m_nMinX) {
                targetPoint.x = m_nMinX;
            }
            if (targetPoint.y < m_nMinY) {
                targetPoint.y = m_nMinY;
            }
            if (targetPoint.x > m_nMaxX) {
                targetPoint.x = m_nMaxX;
            }
            if (targetPoint.y > m_nMaxY) {
                targetPoint.y = m_nMaxY;
            }
        }
        
        this->setPosition(targetPoint);
        
        lyEventManager::ExecuteEventCPP(UIEventType::UI_TOUCH_MOVED, this->GetObjID(),0);
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
void lyUIRole::setRoleIdXLS(  int nRoleId )
{
	if (nRoleId < 0 || nRoleId == (unsigned int)-1 )
	{
		return ;
	}
	m_nRoleId = nRoleId;
   
    const MAP_ONE_LINE* szOneLine = lyTableOneLine("Table/Role.csv",m_nRoleId);
    if(szOneLine)
    {
        int nGroupId = lyStrToInt(szOneLine->find("GroupId")->second.c_str());
        int nMaxBlood = lyStrToInt(szOneLine->find("MaxBlood")->second.c_str());
        setMaxBlood(nMaxBlood);
        setGroupId(nGroupId); 
    }
}
void lyUIRole::initRolebyName(const char* plistname, int startIndex, int indexNum)
{
    m_pAction = lyAction::Create();
    if (m_pAction) {
        m_pAction->initbyPlist(plistname,startIndex,indexNum);
        m_pCurrFrame = m_pAction->GetHeaderFrame();
    }
}

int lyUIRole::getRoleId( void )
{
	return m_nRoleId;
}

void lyUIRole::setGroupId( int Id )
{
	m_nActionGroupId = Id;
    setAction(enActState_Wait);
    updateNextAction();
}

void lyUIRole::setAction( char byState )
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


bool lyUIRole::isDead()
{
    bool bDead = false;
    if (m_nCurrBlood == 0) {
        bDead = true;
    }
    return bDead;
}
int lyUIRole::calcHurt(lyUIRole* pAttacker)
{
    //普通伤害计算
    
    //技能伤害计算
    
    //得有一个系数值
    
    //测试
    if (pAttacker) {
        m_nCurrBlood = m_nCurrBlood - pAttacker->calcAttack();
    }
    else
        CCLOG("pBullet is null");
    CCLOG("m_nCurrBlood = %d",m_nCurrBlood);
    if (m_nCurrBlood < 0)
    {
        m_nCurrBlood = 0;
    }
    
    return m_nCurrBlood;
}
int lyUIRole::calcAttack()
{
    //普通伤害计算
    
    //技能伤害计算
    
    //得有一个系数值
    
    //测试
    int nAttack = 0;
    
    const MAP_ONE_LINE* szOneLine = lyTableOneLine("Table/Role.csv",m_nRoleId);
    if(szOneLine)
    {
        int nAddorDec = lyStrToInt(szOneLine->find("AddorDec")->second.c_str());
        nAttack += nAddorDec;
    }
    return nAttack;
}

