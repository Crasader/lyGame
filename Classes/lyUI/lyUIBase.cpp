
#include "lyUIBase.h"

#ifdef TEST_COLLISION
bool gShowTestCollition = true;
#endif


lyUIBase::lyUIBase()
:lyCocosNode()
,m_bIsTouched(false)
,m_bIsCtrlVisible(true)
,m_bCtrlEnable(true)
,m_bAdjustCtrlSpr(false)
,m_szCtrlName("")
,m_bTouchEnabled(false)
,m_TouchBeginPoint(CCPoint(0,0))
{
}

lyUIBase::~lyUIBase()
{
}

lyUIBase* lyUIBase::Create()
{
    lyUIBase* pCtrl = new lyUIBase();
    if (pCtrl && pCtrl->init()) {
        return pCtrl;
    }
    return NULL;
}
bool lyUIBase::init()
{
    lyCocosNode::init();

    return true;
}

long lyUIBase::GetObjID()
{
	return (long)this;
}

void lyUIBase::SetCtrlName( const char* strCtrlName )
{
	assert(strCtrlName && strlen(strCtrlName) < CTRL_NAME_SIZE);
	memset(m_szCtrlName,0,sizeof(m_szCtrlName));
	sprintf(m_szCtrlName,"%s",strCtrlName);
}

void lyUIBase::onEnter()
{
    lyCocosNode::onEnter();
}

void lyUIBase::onExit()
{
    lyCocosNode::onExit();
}

void lyUIBase::update(float delta)
{
    lyCocosNode::update(delta);
}
void lyUIBase::visit(Renderer* renderer, const Mat4 &parentTransform, uint32_t parentFlags)
{
    lyCocosNode::visit(renderer, parentTransform, parentFlags);
}
void lyUIBase::draw(Renderer* renderer, const Mat4 &transform, uint32_t flags)
{
    lyCocosNode::draw(renderer, transform, flags);
}
bool lyUIBase::onTouchBegan(cocos2d::Touch *touches, cocos2d::Event *event)
{
    CCLOG("---------------------------------------%ld",GetObjID());
    CCPoint touchesPoint = touches->getLocation();
    CCPoint touNodeSpace = this->convertTouchToNodeSpace(touches);
    CCLOG("lyUIBase touchesPoint x=%f, y=%f",touchesPoint.x,touchesPoint.y);
    CCLOG("lyUIBase touNodeSpace x=%f, y=%f",touNodeSpace.x,touNodeSpace.y);
    return true;
}

void lyUIBase::onTouchMoved(cocos2d::Touch *touches, cocos2d::Event *event)
{
    if (m_bIsTouched) {
        //setPosition(touches->getLocation());
    }
}

void lyUIBase::onTouchEnded(cocos2d::Touch *touches, cocos2d::Event *event)
{
    if (!m_bIsTouched) {
        return;
    }
    m_bIsTouched = false;
}
void lyUIBase::onTouchCancelled(cocos2d::Touch *touches, cocos2d::Event *event)
{
    
}
void lyUIBase::setTouchEnabled(bool bTouch)
{
    if (bTouch == m_bTouchEnabled)
    {
        return;
    }
    m_bTouchEnabled = bTouch;
    if (m_bTouchEnabled)
    {
        m_touchListener = EventListenerTouchOneByOne::create();
        CC_SAFE_RETAIN(m_touchListener);
        m_touchListener->setSwallowTouches(true);
        m_touchListener->onTouchBegan = CC_CALLBACK_2(lyUIBase::onTouchBegan, this);
        m_touchListener->onTouchMoved = CC_CALLBACK_2(lyUIBase::onTouchMoved, this);
        m_touchListener->onTouchEnded = CC_CALLBACK_2(lyUIBase::onTouchEnded, this);
        m_touchListener->onTouchCancelled = CC_CALLBACK_2(lyUIBase::onTouchCancelled, this);
        _eventDispatcher->addEventListenerWithSceneGraphPriority(m_touchListener, this);
    }
    else
    {
        _eventDispatcher->removeEventListener(m_touchListener);
        CC_SAFE_RELEASE_NULL(m_touchListener);
    }
}
