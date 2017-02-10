
#include "lyUIBullet.h"
#include "lyActionGroup.h"
#include "lyActionManager.h"
#include "lyPlistManager.h"




lyUIBullet::lyUIBullet()
:lyUIRole()
{
    m_nMissEffectId = 0;
    m_bPlayMiss = false;
    m_pMissFrame = NULL;
    m_pMissAction = NULL;
    m_byMissInterval = 0;
}

lyUIBullet::~lyUIBullet()
{
    m_nMissEffectId = 0;

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
    lyUIRole::onEnter();
   
}

void lyUIBullet::onExit()
{
    lyUIRole::onExit();
}

void lyUIBullet::update(float delta)
{
    lyUIRole::update(delta);
  
}
void lyUIBullet::visit(Renderer* renderer, const Mat4 &parentTransform, uint32_t parentFlags)
{
    lyUIRole::visit(renderer, parentTransform, parentFlags);
    if (m_bPause) {
        return;
    }
    
    if (m_pMissFrame)
    {
        if (m_pCurrFrame) {
            //m_pCurrFrame->setVisible(false);
        }
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
    }
    
}
void lyUIBullet::draw(Renderer* renderer, const Mat4 &transform, uint32_t flags)
{
    lyUIRole::draw(renderer, transform, flags);

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
void lyUIBullet::setRoute()
{
    Size visibleSize = Director::getInstance()->getVisibleSize();
    int randX = lyRandInt(0,visibleSize.width);
    m_pointS = Vec2( randX,visibleSize.height) ;
    m_pointE = Vec2( randX, 0 );
    m_MoveVector = (m_pointE-m_pointS)/50;
}
void lyUIBullet::Clear()
{
    lyUIRole::Clear();
    
    if (m_pMissFrame) {
        m_pMissFrame->cleanup();
        m_pMissFrame = NULL;
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

void lyUIBullet::playMissAction()
{
    m_nMissEffectId=1;
    if (m_nMissEffectId)
    {
        if (m_pCurrFrame) {
            //m_pCurrFrame->setVisible(false);
        }
        const MAP_ONE_LINE* szOneLine = lyTableOneLine("Table/MissEffect.csv",m_nMissEffectId);
        if (szOneLine) {
            playMissEffect(szOneLine);
            //lySoundManager::getInstance()->playSE(szOneLine->find("Sound")->second.c_str());
        }
        
    }
    else
    {
        Clear();
    }
}


void lyUIBullet::playMissEffect(const MAP_ONE_LINE* missData)
{
    if(m_pMissAction)
    {
        m_pMissAction->Clear();
        m_pMissAction = nullptr;
    }
    //播放特效
    m_pMissAction = lyAction::Create();
    if(m_pMissAction)
    {
        int nMaxId = lyStrToInt(missData->find("MaxId")->second.c_str());
        string strPath = missData->find("Path")->second.c_str();
        
        lyPlistManager::getInstance()->loadTexturePlist("Effect_dilei");
        
        for(char byIndex = 0; byIndex <= nMaxId; byIndex++ )
        {
            std::string strFramePath = StringUtils::format(strPath.c_str(), byIndex,RES_EXT);
            lyFrame* pFrame = lyFrame::createWithSpriteName(strFramePath);
            if (pFrame) {
                pFrame->retain();
                pFrame->setScaleX(this->getContentSize().width/pFrame->getContentSize().width);
                pFrame->setScaleY(this->getContentSize().height/pFrame->getContentSize().height);
                pFrame->setPosition(0,0);
                pFrame->setAnchorPoint(this->getAnchorPoint());  //必须设置和本控件一样，因为Node和Sprite的默认热点不一样！！！！
                m_pMissAction->AddFrame(pFrame);
            }
        }
        m_pMissFrame = m_pMissAction->GetHeaderFrame();
    }
}
