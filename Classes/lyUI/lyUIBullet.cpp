
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
    if (m_pBulletFrame) {
        m_pBulletFrame->lyVisit();
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
        this->addChild(m_pBulletFrame);
    }
}
void lyUIBullet::doFly()
{
    auto actionMove = MoveTo::create(200,m_pointE);
    
    auto actionDone = CallFuncN::create(
                                        CC_CALLBACK_1(lyUIBullet::flyEnd, this));
    
    Sequence* sequence = Sequence::create(actionMove, actionDone, NULL);
    this->runAction(sequence);
}
void lyUIBullet::flyEnd(Node* pNode)
{
    
}
