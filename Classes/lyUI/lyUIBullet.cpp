
#include "lyUIBullet.h"
#include "lyActionGroup.h"
#include "lyActionManager.h"





lyUIBullet::lyUIBullet()
:lyUIBase()
,m_pBulletFrame(nullptr)
{
}

lyUIBullet::~lyUIBullet()
{

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
}
void lyUIBullet::draw(Renderer* renderer, const Mat4 &transform, uint32_t flags)
{
    lyUIBase::draw(renderer, transform, flags);
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
void lyUIBullet::InitBulletPath(const char* strPath)
{
    m_pBulletFrame = lyFrame::createWithSpritePath(strPath);
    if (m_pBulletFrame) {
        m_pBulletFrame->retain();
        m_pBulletFrame->setScaleX(this->getContentSize().width/m_pBulletFrame->getContentSize().width);
        m_pBulletFrame->setScaleY(this->getContentSize().height/m_pBulletFrame->getContentSize().height);
        m_pBulletFrame->setPosition(0,0);
        m_pBulletFrame->setAnchorPoint(this->getAnchorPoint());  //必须设置和本控件一样，因为Node和Sprite的默认热点不一样！！！！
        this->addChild(m_pBulletFrame);
    }
}
