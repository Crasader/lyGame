
#include "lyUIBase.h"

#ifdef TEST_COLLISION
bool gShowTestCollition = true;
#endif


lyUIBase::lyUIBase()
{

	m_bIsTouchDown	= false;
	m_bIsCtrlVisible	= true;
	m_bCtrlEnable	= true;
	m_bAdjustCtrlSpr	= false;


	memset(m_szCtrlName,0,sizeof(m_szCtrlName));

}

lyUIBase::~lyUIBase()
{
}

lyUIBase* lyUIBase::Create()
{
    lyUIBase* pCtrl = new lyUIBase();
    return pCtrl;
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
    //Layer::onEnter();
}

void lyUIBase::onExit()
{
    //Layer::onExit();
}

void lyUIBase::update(float delta)
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


