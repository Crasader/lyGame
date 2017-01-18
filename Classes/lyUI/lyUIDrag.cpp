
#include "lyUIDrag.h"

#ifdef TEST_COLLISION
bool gShowTestCollition = true;
#endif


lyUIDrag::lyUIDrag()
:lyUIBase()
,m_pFrame(nullptr)
{

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
    
    
}
void lyUIDrag::draw(Renderer* renderer, const Mat4 &transform, uint32_t flags)
{
    lyUIBase::draw(renderer, transform, flags);
    
    
}

bool lyUIDrag::onTouchBegan(cocos2d::Touch *touches, cocos2d::Event *event)
{
    Vec2 touchNodePoint = this->convertTouchToNodeSpace(touches);
    if (lyCocosFunc::isTouchInWin(this, touches)) {
        m_bIsTouched = true;
        m_TouchBeginPoint = touchNodePoint;
        return true;
    }
    return false;
}

void lyUIDrag::onTouchMoved(cocos2d::Touch *touches, cocos2d::Event *event)
{
    if (m_bIsTouched) {
        Vec2 touchNodePoint = this->convertTouchToNodeSpace(touches);
        Vec2 diffNodePoint = touchNodePoint - m_TouchBeginPoint;
        this->setPosition(this->getPosition()+diffNodePoint);
        this->isOutScreen();
    }
}

void lyUIDrag::onTouchEnded(cocos2d::Touch *touches, cocos2d::Event *event)
{
    if (!m_bIsTouched) {
        return;
    }
    m_bIsTouched = false;
}
void lyUIDrag::onTouchCancelled(cocos2d::Touch *touches, cocos2d::Event *event)
{

}

void lyUIDrag::InitSpritePath(const char* strPath)
{
    m_pFrame = lyFrame::createWithSpritePath(strPath);
    if (m_pFrame) {
        m_pFrame->retain();
        m_pFrame->setScaleX(this->getContentSize().width/m_pFrame->getContentSize().width);
        m_pFrame->setScaleY(this->getContentSize().height/m_pFrame->getContentSize().height);
        //m_pFrame->setContentSize(this->getContentSize());
        m_pFrame->setPosition(0,0);
        this->addChild(m_pFrame);
    }
}

void lyUIDrag::InitSpriteName(const char* strName)
{
    m_pFrame = lyFrame::createWithSpriteName(strName);
    if (m_pFrame) {
        m_pFrame->retain();
        m_pFrame->setScaleX(this->getContentSize().width/m_pFrame->getContentSize().width);
        m_pFrame->setScaleY(this->getContentSize().height/m_pFrame->getContentSize().height);
        //m_pFrame->setContentSize(this->getContentSize());
        m_pFrame->setPosition(0,0);
        this->addChild(m_pFrame);
    }
}