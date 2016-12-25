
#include "lyNode.h"

lyNode* lyNode::m_pNodeInstance = NULL;


lyNode::lyNode()
{

}

lyNode::~lyNode()
{

}
lyNode* lyNode::GetInstance()
{
	if (!m_pNodeInstance)
	{
		m_pNodeInstance = new lyNode();
	}
	return m_pNodeInstance;
}

void lyNode::onEnter()
{
	CCNode::onEnter();
}

void lyNode::onExit()
{
	CCNode::onExit();

}
void lyNode::OnFrame( float fDeltaTime )
{

}

void lyNode::OnDraw( float fx,float fy,float fScale,unsigned char alpha )
{
}


