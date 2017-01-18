
#include "lyUIBullet.h"
#include "lyActionGroup.h"
#include "lyActionManager.h"





lyUIBullet::lyUIBullet()
:lyUIBase()
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
    Vec2 touchNodePoint = this->convertTouchToNodeSpace(touches);
    if (lyCocosFunc::isTouchInWin(this, touches)) {
        m_bIsTouched = true;
        m_TouchBeginPoint = touchNodePoint;
        return true;
    }
    return false;
}

void lyUIBullet::onTouchMoved(cocos2d::Touch *touches, cocos2d::Event *event)
{
    if (m_bIsTouched) {
        Vec2 touchNodePoint = this->convertTouchToNodeSpace(touches);
        Vec2 diffNodePoint = touchNodePoint - m_TouchBeginPoint;
        this->setPosition(this->getPosition()+diffNodePoint);
    }
}

void lyUIBullet::onTouchEnded(cocos2d::Touch *touches, cocos2d::Event *event)
{
    if (!m_bIsTouched) {
        return;
    }
    m_bIsTouched = false;
}
void lyUIBullet::onTouchCancelled(cocos2d::Touch *touches, cocos2d::Event *event)
{
    
}
