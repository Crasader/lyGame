
#include "lyUIDrag.h"

#ifdef TEST_COLLISION
bool gShowTestCollition = true;
#endif


lyUIDrag::lyUIDrag()
:lyUIBase()
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
    //*
    auto dispatcher = Director::getInstance()->getEventDispatcher();
    auto touchListener = EventListenerTouchOneByOne::create();
    //touchListener->setSwallowTouches(true);
    touchListener->onTouchBegan = CC_CALLBACK_2(lyUIDrag::onTouchBegan, this);
    touchListener->onTouchMoved = CC_CALLBACK_2(lyUIDrag::onTouchMoved, this);
    touchListener->onTouchEnded = CC_CALLBACK_2(lyUIDrag::onTouchEnded, this);
    touchListener->onTouchCancelled = CC_CALLBACK_2(lyUIDrag::onTouchCancelled, this);
    
    dispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
    //*/
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
    /*
    CCLOG("touches Location x=%f,    y=%f",touches->getLocation().x,touches->getLocation().y);
    CCLOG("touches LocationInView x=%f,    y=%f",touches->getLocationInView().x,touches->getLocationInView().y);
    
    CCLOG("touch Location x=%f,    y=%f",touch.getLocation().x,touch.getLocation().y);
    CCLOG("touch LocationInView x=%f,    y=%f",touch.getLocationInView().x,touch.getLocationInView().y);
    CCLOG("touch StartLocation x=%f,    y=%f",touch.getStartLocation().x,touch.getStartLocation().y);
     //*/

    Touch touch = lyCocosFunc::convertToCurWinCoordinateOnlyGL(this, touches);
    if (lyCocosFunc::isTouchInWin(this, &touch)) {
        m_bIsTouched = true;
        
        return true;
    }
    
    return false;
}

void lyUIDrag::onTouchMoved(cocos2d::Touch *touches, cocos2d::Event *event)
{
    if (m_bIsTouched) {
        setPosition(touches->getLocation());
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
