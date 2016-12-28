
#include "lyCocosNode.h"

lyCocosNode::lyCocosNode()
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

void lyCocosNode::onEnter()
{
	CCNode::onEnter();
}

void lyCocosNode::onExit()
{
	CCNode::onExit();

}
void lyCocosNode::visit(Renderer* renderer, const Mat4 &parentTransform, uint32_t parentFlags)
{
    if (!_visible)
    {
        return;
    }
    uint32_t flags = processParentFlags(parentTransform, parentFlags);
    
    if(!_children.empty())
    {
        sortAllChildren();
        int i = 0;
        for( ; i < _children.size(); i++ )
        {
            auto node = _children.at(i);
                node->visit(renderer, _modelViewTransform, flags);
        }
        this->draw(renderer, _modelViewTransform, flags);
        
        for(auto it=_children.cbegin()+i; it != _children.cend(); ++it)
            (*it)->visit(renderer, _modelViewTransform, flags);
    }

    
}
void lyCocosNode::draw(Renderer* renderer, const Mat4 &transform, uint32_t flags)
{
}

void lyCocosNode::OnFrame( float fDeltaTime )
{
    if(!_children.empty())
    {
        for (auto& child : _children)
        {
            Node* childWin = dynamic_cast<Node*>(child);
            if(childWin)
            {
                childWin->update(fDeltaTime);
            }
        }
    }
}

void lyCocosNode::OnDraw( float fx,float fy,float fScale,unsigned char alpha )
{
    
}


