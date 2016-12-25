
#include "lyBaseCtrl.h"

#ifdef TEST_COLLISION
bool gShowTestCollition = true;
#endif


lyBaseCtrl::lyBaseCtrl()
{
	m_fCtrlX = 0.f;
	m_fCtrlY = 0.f;
	m_fCtrlW = 0.f;
	m_fCtrlH = 0.f;


	m_bIsTouchDown	= false;
	m_bIsCtrlVisible	= true;
	m_bCtrlEnable	= true;
	m_bAdjustCtrlSpr	= false;
	m_bTouchEnable	= false;


	memset(m_szCtrlName,0,sizeof(m_szCtrlName));

}

lyBaseCtrl::~lyBaseCtrl()
{
}
long lyBaseCtrl::GetObjID()
{
	return (long)this;
}

void lyBaseCtrl::SetCtrlName( const char* strCtrlName )
{
	assert(strCtrlName && strlen(strCtrlName) < CTRL_NAME_SIZE);
	memset(m_szCtrlName,0,sizeof(m_szCtrlName));
	sprintf(m_szCtrlName,"%s",strCtrlName);
}

void lyBaseCtrl::SetCtrlSize( float fw, float fh )
{
	m_fCtrlW = fw;
	m_fCtrlH = fh;

	m_bAdjustCtrlSpr = true;
}
void lyBaseCtrl::SetPosition( float fx, float fy )
{
	m_fCtrlX = fx;
	m_fCtrlY = fy;
}

void lyBaseCtrl::DrawTestRect(float x,float y,ccColor3B& color)
{
	ccDrawColor4B(color.r,color.g,color.b,255);
	glLineWidth(1.0f);
	ccDrawRect(ccp(x + m_fCtrlX,y + m_fCtrlY),ccp(x + m_fCtrlX + m_fCtrlW,y + m_fCtrlY + m_fCtrlH));
}

bool lyBaseCtrl::IsCtrlVisible()
{
	return m_bIsCtrlVisible;
}

void lyBaseCtrl::SetCtrlVisible( bool bVisible )
{
	m_bIsCtrlVisible = bVisible;
}

void lyBaseCtrl::onEnter()
{
    Layer::onEnter();
}

void lyBaseCtrl::onExit()
{
    Layer::onExit();
}

void lyBaseCtrl::update(float delta)
{
    if(!_children.empty())
    {
        for (auto& child : _children)
        {
            Node* childWin = dynamic_cast<Node*>(child);
            if(childWin)
            {
                childWin->update(delta);
            }
        }
    }
}

void lyBaseCtrl::addChild( lyBaseCtrl* pCtrl )
{
	AddLinkItem(pCtrl);
}

void lyBaseCtrl::removeChild( lyBaseCtrl* pCtrl )
{
	DelLinkItem(pCtrl);
}

lyBaseCtrl* lyBaseCtrl::Create()
{
	lyBaseCtrl* pCtrl = new lyBaseCtrl();
	return pCtrl;
}

