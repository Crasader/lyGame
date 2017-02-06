
#include "lyUIDrag.h"

#ifdef TEST_COLLISION
bool gShowTestCollition = true;
#endif


lyUIDrag::lyUIDrag()
:lyUIBase()
,m_pPlaneFrame(nullptr)
{
    m_bPause = false;
    m_bHadSpan = false;
    m_nCurrBlood = 0;
    m_nMaxBlood = 0;
}

lyUIDrag::~lyUIDrag()
{
}

lyUIDrag* lyUIDrag::Create()
{
    lyUIDrag* pCtrl = new lyUIDrag();
    if (pCtrl && pCtrl->init()) {
        return pCtrl;
    }
    return NULL;
}
bool lyUIDrag::init()
{
    setTouchEnabled(true);
    //this->schedule(schedule_selector(lyUIDrag::checkCollision), 0.1f);
    return true;
}
void lyUIDrag::Clear()
{
    
}

void lyUIDrag::onEnter()
{
    lyUIBase::onEnter();
}

void lyUIDrag::onExit()
{
    lyUIBase::onExit();
}

void lyUIDrag::update(float delta)
{
    lyUIBase::update(delta);
}
void lyUIDrag::visit(Renderer* renderer, const Mat4 &parentTransform, uint32_t parentFlags)
{
    lyUIBase::visit(renderer, parentTransform, parentFlags);
    if (m_pPlaneFrame)
    {
        if (0 == m_byCurrInterval%m_byInterval)
        {
            m_pPlaneFrame = m_pPlaneAction->GetNextFrame(m_pPlaneFrame);
            m_byCurrInterval = 0;
        }
        m_byCurrInterval = m_byCurrInterval + 1;
    }
    
}
void lyUIDrag::draw(Renderer* renderer, const Mat4 &transform, uint32_t flags)
{
    lyUIBase::draw(renderer, transform, flags);
    
    if (m_pPlaneFrame) {
        m_pPlaneFrame->lyVisit();
    }
}

bool lyUIDrag::onTouchBegan(cocos2d::Touch *touches, cocos2d::Event *event)
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

void lyUIDrag::onTouchMoved(cocos2d::Touch *touches, cocos2d::Event *event)
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

void lyUIDrag::onTouchEnded(cocos2d::Touch *touches, cocos2d::Event *event)
{
    if (!m_bIsTouched) {
        return;
    }
    lyEventManager::ExecuteEventCPP(UIEventType::UI_TOUCH_UP, this->GetObjID(),0);

    
    m_bIsTouched = false;
}
void lyUIDrag::onTouchCancelled(cocos2d::Touch *touches, cocos2d::Event *event)
{

}
void lyUIDrag::setRoleId(int nid)
{
    m_nRoleId = nid;
    const MAP_ONE_LINE* szOneLine = lyTableOneLine("Table/RoleAction.csv",m_nRoleId);
    if(szOneLine)
    {
        string strPath = szOneLine->find("Path")->second.c_str();
        int nWidth = lyStrToInt(szOneLine->find("Width")->second.c_str());
        int nHeight = lyStrToInt(szOneLine->find("Height")->second.c_str());
        int nMaxBlood = lyStrToInt(szOneLine->find("MaxBlood")->second.c_str());
        int nMaxId = lyStrToInt(szOneLine->find("MaxId")->second.c_str());

        setContentSize(Size(nWidth,nHeight));
        setPosition(200, 0);
        setMaxBlood(nMaxBlood);
        setSpritePath(strPath.c_str(),nMaxId);
    }
}


void lyUIDrag::setSpritePath(const char* strPath, int byMaxId /*= 0*/)
{
    if(m_pPlaneAction)
    {
        m_pPlaneAction->Clear();
        m_pPlaneAction = nullptr;
    }
    m_pPlaneAction = lyAction::Create();
    if(m_pPlaneAction)
    {
        for(char byIndex = 0; byIndex <= byMaxId; byIndex++ )
        {
            std::string strFramePath = StringUtils::format(strPath, byIndex,RES_EXT);
            lyFrame* pFrame = lyFrame::createWithSpritePath(strFramePath);
            if (pFrame) {
                pFrame->retain();
                pFrame->setScaleX(this->getContentSize().width/pFrame->getContentSize().width);
                pFrame->setScaleY(this->getContentSize().height/pFrame->getContentSize().height);
                pFrame->setPosition(0,0);
                pFrame->setAnchorPoint(this->getAnchorPoint());  //必须设置和本控件一样，因为Node和Sprite的默认热点不一样！！！！
                m_pPlaneAction->AddFrame(pFrame);
            }
        }
        m_pPlaneFrame = m_pPlaneAction->GetHeaderFrame();
    }
}

void lyUIDrag::setSpriteName(const char* strName, int byMaxId /*= 0*/)
{
    if(m_pPlaneAction)
    {
        m_pPlaneAction->Clear();
        m_pPlaneAction = nullptr;
    }
    m_pPlaneAction = lyAction::Create();
    if(m_pPlaneAction)
    {
        for(char byIndex = 0; byIndex <= byMaxId; byIndex++ )
        {
            std::string strFramePath = StringUtils::format(strName, byIndex,RES_EXT);
            lyFrame* pFrame = lyFrame::createWithSpriteName(strFramePath);
            if (pFrame) {
                pFrame->retain();
                pFrame->setScaleX(this->getContentSize().width/pFrame->getContentSize().width);
                pFrame->setScaleY(this->getContentSize().height/pFrame->getContentSize().height);
                pFrame->setPosition(0,0);
                pFrame->setAnchorPoint(this->getAnchorPoint());  //必须设置和本控件一样，因为Node和Sprite的默认热点不一样！！！！
                m_pPlaneAction->AddFrame(pFrame);
            }
        }
        m_pPlaneFrame = m_pPlaneAction->GetHeaderFrame();
    }

}
void lyUIDrag::setDragSpan(int minX, int maxX,int minY, int maxY)
{
    m_bHadSpan = true;
    m_nMinX = minX;
    m_nMinY = minY;
    m_nMaxX = maxX;
    m_nMaxY = maxY;
}

bool lyUIDrag::isDead()
{
    bool bDead = false;
    if (m_nCurrBlood == 0) {
        bDead = true;
    }
    return bDead;
}
int lyUIDrag::calcHurt(lyUIBullet* pBullet)
{
    //普通伤害计算
    
    //技能伤害计算
    
    //得有一个系数值
    
    //测试
    if (pBullet) {
        m_nCurrBlood = m_nCurrBlood - pBullet->calcAttack();
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
int lyUIDrag::calcAttack()
{
    //普通伤害计算
    
    //技能伤害计算
    
    //得有一个系数值
    
    //测试
    return 10;
}
