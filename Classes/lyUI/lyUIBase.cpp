
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

