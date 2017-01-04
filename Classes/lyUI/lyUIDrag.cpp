
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
    CCLOG("------------------------------------------");
    CCPoint touchesPoint = touches->getLocation();
    CCPoint touchNodePoint = this->convertTouchToNodeSpace(touches);
    CCPoint NodePoint = this->getPosition();
    //CCLOG("onTouchBegan touchesPoint x=%f, y=%f",touchesPoint.x,touchesPoint.y);
    CCLOG("onTouchBegan touchNodePoint x=%f, y=%f",touchNodePoint.x,touchNodePoint.y);
    //CCLOG("onTouchBegan NodePoint    x=%f, y=%f",NodePoint.x,NodePoint.y);

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

void lyUIDrag::onTouchMoved(cocos2d::Touch *touches, cocos2d::Event *event)
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

void lyUIDrag::InitSpr(const char* str)
{
    m_pFrame = lyFrame::create(str);
    if (m_pFrame) {
        m_pFrame->retain();
        m_pFrame->setScaleX(this->getContentSize().width/m_pFrame->getContentSize().width);
        m_pFrame->setScaleY(this->getContentSize().height/m_pFrame->getContentSize().height);
        //m_pFrame->setContentSize(this->getContentSize());
        m_pFrame->setPosition(0,0);
        this->addChild(m_pFrame);
    }

    
}
