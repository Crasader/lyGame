
#include "lyUIBullet.h"
#include "lyActionGroup.h"
#include "lyActionManager.h"
#include "lyPlistManager.h"




lyUIBullet::lyUIBullet()
:lyUIBase()
{
    m_nMissEffectId = 0;
   
    m_pButtleAction = NULL;
    m_pButtleFrame = NULL;
    
    m_bPlayMiss = false;
    m_pMissFrame = NULL;
    m_pMissAction = NULL;
    m_byMissInterval = 0;
}

lyUIBullet::~lyUIBullet()
{
    m_nMissEffectId = 0;
    
    m_pButtleAction = NULL;
    m_pButtleFrame = NULL;
    
    m_bPlayMiss = false;
    m_pMissFrame = NULL;
    m_pMissAction = NULL;
    m_byMissInterval = 0;
}

lyUIBullet* lyUIBullet::Create()
{
    lyUIBullet* pCtrl = new lyUIBullet();
    if (pCtrl && pCtrl->init()) {
        return pCtrl;
    }
    return NULL;
}
bool lyUIBullet::init()
{
    setTouchEnabled(true);
    return true;
}
void lyUIBullet::onEnter()
{
    lyUIBase::onEnter();
   
    //doFly();
}

void lyUIBullet::onExit()
{
    lyUIBase::onExit();
}

void lyUIBullet::update(float delta)
{
    lyUIBase::update(delta);
  
}
void lyUIBullet::visit(Renderer* renderer, const Mat4 &parentTransform, uint32_t parentFlags)
{
    lyUIBase::visit(renderer, parentTransform, parentFlags);
    if (!_visible)
    {
        return;
    }
    
    if (m_pMissFrame)
    {
        m_pButtleFrame->setVisible(false);
        
        bool bClear = false;
        if (m_pMissFrame == m_pMissAction->GetTailFrame() )
        {
            bClear = true;
        }
        if (0 == m_byMissInterval%m_byInterval)
        {
            m_pMissFrame = m_pMissAction->GetNextFrame(m_pMissFrame);
            m_byMissInterval = 0;
        }
        m_byMissInterval = m_byMissInterval + 1;
        if (bClear) {
            this->Clear();
        }
    }
    else
    {
        if (m_pButtleFrame)
        {
            if (0 == m_byCurrInterval%m_byInterval)
            {
                m_pButtleFrame = m_pButtleAction->GetNextFrame(m_pButtleFrame);
                m_byCurrInterval = 0;
            }
            m_byCurrInterval = m_byCurrInterval + 1;
        }
    }
    
}
void lyUIBullet::draw(Renderer* renderer, const Mat4 &transform, uint32_t flags)
{
    lyUIBase::draw(renderer, transform, flags);
    
    if (m_pButtleFrame) {
        m_pButtleFrame->lyVisit();
    }
    if (m_pMissFrame) {
        m_pMissFrame->lyVisit();
    }
}


bool lyUIBullet::onTouchBegan(cocos2d::Touch *touches, cocos2d::Event *event)
{
    return false;
}

void lyUIBullet::onTouchMoved(cocos2d::Touch *touches, cocos2d::Event *event)
{

}

void lyUIBullet::onTouchEnded(cocos2d::Touch *touches, cocos2d::Event *event)
{
}
void lyUIBullet::onTouchCancelled(cocos2d::Touch *touches, cocos2d::Event *event)
{
    
}
void lyUIBullet::setButtlePath(std::string strPath, char byMaxId/*=0*/)
{
    if(m_pButtleAction)
    {
        m_pButtleAction->Clear();
        m_pButtleAction = nullptr;
    }
    m_pButtleAction = lyAction::Create();
    if(m_pButtleAction)
    {
        for(char byIndex = 0; byIndex <= byMaxId; byIndex++ )
        {
            std::string strFramePath = StringUtils::format(strPath.c_str(), byIndex,RES_EXT);
            lyFrame* pFrame = lyFrame::createWithSpritePath(strFramePath);
            if (pFrame) {
                pFrame->retain();
                pFrame->setScaleX(this->getContentSize().width/pFrame->getContentSize().width);
                pFrame->setScaleY(this->getContentSize().height/pFrame->getContentSize().height);
                pFrame->setPosition(0,0);
                pFrame->setAnchorPoint(this->getAnchorPoint());  //必须设置和本控件一样，因为Node和Sprite的默认热点不一样！！！！
                m_pButtleAction->AddFrame(pFrame);
            }
        }
        m_pButtleFrame = m_pButtleAction->GetHeaderFrame();
    }
}
void lyUIBullet::Clear()
{
    lyUIBase::Clear();
    
    if (m_pButtleFrame) {
        m_pButtleFrame->cleanup();
        m_pButtleFrame = NULL;
    }
    if (m_pMissFrame) {
        m_pMissFrame->cleanup();
        m_pMissFrame = NULL;
    }
    if (m_pButtleAction) {
        m_pButtleAction->Clear();
        m_pButtleAction = NULL;
    }
    if (m_pMissAction) {
        m_pMissAction->Clear();
        m_pMissAction = NULL;
    }
}

void lyUIBullet::setMissEffectId(int missId)
{
    m_nMissEffectId = missId;
}
void lyUIBullet::playMissEffect()
{
    if (m_pButtleFrame) {
        m_pButtleFrame->setVisible(false);
    }
    m_nMissEffectId=1;
    if (m_nMissEffectId)
    {
        if(m_pMissAction)
        {
            m_pMissAction->Clear();
            m_pMissAction = nullptr;
        }
        m_pMissAction = lyAction::Create();
        if(m_pMissAction)
        {
            const MAP_ONE_LINE* szOneLine = lyTableOneLine("Table/MissEffect.csv",m_nMissEffectId);
            if(szOneLine)
            {
                int nMaxId = lyStrToInt(szOneLine->find("MaxId")->second.c_str());
                string strPath = szOneLine->find("Path")->second.c_str();
                
                lyPlistManager::getInstance()->loadTexturePlist("Effect_dilei");
                
                for(char byIndex = 0; byIndex <= nMaxId; byIndex++ )
                {
                    std::string strFramePath = StringUtils::format(strPath.c_str(), byIndex,RES_EXT);
                    lyFrame* pFrame = lyFrame::createWithSpriteName(strFramePath);
                    if (pFrame) {
                        pFrame->retain();
                        //pFrame->setScaleX(this->getContentSize().width/pFrame->getContentSize().width);
                        //pFrame->setScaleY(this->getContentSize().height/pFrame->getContentSize().height);
                        pFrame->setPosition(0,0);
                        pFrame->setAnchorPoint(this->getAnchorPoint());  //必须设置和本控件一样，因为Node和Sprite的默认热点不一样！！！！
                        m_pMissAction->AddFrame(pFrame);
                    }
                }
                m_pMissFrame = m_pMissAction->GetHeaderFrame();
            }
        }
    }
    else
    {
        this->Clear();
    }
    
}
