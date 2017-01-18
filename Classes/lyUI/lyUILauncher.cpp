
#include "lyUILauncher.h"
#include "lyActionGroup.h"
#include "lyActionManager.h"





lyUILauncher::lyUILauncher()
:lyUIBase()
{
}

lyUILauncher::~lyUILauncher()
{

}

lyUILauncher* lyUILauncher::Create()
{
    lyUILauncher* pCtrl = new lyUILauncher();
    if (pCtrl && pCtrl->init()) {
        return pCtrl;
    }
    return NULL;
}
bool lyUILauncher::init()
{
    setTouchEnabled(true);
    return true;
}
void lyUILauncher::onEnter()
{
    lyUIBase::onEnter();
   
}

void lyUILauncher::onExit()
{
    lyUIBase::onExit();
}

void lyUILauncher::update(float delta)
{
    lyUIBase::update(delta);
  
}
void lyUILauncher::visit(Renderer* renderer, const Mat4 &parentTransform, uint32_t parentFlags)
{
    lyUIBase::visit(renderer, parentTransform, parentFlags);
    if (!_visible)
    {
        return;
    }
}
void lyUILauncher::draw(Renderer* renderer, const Mat4 &transform, uint32_t flags)
{
    lyUIBase::draw(renderer, transform, flags);
}


bool lyUILauncher::onTouchBegan(cocos2d::Touch *touches, cocos2d::Event *event)
{
    Vec2 touchNodePoint = this->convertTouchToNodeSpace(touches);
    if (lyCocosFunc::isTouchInWin(this, touches)) {
        m_bIsTouched = true;
        m_TouchBeginPoint = touchNodePoint;
        return true;
    }
    return false;
}

void lyUILauncher::onTouchMoved(cocos2d::Touch *touches, cocos2d::Event *event)
{
    if (m_bIsTouched) {
        Vec2 touchNodePoint = this->convertTouchToNodeSpace(touches);
        Vec2 diffNodePoint = touchNodePoint - m_TouchBeginPoint;
        this->setPosition(this->getPosition()+diffNodePoint);
    }
}

void lyUILauncher::onTouchEnded(cocos2d::Touch *touches, cocos2d::Event *event)
{
    if (!m_bIsTouched) {
        return;
    }
    m_bIsTouched = false;
}
void lyUILauncher::onTouchCancelled(cocos2d::Touch *touches, cocos2d::Event *event)
{
    
}
void lyUILauncher::setId(int nLauncherId,int nBulletId)
{
    m_nLauncherId = nLauncherId;
    m_nBulletId = nBulletId;
    
    //初始化发射器
    
}
void lyUILauncher::InitSpritePath(const char* strPath)
{

}

void lyUILauncher::InitSpriteName(const char* strName)
{

}
