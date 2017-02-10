
#include "lyCocosNode.h"

lyCocosNode::lyCocosNode()
:CCNode()
{

}

lyCocosNode::~lyCocosNode()
{

}
lyCocosNode* lyCocosNode::Create()
{
    lyCocosNode *pRet = new lyCocosNode();
    if (pRet && pRet->init())
    {
        pRet->autorelease();
        return pRet;
    }
    else
    {
        delete pRet;
        pRet = NULL;
        return NULL;
    }
}
bool lyCocosNode::init()
{
    Node::init();
    /*
     auto dispatcher = Director::getInstance()->getEventDispatcher();
     auto touchListener = EventListenerTouchOneByOne::create();
     touchListener->setSwallowTouches(true);
     touchListener->onTouchBegan = CC_CALLBACK_2(lyCocosNode::onTouchBegan, this);
     touchListener->onTouchMoved = CC_CALLBACK_2(lyCocosNode::onTouchMoved, this);
     touchListener->onTouchEnded = CC_CALLBACK_2(lyCocosNode::onTouchEnded, this);
     touchListener->onTouchCancelled = CC_CALLBACK_2(lyCocosNode::onTouchCancelled, this);
     
     dispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
     //*/

    return true;
}
void lyCocosNode::onEnter()
{
	Node::onEnter();
}

void lyCocosNode::onExit()
{
	Node::onExit();

}
void lyCocosNode::visit(Renderer* renderer, const Mat4 &parentTransform, uint32_t parentFlags)
{
    Node::visit(renderer, parentTransform, parentFlags);
    if (!_visible)
    {
        return;
    }
}
void lyCocosNode::draw(Renderer* renderer, const Mat4 &transform, uint32_t flags)
{
    Node::draw(renderer, transform, flags);
    
}

bool lyCocosNode::onTouchBegan(cocos2d::Touch *touches, cocos2d::Event *event)
{
    CCLOG("--------------------------------------lyCocosNode::onTouchBegan");
    return false;
}

void lyCocosNode::onTouchMoved(cocos2d::Touch *touches, cocos2d::Event *event)
{

}

void lyCocosNode::onTouchEnded(cocos2d::Touch *touches, cocos2d::Event *event)
{

}
void lyCocosNode::onTouchCancelled(cocos2d::Touch *touches, cocos2d::Event *event)
{
    
}

