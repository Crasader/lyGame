
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
,m_nBulletId(0)
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
    m_nBulletId = 0;
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
        if (m_nBulletId) {
            //从此坐标 发射出一个子弹
        }
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
//检测碰撞
bool lyUIBase::checkCollision(lyUIBase* temp)
{
    if(!temp)
    {
        return false;
    }
    if (this->getPosition().x + this->getContentSize().width < temp->getPosition().x
        || temp->getPosition().x + temp->getContentSize().width < this->getPosition().x
        || this->getPosition().y + this->getContentSize().height < temp->getPosition().y
        || temp->getPosition().y + temp->getContentSize().height < this->getPosition().y
        
        ) {
        return false;
    }
    return true;
}
bool lyUIBase::isOutScreen()
{
    bool bOut = true;
    //Vec2 anchorPoint = this->getAnchorPoint();
    //CCLOG("anchorPoint==========%f,%f",anchorPoint.x,anchorPoint.y);
    Size sizeWin = Director::getInstance()->getOpenGLView()->getFrameSize();
    CCLOG("sizeWin==========%f,%f",sizeWin.width,sizeWin.height);
    Point pointLD = Vec2(this->getPosition().x,this->getPosition().y);    //左下
    CCLOG("pointLD==========%f,%f",pointLD.x,pointLD.y);
    Point pointLU = Vec2(this->getPosition().x,this->getPosition().y + this->getContentSize().height);  //左上角
    Point pointRD = Vec2(this->getPosition().x + this->getContentSize().width, this->getPosition().y);  //右下角
    Point pointRU = Vec2(this->getPosition().x + this->getContentSize().width, this->getPosition().y + this->getContentSize().height);  //右上角
    //判断四个坐标，有一个坐标在屏幕内就是false
    if ( ( pointLD.x > 0 && pointLD.x < sizeWin.width && pointLD.y > 0 && pointLD.y < sizeWin.height )
        || ( pointLU.x > 0 && pointLU.x < sizeWin.width && pointLU.y > 0 && pointLU.y < sizeWin.height )
        || ( pointRD.x > 0 && pointRD.x < sizeWin.width && pointRD.y > 0 && pointRD.y < sizeWin.height )
        || ( pointRU.x > 0 && pointRU.x < sizeWin.width && pointRU.y > 0 && pointRU.y < sizeWin.height )
        ) {
        bOut = false;
    }
    if (bOut) {
        CCLOG("out" );
    }
    else
        CCLOG("in" );
    return bOut;
}
